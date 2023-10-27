//============================================
//
//	�G�t�F�N�g���� [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#include "EffectMovePolygon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//�}�N����`
#define SMALLER (10.0f)

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CEffectMovePolygon::m_pTexture = NULL;

//====================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//====================================================================
CEffectMovePolygon::~CEffectMovePolygon()
{

}

//====================================================================
//��������
//====================================================================
CEffectMovePolygon *CEffectMovePolygon::Create()
{
	CEffectMovePolygon *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CEffectMovePolygon();
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
HRESULT CEffectMovePolygon::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	SetType(CObject::TYPE_EFFECT);

	CObjectBillboard::Init();

	//���_�J���[�̐ݒ�
	SetColor(m_col);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CEffectMovePolygon::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//�X�V����
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

		//�T�C�Y�̒���
		m_fRadius += m_fDel;

		m_nLife--;

		//�ʒu�X�V
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

		//�T�C�Y�̒���
		m_fRadius -= m_fDel;
		SetWight(m_fRadius);
		SetHeight(m_fRadius);

		m_nLife--;

		//�ʒu�X�V
		SetPos(GetPos() += m_move);

		if (m_fRadius <= 0.0f)
		{
			Uninit();
			return;
		}
	}

	//���_���̍X�V
	CObjectBillboard::Update();

	SetVerPos(m_VtxPos[0], m_VtxPos[1], m_VtxPos[2], m_VtxPos[3]);
}

//====================================================================
//�`�揈��
//====================================================================
void CEffectMovePolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CObjectBillboard::Draw();
}