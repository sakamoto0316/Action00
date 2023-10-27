//============================================
//
//	�G�t�F�N�g���� [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#include "EMPManager.h"
#include "EffectMovePolygon.h"

//�}�N����`

//�ÓI�����o�ϐ��錾

//====================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//====================================================================
CEMPManager::~CEMPManager()
{

}

//====================================================================
//��������
//====================================================================
CEMPManager *CEMPManager::Create(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType)
{
	CEMPManager *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CEMPManager(pos, fRadius, fDel, nSetCount, nType);
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pPlayer->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//����������
//====================================================================
HRESULT CEMPManager::Init(void)
{
	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CEMPManager::Uninit(void)
{

}

//====================================================================
//�X�V����
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
//�`�揈��
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
//�`�揈��
//====================================================================
void CEMPManager::Draw(void)
{

}