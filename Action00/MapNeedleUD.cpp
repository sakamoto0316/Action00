//============================================
//
//	上下に作用するとげ [MapNeedleUD.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapNeedleUD.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "playerlevel.h"
#include "Map2D.h"
#include "Particle.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CMapNeedleUD::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapNeedleUD::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapNeedleUD::m_dwNumMat = NULL;				//マテリアルの数
int CMapNeedleUD::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapNeedleUD::m_CollisionPos = INITVECTOR3;
bool CMapNeedleUD::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapNeedleUD::CMapNeedleUD(bool bChange, int nPriority) : CObjectXtex(nPriority)
{
	m_ChangeRot = bChange;
}

//====================================================================
//デストラクタ
//====================================================================
CMapNeedleUD::~CMapNeedleUD()
{

}

//====================================================================
//生成処理
//====================================================================
CMapNeedleUD *CMapNeedleUD::Create(bool bChange)
{
	CMapNeedleUD *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapNeedleUD(bChange);
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapNeedleUD.x");

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
HRESULT CMapNeedleUD::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPNEEDLEUD);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapNeedleUD::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapNeedleUD::Update(void)
{
	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CMapNeedleUD::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapNeedleUD::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight() * 1.5f;
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
				pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//上からめり込んだ時
			*bHit = true;
			CGame::GetPlayerLevel()->HitDamage();
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
				pPosOld.y <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//下からめり込んだ時
			*bHit = true;
			CGame::GetPlayerLevel()->HitDamage();
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
				pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y  < mtPos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = mtPos.x - myWight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = mtPos.x + myWight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
		}
	}

	return bOn;
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapNeedleUD::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight() * 1.5f;
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
			pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//上からめり込んだ時
			bOn = true;
			pPos->y = mtPos.y + myHeight;		//ブロックのうえにたたせる
			pMove->y = 0.0f;					//移動量を０にする
			*bHit = true;
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
			pPosOld.y <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//下からめり込んだ時
			*bJumpMove = false;
			pPos->y = mtPos.y - myHeight - fHeight;		//ブロックの下で止める
			pMove->y = 0.0f;					//移動量を０にする
			*bHit = true;
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
			pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y  < mtPos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = mtPos.x - myWight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
			*bHit = true;
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
			pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = mtPos.x + myWight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
			*bHit = true;
		}
	}

	return bOn;
}