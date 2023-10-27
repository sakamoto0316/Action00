//============================================
//
//	マップの中のチェックポイント [MapCheckPoint.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapCheckPoint.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "Map2D.h"
#include "Particle.h"
#include "PlayerLevel.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CMapCheckPoint::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapCheckPoint::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapCheckPoint::m_dwNumMat = NULL;				//マテリアルの数
int CMapCheckPoint::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapCheckPoint::m_CollisionPos = INITVECTOR3;
bool CMapCheckPoint::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapCheckPoint::CMapCheckPoint(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//デストラクタ
//====================================================================
CMapCheckPoint::~CMapCheckPoint()
{

}

//====================================================================
//生成処理
//====================================================================
CMapCheckPoint *CMapCheckPoint::Create()
{
	CMapCheckPoint *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapCheckPoint();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\CheckPoint.x");

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
HRESULT CMapCheckPoint::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPCHECKPOINT);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapCheckPoint::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapCheckPoint::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	CollisionObject(pos);

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CMapCheckPoint::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CMapCheckPoint::CollisionObject(D3DXVECTOR3 pos)
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
			float CollsionHeight = pObj->GetHeight() * 0.5f;	//高さを取得
			float fmyWight = GetWight() * 0.5f;					//中心からの幅
			float fmyHeight = GetHeight() * 0.5f;				//中心からの高さ

			if (type == TYPE_PLAYER3D)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					CPlayerLevel *pPlayer = (CPlayerLevel*)pObj;

					pPlayer->SetReSpownPos(D3DXVECTOR3(pos.x, pos.y + 55.0f, pos.z));

					return true;
				}
			}

			pObj = pObjNext;
		}
	}
	return false;
}