//============================================
//
//	�`���[�g���A������UI�ݒ� [TutorialUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "TutorialUI.h"
#include "manager.h"
#include "game.h"
#include "object2D.h"
#include "input.h"
#include "sound.h"
#include "playerlevel.h"

//�ÓI�����o�ϐ��錾

//====================================================================
//�R���X�g���N�^
//====================================================================
CTutorialUI::CTutorialUI(int TutorialNumber)
{
	m_TurorialNumber = TutorialNumber;
	m_SetColor = 0.0f;
	m_SetColorHlaf = 0.0f;
	m_bColor = true;

	m_pTIPS = NULL;
	m_pTextBG = NULL;
	m_pTutorialText = NULL;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CTutorialUI::~CTutorialUI()
{

}

//====================================================================
//��������
//====================================================================
CTutorialUI *CTutorialUI::Create(int TutorialNumber)
{
	CTutorialUI *pTutorialUI = NULL;

	if (pTutorialUI == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pTutorialUI = new CTutorialUI(TutorialNumber);
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pTutorialUI->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pTutorialUI;
}

//====================================================================
//����������
//====================================================================
HRESULT CTutorialUI::Init(void)
{
	m_pTextBG = CObject2D::Create(7);
	m_pTextBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	m_pTextBG->SetType(CObject::TYPE_TUTORIALUI);
	m_pTextBG->SetTexture("data\\TEXTURE\\Test.jpg");
	m_pTextBG->SetPos(D3DXVECTOR3(0.0f, 500.0f, 0.0f));
	m_pTextBG->SetHeight(50.0f);

	m_pTIPS = CObject2D::Create(7);
	m_pTIPS->SetType(CObject::TYPE_TUTORIALUI);
	m_pTIPS->SetTexture("data\\TEXTURE\\Tutorial_TIPS.png");
	m_pTIPS->SetPos(D3DXVECTOR3(50.0f, 500.0f, 0.0f));
	m_pTIPS->SetWight(100.0f);
	m_pTIPS->SetHeight(100.0f);

	m_pTutorialText = CObject2D::Create(7);
	m_pTutorialText->SetType(CObject::TYPE_TUTORIALUI);
	m_pTutorialText->SetPos(D3DXVECTOR3(230.0f, 500.0f, 0.0f));
	m_pTutorialText->SetWight(300.0f);
	m_pTutorialText->SetHeight(150.0f);

	switch (m_TurorialNumber)
	{
	case 0:
		if (CManager::GetInstance()->GetUseJoyPad() == false)
		{
			m_pTextBG->SetWight(500.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_008.png");
		}
		else
		{
			m_pTextBG->SetWight(640.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_009.png");
		}
		break;

	case 1:
		if (CManager::GetInstance()->GetUseJoyPad() == false)
		{
			m_pTextBG->SetWight(720.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_000.png");
		}
		else
		{
			m_pTextBG->SetWight(620.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_010.png");
		}
		break;

	case 2:
		m_pTextBG->SetWight(500.0f);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_001.png");
		break;

	case 3:
		if (CManager::GetInstance()->GetUseJoyPad() == false)
		{
			m_pTextBG->SetWight(450.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_002.png");
		}
		else
		{
			m_pTextBG->SetWight(370.0f);
			m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_011.png");
		}
		break;

	case 4:
		m_pTextBG->SetWight(750.0f);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_003.png");
		break;

	case 5:
		m_pTextBG->SetWight(750.0f);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_004.png");
		break;

	case 6:
		m_pTextBG->SetWight(750.0);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_005.png");
		break;

	case 7:
		m_pTextBG->SetWight(750.0f);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_006.png");
		break;

	case 8:
		m_pTextBG->SetWight(600.0f);
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_007.png");
		break;

	default:
		m_pTutorialText->SetTexture("data\\TEXTURE\\Tutorial_000.png");
		break;
	}

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CTutorialUI::Uninit(void)
{
	CGame::DeleteTutorial();
}

//====================================================================
//UI�폜����
//====================================================================
void CTutorialUI::DeleteUI(void)
{
	if (m_pTIPS != NULL)
	{
		m_pTIPS->Uninit();
		m_pTIPS = NULL;
	}
	if (m_pTextBG != NULL)
	{
		m_pTextBG->Uninit();
		m_pTextBG = NULL;
	}
	if (m_pTutorialText != NULL)
	{
		m_pTutorialText->Uninit();
		m_pTutorialText = NULL;
	}
}

//====================================================================
//�`���[�g���A���I������
//====================================================================
void CTutorialUI::DeleteTutorial(void)
{
	CManager::GetInstance()->SetStop(false);
	DeleteUI();
	Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CTutorialUI::Update(void)
{
	switch (m_TurorialNumber)
	{
	case 0:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 100.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	case 1:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 500.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	case 2:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 1000.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	case 3:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 1850.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	case 4:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 3150.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	case 5:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 4550.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
	case 6:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 7050.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}

	case 7:
		if (CGame::GetPlayerLevel()->GetPos().x > CGame::GetStartPosX() + 8950.0f)
		{
			CGame::SetTutorial(false);
			DeleteTutorial();
		}
		break;
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CTutorialUI::Draw(void)
{

}
