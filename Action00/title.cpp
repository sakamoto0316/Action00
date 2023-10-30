//============================================
//
//	�^�C�g����� [title.cpp]
//	Author:sakamoto kai
//
//============================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "player3D.h"
#include "break_block3D.h"
#include "BlockUI.h"
#include "ranking.h"
#include "TitleUI.h"
#include "particle.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
CObject2D *CTitle::m_pTitle = NULL;
CObject2D *CTitle::m_pTitleButton = NULL;
CObject2D *CTitle::m_pTitleLogo[4] = {};
int CTitle::m_nSelect = 1;
int CTitle::m_CreateCount = 0;
D3DXVECTOR2 CTitle::m_Tex = D3DXVECTOR2(0.0f, 0.0f);
//====================================================================
//�R���X�g���N�^
//====================================================================
CTitle::CTitle()
{
	m_nSelect = 1;
	m_CreateCount = 0;
	m_Tex = D3DXVECTOR2(0.0f, 0.0f);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CTitle::~CTitle()
{

}

//====================================================================
//����������
//====================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_pTitle = CObject2D::Create();
	m_pTitle->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pTitle->SetWight(1280.0f);
	m_pTitle->SetHeight(720.0f);
	m_pTitle->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	m_pTitle->SetIdx(pTexture->Regist("data\\TEXTURE\\BG.png"));

	m_pTitleLogo[0] = CObject2D::Create();
	m_pTitleLogo[0]->SetPos(D3DXVECTOR3(640.0f, 460.0f, 0.0f));
	m_pTitleLogo[0]->SetWight(1280.0f);
	m_pTitleLogo[0]->SetHeight(720.0f);
	m_pTitleLogo[0]->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleBG00.png"));

	m_pTitleLogo[1] = CObject2D::Create();
	m_pTitleLogo[1]->SetPos(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	m_pTitleLogo[1]->SetRot(D3DXVECTOR3(0.0f, 0.0f, -0.0f));
	m_pTitleLogo[1]->SetWight(1280.0f);
	m_pTitleLogo[1]->SetHeight(720.0f);
	m_pTitleLogo[1]->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleLogoBG.png"));

	m_pTitleLogo[2] = CObject2D::Create();
	m_pTitleLogo[2]->SetPos(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	m_pTitleLogo[2]->SetWight(300.0f);
	m_pTitleLogo[2]->SetHeight(400.0f);
	m_pTitleLogo[2]->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleBG01.png"));

	m_pTitleLogo[3] = CObject2D::Create();
	m_pTitleLogo[3]->SetPos(D3DXVECTOR3(640.0f, 310.0f, 0.0f));
	m_pTitleLogo[3]->SetWight(1050.0f);
	m_pTitleLogo[3]->SetHeight(860.0f);
	m_pTitleLogo[3]->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleLogo.png"));

	m_pTitleButton = CObject2D::Create();
	m_pTitleButton->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
	m_pTitleButton->SetWight(600.0f);
	m_pTitleButton->SetHeight(350.0f);
	m_pTitleButton->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleBotton.png"));

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CTitle::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//====================================================================
//�X�V����
//====================================================================
void CTitle::Update(void)
{
	m_Tex.y -= 0.001f;

	m_pTitle->SetScroll(m_Tex);

	//�I������
	Select();

	m_CreateCount++;
}

//====================================================================
//�`�揈��
//====================================================================
void CTitle::Draw(void)
{

}

//====================================================================
//�I������
//====================================================================
void CTitle::Select(void)
{
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		CManager::GetInstance()->SetUseJoyPad(false);
		CFade::SetFade(CScene::MODE_GAME);
	}
	else if (CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetUseJoyPad(true);
		CFade::SetFade(CScene::MODE_GAME);
	}
}

//====================================================================
//�I�����ڂ̃J���[�ύX����
//====================================================================
void CTitle::SetSelectColor(int nCnt)
{
	m_nSelect = nCnt;
}