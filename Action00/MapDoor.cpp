//============================================
//
//	マップの中のドア [MapDoor.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapDoor.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"
#include "PlayerLevel.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define DOOR_RANGE (100.0f)			//ドア開閉時の振れ幅

LPD3DXMESH CMapDoor::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapDoor::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapDoor::m_dwNumMat = NULL;				//マテリアルの数
int CMapDoor::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapDoor::m_CollisionPos = INITVECTOR3;
bool CMapDoor::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapDoor::CMapDoor(D3DXVECTOR3 Pos, int nPriority) : CObjectXtex(nPriority)
{
	m_StartPos = Pos;
	m_bOpen = false;
}

//====================================================================
//デストラクタ
//====================================================================
CMapDoor::~CMapDoor()
{

}

//====================================================================
//生成処理
//====================================================================
CMapDoor *CMapDoor::Create(D3DXVECTOR3 Pos)
{
	CMapDoor *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapDoor(Pos);
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapDoor.x");

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
HRESULT CMapDoor::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPDOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapDoor::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapDoor::Update(void)
{
	if (m_bOpen == true)
	{
		DoorOpen();
	}
	else
	{ 
		DoorClose();
	}

	CollisionObject(D3DXVECTOR3(m_StartPos.x + 100.0f, m_StartPos.y, m_StartPos.z));

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//ドアを開ける処理
//====================================================================
void CMapDoor::DoorOpen(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (pos.y < m_StartPos.y + DOOR_RANGE)
	{
		m_move.y += 0.2f;
		pos.y += m_move.y;
	}
	else
	{
		pos.y = m_StartPos.y + DOOR_RANGE;
		m_move.y = 0.0f;
	}

	SetPos(pos);
}

//====================================================================
//ドアを閉める処理
//====================================================================
void CMapDoor::DoorClose(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (pos.y > m_StartPos.y)
	{
		m_move.y -= 0.2f;
		pos.y += m_move.y;
	}
	else
	{
		pos.y = m_StartPos.y;
		m_move.y = 0.0f;
	}

	SetPos(pos);
}

//====================================================================
//描画処理
//====================================================================
void CMapDoor::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapDoor::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();

	if (
		(pPos->x + fWidth > mtPos.x - myWight &&
			pPosOld.x + fWidth <= mtPos.x - myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//左からめり込んだ時
		pPos->x = mtPos.x - myWight - fWidth;		//ブロックの左で止める
		pMove->x = 0.0f;					//移動量を０にする

		//仮
		m_bOpen = true;
	}

	if (
		(pPos->x - fWidth < mtPos.x + myWight &&
			pPosOld.x - fWidth >= mtPos.x + myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//右からめり込んだ時
		pPos->x = mtPos.x + myWight + fWidth;		//ブロックの右で止める
		pMove->x = 0.0f;					//移動量を０にする

		//仮
		m_bOpen = false;
	}

	return bOn;
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapDoor::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();

	if (
		(pPos->x + fWidth > mtPos.x - myWight &&
			pPosOld.x + fWidth <= mtPos.x - myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//左からめり込んだ時
		pPos->x = mtPos.x - myWight - fWidth;		//ブロックの左で止める
		pMove->x = 0.0f;					//移動量を０にする
		*bHit = true;
	}

	if (
		(pPos->x - fWidth < mtPos.x + myWight &&
			pPosOld.x - fWidth >= mtPos.x + myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//右からめり込んだ時
		pPos->x = mtPos.x + myWight + fWidth;		//ブロックの右で止める
		pMove->x = 0.0f;					//移動量を０にする
		*bHit = true;
	}

	return bOn;
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CMapDoor::CollisionObject(D3DXVECTOR3 pos)
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