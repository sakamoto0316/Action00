//============================================
//
//	復活時のブロック生成 [BlockSpawn.cpp]
//	Author:sakamoto kai
//
//============================================
#include "BlockReSpawn.h"
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
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

LPD3DXMESH CBlockReSpawn::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CBlockReSpawn::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CBlockReSpawn::m_dwNumMat = NULL;				//マテリアルの数
int CBlockReSpawn::m_nIdxXModel = NULL;				//マテリアルの数

//====================================================================
//コンストラクタ
//====================================================================
CBlockReSpawn::CBlockReSpawn(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//デストラクタ
//====================================================================
CBlockReSpawn::~CBlockReSpawn()
{

}

//====================================================================
//生成処理
//====================================================================
CBlockReSpawn *CBlockReSpawn::Create()
{
	CBlockReSpawn *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CBlockReSpawn();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\Block_Death.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CBlockReSpawn::Init(void)
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
void CBlockReSpawn::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBlockReSpawn::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	//重力
	m_move.y -= 0.98f;

	//減衰係数
	m_move.x = m_move.x * 0.9f;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	//X軸の位置更新
	pos.x += m_move.x;

	//Y軸の位置更新
	pos.y += m_move.y;

	SetPos(pos);

	//頂点情報の更新
	CObjectXtex::Update();

	if (pos.y < 0.0f)
	{
		Uninit();
	}
}

//====================================================================
//描画処理
//====================================================================
void CBlockReSpawn::Draw(void)
{
	CObjectXtex::Draw();
}