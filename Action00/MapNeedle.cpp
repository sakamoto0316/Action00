//============================================
//
//	上下に作用するとげ [MapNeedleUD.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapNeedle.h"
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

LPD3DXMESH CMapNeedle::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapNeedle::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapNeedle::m_dwNumMat = NULL;				//マテリアルの数
int CMapNeedle::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapNeedle::m_CollisionPos = INITVECTOR3;
bool CMapNeedle::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapNeedle::CMapNeedle(D3DXVECTOR3 StartPos, int nPriority) : CObjectXtex(nPriority)
{
	m_StartPos = StartPos;
	m_bRotChange = true;
	m_fMoveWight = 300.0f;
	m_MoveSpeed = 0.005f;
}

//====================================================================
//デストラクタ
//====================================================================
CMapNeedle::~CMapNeedle()
{

}

//====================================================================
//生成処理
//====================================================================
CMapNeedle *CMapNeedle::Create(D3DXVECTOR3 StartPos)
{
	CMapNeedle *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapNeedle(StartPos);
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapNeedle.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(m_CollisionPos.x * 0.5f);
	pBlock->SetHeight(m_CollisionPos.y * 0.5f);

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
HRESULT CMapNeedle::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPNEEDLE);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapNeedle::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapNeedle::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	m_move.x += m_MoveSpeed;

	if (m_bRotChange == false)
	{
		pos.x = m_StartPos.x + sinf(D3DX_PI * m_move.x) * m_fMoveWight;
	}
	else
	{
		pos.y = m_StartPos.y + sinf(D3DX_PI * m_move.x) * m_fMoveWight;
	}


	rot.x += 0.04f;
	rot.y += 0.04f;
	rot.z += 0.04f;

	if (CManager::GetInstance()->GetEdit() == true)
	{
		pos = m_StartPos;
	}

	if (pos.y <= 0.0f)
	{
		Uninit();
		return;
	}

	SetPos(pos);
	SetRot(rot);

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CMapNeedle::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapNeedle::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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

			CGame::GetPlayerLevel()->HitDamage();
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
			*bHit = true;

			CGame::GetPlayerLevel()->HitDamage();
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

			CGame::GetPlayerLevel()->HitDamage();
		}
	}

	return bOn;
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapNeedle::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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