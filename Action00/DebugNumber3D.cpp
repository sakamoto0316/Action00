//============================================
//
//	デバッグ用数字の処理 [DebugNumber.cpp]
//	Author:sakamoto kai
//
//============================================
#include "DebugNumber3D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define NUMBER_WIGHT (100.0f)		//横幅
#define NUMBER_HEIGHT (100.0f)		//縦幅

//====================================================================
//コンストラクタ
//====================================================================
CDebugNumber3D::CDebugNumber3D(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
	m_nNumber = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CDebugNumber3D::~CDebugNumber3D()
{

}

//====================================================================
//生成処理
//====================================================================
CDebugNumber3D *CDebugNumber3D::Create(void)
{
	CDebugNumber3D *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		//オブジェクト2Dの生成
		pExplosion = new CDebugNumber3D();
	}

	//オブジェクトの初期化処理
	if (FAILED(pExplosion->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pExplosion;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CDebugNumber3D::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Number00.png");

	SetType(CObject::TYPE_NUMBER);

	CObjectBillboard::Init();

	SetAnim(D3DXVECTOR2(0.2f, 0.2f));

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CDebugNumber3D::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CDebugNumber3D::Update(void)
{
	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (m_nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (m_nNumber * 0.1f), 1.0f);

	//頂点バッファをアンロックする
	GetVtxBuff()->Unlock();

	//頂点情報の更新
	CObjectBillboard::Update();
}

//====================================================================
//描画処理
//====================================================================
void CDebugNumber3D::Draw(void)
{
	CObjectBillboard::Draw();
}