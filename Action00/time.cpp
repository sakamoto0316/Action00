//============================================
//
//	�^�C���̏��� [time.cpp]
//	Author:sakamoto kai
//
//============================================
#include "time.h"
#include "number.h"
#include "game.h"
#include "playerlevel.h"

//�}�N����`
#define SPACE_TIME (60.0f)		//�^�C�����m�̌���

//�ÓI�����o�ϐ��錾
CNumber *CTime::m_apObject[NUM_TIME] = {};
D3DXVECTOR3 CTime::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CTime::m_nTime = 0;
int CTime::m_nCount = 0;
int CTime::m_nNumber[NUM_TIME] = { 0 };

//====================================================================
//�R���X�g���N�^
//====================================================================
CTime::CTime()
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CTime::~CTime()
{

}

//====================================================================
//��������
//====================================================================
CTime *CTime::Create()
{
	CTime *pMultiBG = NULL;

	if (pMultiBG == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMultiBG = new CTime();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pMultiBG->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pMultiBG;
}

//====================================================================
//�^�C���̏�����
//====================================================================
HRESULT CTime::Init(void)
{
	SetType(CObject::TYPE_MULTIBG);

	SetPos(D3DXVECTOR3(580.0f, 60.0f, 0.0f));

	SetTime(10);

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = CNumber::Create();
			m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * SPACE_TIME), m_pos.y, m_pos.z));
		}
	}
	return S_OK;
}

//====================================================================
//�^�C���̏I��
//====================================================================
void CTime::Uninit(void)
{
	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
			m_apObject[nCntObject] = NULL;
		}
	}

	SetDeathFlag(true);
}

//====================================================================
//�^�C���̍X�V
//====================================================================
void CTime::Update(void)
{
	if (m_nTime > 0)
	{
		m_nCount++;
	}
	else
	{
		CGame::GetPlayerLevel()->HitDamage();
	}

	if (m_nCount >= 60)
	{
		m_nCount = 0;
		m_nTime--;
	}

	m_nNumber[0] = m_nTime % 100 / 10;
	m_nNumber[1] = m_nTime % 10 / 1;

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		m_apObject[nCntObject]->SetNumber(m_nNumber[nCntObject]);
	}
}

//====================================================================
//�^�C���̕`��
//====================================================================
void CTime::Draw(void)
{

}