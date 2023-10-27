//============================================
//
//	マップの中の大砲 [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "CannonBullet.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "Map2D.h"
#include "Particle.h"
#include "Effect.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CCannonBullet::m_pMesh = NULL;			//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CCannonBullet::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CCannonBullet::m_dwNumMat = NULL;				//マテリアルの数
int CCannonBullet::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CCannonBullet::m_CollisionPos = INITVECTOR3;
bool CCannonBullet::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CCannonBullet::CCannonBullet(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//デストラクタ
//====================================================================
CCannonBullet::~CCannonBullet()
{

}

//====================================================================
//生成処理
//====================================================================
CCannonBullet *CCannonBullet::Create()
{
	CCannonBullet *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CCannonBullet();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\CannonBullet.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(m_CollisionPos.x);
	pBlock->SetHeight(m_CollisionPos.y);

	//オブジェクトの初期化処理
	if (FAILED(pBlock->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pBlock;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CCannonBullet::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_CANNONBULLET);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CCannonBullet::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CCannonBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	pos += m_move;

	CollisionObject(pos);

	CEffect *pEffect = CEffect::Create();
	pEffect->SetPos(pos);
	pEffect->SetRadius(50.0f);
	pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pEffect->SetLife(500);
	pEffect->SetDel(10.0f);

	SetPos(pos);

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CCannonBullet::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CCannonBullet::CollisionObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();				//種類を取得
			D3DXVECTOR3 CollsionPos = pObj->GetPos();			//位置を取得
			float CollsionWight = pObj->GetWight() * 0.5f;		//幅を取得
			float CollsionHeight = pObj->GetHeight() * 0.5f;			//高さを取得
			float fmyWight = GetWight() * 0.5f;					//中心からの幅
			float fmyHeight = GetHeight() * 0.5f;				//中心からの高さ

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPNEEDLEUD)
			{//種類がマップオブジェクトの時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_WALL)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_PLAYER3D)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					pObj->HitDamage();

					Uninit();

					return true;
				}
			}

			pObj = pObjNext;
		}
	}
	return false;
}
