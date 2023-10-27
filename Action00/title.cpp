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
int CTitle::m_nSelect = 1;
int CTitle::m_CreateCount = 0;
//====================================================================
//�R���X�g���N�^
//====================================================================
CTitle::CTitle()
{
	m_nSelect = 1;
	m_CreateCount = 0;
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

	m_pTitle = CObject2D::Create();
	m_pTitle->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pTitle->SetWight(1280.0f);
	m_pTitle->SetHeight(720.0f);
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_pTitle->SetIdx(pTexture->Regist("data\\TEXTURE\\Title.png"));

	//for (int nCnt = 0; nCnt < 10; nCnt++)
	//{
	//	m_pBlock3D = CBreak_Block3D::Create();
	//	m_pBlock3D->bUseSet();
	//	m_pBlock3D->SetPos(D3DXVECTOR3(-240.0f + nCnt * 40.0f, 0.0f, 0.0f));
	//	m_pBlock3D->SetWNumber(5);
	//}

	////BGM�̍Đ�
	//m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

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