//============================================
//
//	横方向への壁生成攻撃 [WallAttackSide.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallAttackSide.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"

//マクロ定義
#define BLOCK_WIGHT (40.0f)		//横幅
#define BLOCK_HEIGHT (40.0f)	//縦幅
#define WALL_UPEND (30.0f)		//上昇位置
#define MAX_LIFE (60)			//寿命の最大値

LPD3DXMESH CWallAttackSide::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CWallAttackSide::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CWallAttackSide::m_dwNumMat = NULL;					//マテリアルの数
int CWallAttackSide::m_nIdxXModel = NULL;					//マテリアルの数
D3DXVECTOR3 CWallAttackSide::m_CollisionPos = INITVECTOR3;
bool CWallAttackSide::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CWallAttackSide::CWallAttackSide(bool bRight, int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;

	m_bRight = bRight;

	SetMatChange(true);

	if (m_bRight == true)
	{
		m_move.x = WALL_UPEND;
	}
	else
	{
		m_move.x = -WALL_UPEND;
	}

	m_bFall = false;
	m_bBreak = false;
	m_nLife = MAX_LIFE;
}

//====================================================================
//デストラクタ
//====================================================================
CWallAttackSide::~CWallAttackSide()
{

}

//====================================================================
//生成処理
//====================================================================
CWallAttackSide *CWallAttackSide::Create(bool bRight)
{
	CWallAttackSide *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CWallAttackSide(bRight);
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallAttackSample.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pPlayer->GetSize();
		m_bCollision = true;
	}
	pPlayer->SetWight(m_CollisionPos.x);
	pPlayer->SetHeight(m_CollisionPos.y);

	//オブジェクトの初期化処理
	if (FAILED(pPlayer->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CWallAttackSide::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_WALL);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CWallAttackSide::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CWallAttackSide::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;

	//減衰係数
	m_move.x = m_move.x * 0.7f;

	//速度が一定以下になると動きを止めて落下させる
	if (m_move.x > -0.01f && m_move.x < 0.01f)
	{
		m_move.x = 0.0f;

		m_bFall = true;
	}

	if (m_bFall == true)
	{
		m_move.y -= 0.5f;
	}

	//位置情報の更新
	pos.x += m_move.x;
	CollisionObject(&pos, true);

	//位置情報の更新
	pos.y += m_move.y;
	CollisionObject(&pos, false);

	SetPos(pos);

	//頂点情報の更新
	CObjectXtex::Update();

	if (m_bBreak == true)
	{
		if (m_nLife > 0)
		{
			m_nLife--;
		}
		else
		{
			Uninit();
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CWallAttackSide::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
bool CWallAttackSide::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLEUD ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPPITFLOOR ||
				type == TYPE_MAPCANNON)
			{//種類がブロックの時
				bool bJampMove = true;
				bool Hit = false;
				D3DXVECTOR3 MoveOld = m_move;

				pObj->Collision(pos, m_posOld, &m_move, GetHeight(), GetWight() * 0.5f, &bJampMove, &Hit, bX);

				if (Hit == true)
				{
					if (MoveOld.y < -5.0f)
					{
						Uninit();
						return true;
					}
					else
					{
						m_bBreak = true;
					}
				}
			}
			else if (type == TYPE_BOSSLEVEL)
			{
				bool bJampMove = true;
				bool Hit = false;
				D3DXVECTOR3 MoveOld = m_move;

				pObj->Collision(pos, m_posOld, &m_move, GetHeight(), GetWight() * 0.5f, &bJampMove, &Hit, bX);

				if (Hit == true)
				{
					Uninit();
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}