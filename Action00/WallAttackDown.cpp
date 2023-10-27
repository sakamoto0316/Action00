//============================================
//
//	下方向への壁生成攻撃 [WallAttackDown.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallAttackDown.h"
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
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CWallAttackDown::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CWallAttackDown::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CWallAttackDown::m_dwNumMat = NULL;					//マテリアルの数
int CWallAttackDown::m_nIdxXModel = NULL;					//マテリアルの数
D3DXVECTOR3 CWallAttackDown::m_CollisionPos = INITVECTOR3;
bool CWallAttackDown::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CWallAttackDown::CWallAttackDown(int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;

	SetMatChange(true);

	m_posOld = INITVECTOR3;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//デストラクタ
//====================================================================
CWallAttackDown::~CWallAttackDown()
{

}

//====================================================================
//生成処理
//====================================================================
CWallAttackDown *CWallAttackDown::Create()
{
	CWallAttackDown *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CWallAttackDown();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallJumpSample.x");

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
HRESULT CWallAttackDown::Init(void)
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
void CWallAttackDown::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CWallAttackDown::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;

	//重力
	m_move.y -= 0.98f;

	//位置情報の更新
	pos.x += m_move.x;
	CollisionObject(&pos, true);

	//位置情報の更新
	pos.y += m_move.y;
	CollisionObject(&pos, false);

	SetPos(pos);

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CWallAttackDown::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
bool CWallAttackDown::CollisionObject(D3DXVECTOR3 *pos, bool bX)
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
				type == TYPE_MAPCANNON)
			{//種類がブロックの時
				bool bJampMove = true;
				bool Hit = false;
				D3DXVECTOR3 MoveOld = m_move;

				pObj->Collision(pos, m_posOld, &m_move, GetHeight(), GetWight() * 0.5f, &bJampMove, &Hit, bX);

				if (Hit == true)
				{
					Uninit();
					return true;
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