//============================================
//
//	エフェクト処理 [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#include "EffectMovePolygon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define SMALLER (10.0f)

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CEffectMovePolygon::m_pTexture = NULL;

//====================================================================
//コンストラクタ
//====================================================================
CEffectMovePolygon::CEffectMovePolygon(int nPriority) : CObjectBillboard(nPriority)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxPos[nCnt] = INITVECTOR3;
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = 0.0f;
	m_fSetRadius = 10.0f;
	m_nLife = 10;
	m_fDel = SMALLER;
	m_bStart = false;
	m_bCenter = false;
	m_fStartRadius = 10.0f;
	m_bSet = false;

	if (m_bSet == true)
	{
		m_fRadius = 100.0f;
	}
}

//====================================================================
//デストラクタ
//====================================================================
CEffectMovePolygon::~CEffectMovePolygon()
{

}

//====================================================================
//生成処理
//====================================================================
CEffectMovePolygon *CEffectMovePolygon::Create()
{
	CEffectMovePolygon *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CEffectMovePolygon();
	}

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
HRESULT CEffectMovePolygon::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	SetType(CObject::TYPE_EFFECT);

	CObjectBillboard::Init();

	//頂点カラーの設定
	SetColor(m_col);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEffectMovePolygon::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CEffectMovePolygon::Update(void)
{
	if (m_bSet == false)
	{
		if (m_bStart == false)
		{
			m_CenterPos = D3DXVECTOR3(-m_fSetRadius * 0.5f, -m_fSetRadius * 0.5f, 0.0f);

			m_VtxPos[0] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y + m_fRadius, 0.0f);
			m_VtxPos[1] = D3DXVECTOR3(m_CenterPos.x + m_fRadius, m_CenterPos.y + m_fRadius, 0.0f);
			m_VtxPos[2] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, 0.0f);
			m_VtxPos[3] = D3DXVECTOR3(m_CenterPos.x + m_fRadius, m_CenterPos.y, 0.0f);

			m_fStartRadius = m_fSetRadius;
			m_bStart = true;
		}

		if (m_bCenter == false)
		{
			if (m_fSetRadius * 0.5f < m_fRadius)
			{
				m_bCenter = true;
			}
		}

		if (m_bCenter == false)
		{
			m_VtxPos[0] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y + m_fRadius * 2.0f, 0.0f);
			m_VtxPos[1] = D3DXVECTOR3(m_CenterPos.x + m_fRadius, m_CenterPos.y + m_fRadius, 0.0f);
			m_VtxPos[2] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, 0.0f);
			m_VtxPos[3] = D3DXVECTOR3(m_CenterPos.x + m_fRadius * 2.0f, m_CenterPos.y, 0.0f);
		}
		else
		{
			m_VtxPos[1] = D3DXVECTOR3(m_CenterPos.x + m_fRadius, m_CenterPos.y + m_fRadius, 0.0f);
			m_VtxPos[2] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, 0.0f);
		}

		//サイズの調整
		m_fRadius += m_fDel;

		m_nLife--;

		//位置更新
		SetPos(GetPos() += m_move);

		if (m_fRadius > m_fSetRadius)
		{
			m_fRadius = m_fSetRadius;
			m_bSet = true;
			m_bStart = false;
			m_bCenter = false;
		}
	}
	else
	{
		if (m_bStart == false)
		{
			m_CenterPos = D3DXVECTOR3(m_fSetRadius * 0.5f, m_fSetRadius * 0.5f, 0.0f);

			m_VtxPos[0] = D3DXVECTOR3(m_CenterPos.x - m_fRadius, m_CenterPos.y, 0.0f);
			m_VtxPos[1] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, 0.0f);
			m_VtxPos[2] = D3DXVECTOR3(m_CenterPos.x - m_fRadius, m_CenterPos.y - m_fRadius, 0.0f);
			m_VtxPos[3] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y - m_fRadius, 0.0f);

			m_fStartRadius = m_fSetRadius;
			m_bStart = true;
		}

		if (m_bCenter == false)
		{
			if (m_fStartRadius * 0.5f >= m_fRadius)
			{
				m_bCenter = true;
			}
		}

		if (m_bCenter == true)
		{
			m_VtxPos[0] = D3DXVECTOR3(m_CenterPos.x - m_fRadius * 2.0f, m_CenterPos.y, 0.0f);
			m_VtxPos[3] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y - m_fRadius * 2.0f, 0.0f);
		}

		m_VtxPos[1] = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, 0.0f);
		m_VtxPos[2] = D3DXVECTOR3(m_CenterPos.x - m_fRadius, m_CenterPos.y - m_fRadius, 0.0f);

		//サイズの調整
		m_fRadius -= m_fDel;
		SetWight(m_fRadius);
		SetHeight(m_fRadius);

		m_nLife--;

		//位置更新
		SetPos(GetPos() += m_move);

		if (m_fRadius <= 0.0f)
		{
			Uninit();
			return;
		}
	}

	//頂点情報の更新
	CObjectBillboard::Update();

	SetVerPos(m_VtxPos[0], m_VtxPos[1], m_VtxPos[2], m_VtxPos[3]);
}

//====================================================================
//描画処理
//====================================================================
void CEffectMovePolygon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CObjectBillboard::Draw();
}