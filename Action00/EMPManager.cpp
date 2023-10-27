//============================================
//
//	エフェクト処理 [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#include "EMPManager.h"
#include "EffectMovePolygon.h"

//マクロ定義

//静的メンバ変数宣言

//====================================================================
//コンストラクタ
//====================================================================
CEMPManager::CEMPManager(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType, int nPriority) : CObject(nPriority)
{
	//CEMPManager::Create(m_pos, 50.0f, 7.0f, 8, 0);

	m_nPSetWave = 0;
	m_nPSetCount = 0;
	m_nPSetCountMax = nSetCount;
	m_Ppos = pos;
	m_nPRadius = fRadius;
	m_nPDel = fDel;
	m_nType = nType;
}

//====================================================================
//デストラクタ
//====================================================================
CEMPManager::~CEMPManager()
{

}

//====================================================================
//生成処理
//====================================================================
CEMPManager *CEMPManager::Create(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType)
{
	CEMPManager *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CEMPManager(pos, fRadius, fDel, nSetCount, nType);
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
HRESULT CEMPManager::Init(void)
{
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEMPManager::Uninit(void)
{

}

//====================================================================
//更新処理
//====================================================================
void CEMPManager::Update(void)
{
	if (m_nPSetCount > 0)
	{
		m_nPSetCount--;
	}
	else
	{
		CEffectMovePolygon *pEffect = CEffectMovePolygon::Create();

		switch (m_nType)
		{
		case 0:
			switch (m_nPSetWave)
			{
			case 0:
				m_nPSetCount = m_nPSetCountMax;
				m_nPSetWave++;

				pEffect->SetPos(m_Ppos);
				pEffect->SetRadius(m_nPRadius);
				pEffect->SetDel(m_nPDel);
				break;

			case 1:
				m_nPSetCount = m_nPSetCountMax;
				m_nPSetWave++;

				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					CEffectMovePolygon *pEffect = CEffectMovePolygon::Create();

					switch (nCnt)
					{
					case 0:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x - m_nPRadius, m_Ppos.y				, m_Ppos.z));
						break;
					case 1:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x - m_nPRadius, m_Ppos.y - m_nPRadius, m_Ppos.z));
						break;
					case 2:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x			, m_Ppos.y - m_nPRadius, m_Ppos.z));
						break;
					case 3:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x + m_nPRadius, m_Ppos.y - m_nPRadius, m_Ppos.z));
						break;
					case 4:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x + m_nPRadius, m_Ppos.y				, m_Ppos.z));
						break;
					case 5:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x + m_nPRadius, m_Ppos.y + m_nPRadius, m_Ppos.z));
						break;
					case 6:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x			, m_Ppos.y + m_nPRadius, m_Ppos.z));
						break;
					case 7:
						pEffect->SetPos(D3DXVECTOR3(m_Ppos.x - m_nPRadius, m_Ppos.y + m_nPRadius, m_Ppos.z));
						break;
					}
					pEffect->SetRadius(m_nPRadius);
					pEffect->SetDel(m_nPDel);
				}
				break;
			}
			break;
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CEMPManager::SetMoveParticle(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType)
{
	switch (nType)
	{
	case 0:
		switch (m_nPSetWave)
		{
		case -1:
			m_nPSetWave = 0;
			m_nPSetCount = nSetCount;
			m_nPSetCountMax = nSetCount;
			m_Ppos = pos;
			m_nPRadius = fRadius;
			m_nPDel = fDel;

			CEffectMovePolygon *pEffect = CEffectMovePolygon::Create();
			pEffect->SetPos(m_Ppos);
			pEffect->SetRadius(m_nPRadius);
			pEffect->SetDel(m_nPDel);
			break;
		}
		break;
	}
}

//====================================================================
//描画処理
//====================================================================
void CEMPManager::Draw(void)
{

}