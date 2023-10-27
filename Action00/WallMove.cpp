//============================================
//
//	移動時の壁生成処理 [WallMove.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallMove.h"
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

LPD3DXMESH CWallMove::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CWallMove::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CWallMove::m_dwNumMat = NULL;					//マテリアルの数
int CWallMove::m_nIdxXModel = NULL;					//マテリアルの数

//====================================================================
//コンストラクタ
//====================================================================
CWallMove::CWallMove(int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;

	SetMatChange(true);
}

//====================================================================
//デストラクタ
//====================================================================
CWallMove::~CWallMove()
{

}

//====================================================================
//生成処理
//====================================================================
CWallMove *CWallMove::Create()
{
	CWallMove *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CWallMove();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallMove.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CWallMove::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_EFFECT);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CWallMove::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CWallMove::Update(void)
{
	if (m_ColorA > 0.0f)
	{
		m_ColorA -= 0.03f;
	}
	m_BlockColor.a = m_ColorA;

	if (m_fUpPos < WALL_UPEND)
	{
		D3DXVECTOR3 pos = GetPos();

		pos.y += m_fUpPos;
		m_fUpPos += 5.0f;

		SetPos(pos);
	}

	//頂点情報の更新
	CObjectXtex::Update();

	if (m_ColorA < 0.0f)
	{
		Uninit();
	}
}

//====================================================================
//描画処理
//====================================================================
void CWallMove::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}