//============================================
//
//	マップの中のスイッチ [MapSwitch.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapSwitch.h"
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
#include "sound.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CMapSwitch::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapSwitch::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapSwitch::m_dwNumMat = NULL;				//マテリアルの数
int CMapSwitch::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapSwitch::m_CollisionPos = INITVECTOR3;
bool CMapSwitch::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapSwitch::CMapSwitch(int nPriority) : CObjectXtex(nPriority)
{
	SwitchOn = false;
	SetTexOne(true);
	OnTime = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CMapSwitch::~CMapSwitch()
{

}

//====================================================================
//生成処理
//====================================================================
CMapSwitch *CMapSwitch::Create()
{
	CMapSwitch *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapSwitch();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapSwitch.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(48.0f);
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
HRESULT CMapSwitch::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPSWITCH);

	m_pDoor = CMapDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pDoor->SetType(CObject::TYPE_MAPSDOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapSwitch::Uninit(void)
{
	m_pDoor->Uninit();

	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapSwitch::Update(void)
{
	D3DXVECTOR3 Pos = GetPos();
	D3DXVECTOR3 Rot = GetRot();

	if (bSetDoor == false)
	{
		m_pDoor->SetStartPos(m_DoorPos);
		m_pDoor->SetPos(m_DoorPos);

		bSetDoor = true;
	}

	Rot.y += 0.02f;

	SetRot(Rot);

	if (SwitchOn == false)
	{
		CTexture *pTexture = CManager::GetInstance()->GetTexture();;
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
	}
	else
	{
		CTexture *pTexture = CManager::GetInstance()->GetTexture();;
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0_1.png");

		OnCountDown();
	}

	m_pDoor->SetOpen(SwitchOn);

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//更新処理
//====================================================================
void CMapSwitch::OnCountDown(void)
{
	if (OnTime > 0)
	{
		OnTime--;
	}
	else
	{
		SwitchOn = false;
	}
}


//====================================================================
//描画処理
//====================================================================
void CMapSwitch::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapSwitch::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
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
bool CMapSwitch::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
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

			//仮
			if (SwitchOn == false)
			{
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
				SwitchOn = true;
			}
			OnTime = 120;
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

			//仮
			SwitchOn = true;
			OnTime = 120;
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
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

			//仮
			SwitchOn = true;
			OnTime = 120;
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
		}
	}

	return bOn;
}