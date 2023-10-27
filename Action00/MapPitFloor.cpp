//============================================
//
//	マップ中のすり抜け床 [MapPitFloor.h]
//	Author:sakamoto kai
//
//============================================
#include "MapPitFloor.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"
#include "input.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CMapPitFloor::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CMapPitFloor::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CMapPitFloor::m_dwNumMat = NULL;				//マテリアルの数
int CMapPitFloor::m_nIdxXModel = NULL;				//マテリアルの数
D3DXVECTOR3 CMapPitFloor::m_CollisionPos = INITVECTOR3;
bool CMapPitFloor::m_bCollision = false;

//====================================================================
//コンストラクタ
//====================================================================
CMapPitFloor::CMapPitFloor(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//デストラクタ
//====================================================================
CMapPitFloor::~CMapPitFloor()
{

}

//====================================================================
//生成処理
//====================================================================
CMapPitFloor *CMapPitFloor::Create()
{
	CMapPitFloor *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CMapPitFloor();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapPtiFloor.x");

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
HRESULT CMapPitFloor::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPPITFLOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CMapPitFloor::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CMapPitFloor::Update(void)
{
	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CMapPitFloor::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapPitFloor::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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

		 //キーボードの取得
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
			CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

			if ((pInputKeyboard->GetPress(DIK_S) == false &&
				pInputKeyboard->GetPress(DIK_DOWN) == false &&
				pInputJoypad->GetPress(CInputJoypad::BUTTON_DOWN, 0) == false) &&
				0.01f > pInputJoypad->Get_Stick_Left(0).y)
			{
				bOn = true;
				pPos->y = mtPos.y + myHeight;		//ブロックのうえにたたせる
				pMove->y = 0.0f;					//移動量を０にする
				*bHit = true;
			}
		}
	}

	return bOn;
}

//====================================================================
//当たり判定処理
//====================================================================
bool CMapPitFloor::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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
		}
	}

	return bOn;
}