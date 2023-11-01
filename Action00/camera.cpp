//============================================
//
//	�J�����̏��� [camera.cpp]
//	Author:sakamoto kai
//
//============================================
#include "camera.h"
#include "manager.h"
#include "game.h"
#include "player3D.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "bosslevel.h"
#include "playerlevel.h"
#include "Edit.h"

//�}�N����`
#define CAMERA_DISTANCE (700.0f)//���_�ƒ����_�̋���
#define MODEL_DISTANCE (10.0f)	//���f���ƒ����_�̋���
#define CAMERA_SPEED (3.0f)		//�J�����̈ړ��X�s�[�h
#define CAMERA_VR_SPEED (0.03f)	//�J�����̎��_�X�s�[�h
#define CAMERA_HOMING (0.1f)	//�J�����̒Ǐ]�X�s�[�h
#define POS_HOMING (0.9f)		//�ʒu�ւ̒Ǐ]�X�s�[�h

//====================================================================
//�R���X�g���N�^
//====================================================================
CCamera::CCamera()
{
	m_bBib = false;
	m_fBibPowor = 0.0f;
	m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	m_PlayerPos = INITVECTOR3;
	m_DelCameraPos = INITVECTOR3;
	ResetCamera();
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CCamera::~CCamera()
{

}

//====================================================================
//�J�����̏���������
//====================================================================
HRESULT CCamera::Init(void)
{
	return S_OK;
}

//====================================================================
//�J�����̏I������
//====================================================================
void CCamera::Uninit(void)
{

}

//====================================================================
//�J�����̍X�V����
//====================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#if _DEBUG
	if (m_rot.x <= D3DX_PI * 0.5f && m_rot.x >= -(D3DX_PI * 0.5f))
	{//����
		m_rotOld.x = m_rot.x;

		//�L�[�{�[�h
		if (pInputKeyboard->GetPress(DIK_I) == true)
		{
			m_rot.x += CAMERA_VR_SPEED;
		}
		if (pInputKeyboard->GetPress(DIK_K) == true)
		{
			m_rot.x -= CAMERA_VR_SPEED;
		}
	}

	if (fabsf(m_rot.x) > fabsf(D3DX_PI * 0.5f))
	{//����ɒB�������P�t���[���O��rot�ɂ��ǂ�
		m_rot.x = m_rotOld.x;
	}

	//�L�[�{�[�h
	if (pInputKeyboard->GetPress(DIK_J) == true)
	{
		m_rot.y -= CAMERA_VR_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_L) == true)
	{
		m_rot.y += CAMERA_VR_SPEED;
	}

	//����������̌����̕␳
	if (m_rot.y > D3DX_PI * 1.0f)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI * 1.0f)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}


	//�L�[�{�[�h
	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		m_posV.y += CAMERA_SPEED;
		m_posR.y += CAMERA_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_LCONTROL) == true)
	{
		m_posV.y -= CAMERA_SPEED;
		m_posR.y -= CAMERA_SPEED;
	}
	if (pInputKeyboard->GetPress(DIK_RSHIFT) == true)
	{
		m_posV.y += CAMERA_SPEED;
		m_posR.y += CAMERA_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_RCONTROL) == true)
	{
		m_posV.y -= CAMERA_SPEED;
		m_posR.y -= CAMERA_SPEED;
	}

	if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_CameraDistance -= 500.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		m_CameraDistance += 500.0f;
	}

	////�L�[�{�[�h
	//if (pInputKeyboard->GetPress(DIK_W) == true)
	//{
	//	m_posR.z += CAMERA_SPEED * cosf(m_rot.y);
	//	m_posR.x += CAMERA_SPEED * sinf(m_rot.y);

	//	m_posV.z += CAMERA_SPEED * cosf(m_rot.y);
	//	m_posV.x += CAMERA_SPEED * sinf(m_rot.y);

	//}
	//if (pInputKeyboard->GetPress(DIK_S) == true)
	//{
	//	m_posR.z += -CAMERA_SPEED * cosf(m_rot.y);
	//	m_posR.x += -CAMERA_SPEED * sinf(m_rot.y);

	//	m_posV.z += -CAMERA_SPEED * cosf(m_rot.y);
	//	m_posV.x += -CAMERA_SPEED * sinf(m_rot.y);
	//}
	//if (pInputKeyboard->GetPress(DIK_A) == true)
	//{
	//	m_posR.x += -CAMERA_SPEED * cosf(m_rot.y);
	//	m_posR.z -= -CAMERA_SPEED * sinf(m_rot.y);

	//	m_posV.x += -CAMERA_SPEED * cosf(m_rot.y);
	//	m_posV.z -= -CAMERA_SPEED * sinf(m_rot.y);
	//}
	//if (pInputKeyboard->GetPress(DIK_D) == true)
	//{
	//	m_posR.x += CAMERA_SPEED * cosf(m_rot.y);
	//	m_posR.z -= CAMERA_SPEED * sinf(m_rot.y);

	//	m_posV.x += CAMERA_SPEED * cosf(m_rot.y);
	//	m_posV.z -= CAMERA_SPEED * sinf(m_rot.y);
	//}
#endif

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{

	CPlayerLevel *pPlayer = CGame::GetPlayerLevel();

		if (pPlayer->GetState() == CPlayerLevel::STATE_NORMAL || pPlayer->GetState() == CPlayerLevel::STATE_NODAMAGE)
		{
			m_PlayerPos = pPlayer->GetPos();
			m_DelCameraPos = pPlayer->GetPos();

			//���_�̏����o�͂���
			m_posR.x = m_PlayerPos.x;
			m_posV.x = m_PlayerPos.x;

			m_posR.y = m_PlayerPos.y + 100.0f;
			m_posV.y = m_PlayerPos.y + 100.0f;

			//m_posR.y = 300.0f;
			//m_posV.y = m_posR.y + sinf(-m_rot.x) * m_CameraDistance;
			m_posV.z = m_posR.z + cosf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
		}
		else if (pPlayer->GetState() != CPlayerLevel::STATE_NORMAL)
		{
			D3DXVECTOR3 PlayerRePos = pPlayer->GetReSpownPos();

			m_DelCameraPos = m_DelCameraPos * POS_HOMING;

			//PlayerPos.x = PlayerPos.x + m_posR.x;
			//PlayerPos.y = PlayerPos.y + m_posR.y;

			float f = m_PlayerPos.x * (m_PlayerPos.x / m_posR.x);

			//���_�̏����o�͂���
			m_posR.x = PlayerRePos.x + (m_PlayerPos.x - PlayerRePos.x) * (m_DelCameraPos.x / m_PlayerPos.x);
			m_posV.x = PlayerRePos.x + (m_PlayerPos.x - PlayerRePos.x) * (m_DelCameraPos.x / m_PlayerPos.x);

			m_posR.y = PlayerRePos.y + (m_PlayerPos.y - PlayerRePos.y) * (m_DelCameraPos.y / m_PlayerPos.y);
			m_posV.y = PlayerRePos.y + (m_PlayerPos.y - PlayerRePos.y) * (m_DelCameraPos.y / m_PlayerPos.y);
			m_posV.z = m_posR.z + cosf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
		}

		if (CGame::GetBossEvent() == true)
		{
			//m_posR.x = 19500.0f;
			//m_posV.x = 19500.0f;

			//m_posR.y = 600.0f;
			//m_posV.y = 600.0f;

			m_CameraDistance = 900.0f;
		}

	}
	else if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_RESULT)
	{
		m_posR += m_move;

		//���_�̏����o�͂���
		m_posV.x = m_posR.x - 200.0f + sinf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance * 1.5f;
		m_posV.y = m_posR.y + sinf(-m_rot.x) * m_CameraDistance * 1.5f;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance * 1.5f;
	}
	else
	{
		//���_�̏����o�͂���
		m_posV.x = m_posR.x + sinf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
		m_posV.y = m_posR.y + sinf(-m_rot.x) * m_CameraDistance;
		m_posV.z = m_posR.z + cosf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
	}

	//if (m_bBib == true)
	//{
	//	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	//	m_fBibPowor += 0.4f;

	//	m_posR.y += (int)(sin(D3DX_PI * m_fBibPowor) * 10.0f);

	//	//���_�̏����o�͂���
	//	m_posV.x = m_posR.x + sinf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
	//	m_posV.y = m_posR.y + sinf(-m_rot.x) * m_CameraDistance + (int)(sin(D3DX_PI * m_fBibPowor) * 10.0f);
	//	m_posV.z = m_posR.z + cosf(m_rot.y) * -cosf(m_rot.x) * m_CameraDistance;
	//}

	if (CManager::GetInstance()->GetEdit() == true)
	{
		D3DXVECTOR3 Pos = CGame::GetEdit()->GetEditPos();

		if (m_CameraDistance < 1300.0f)
		{
			m_CameraDistance = 1300.0f;
		}

		//���_�̏����o�͂���
		m_posR.x = Pos.x;
		m_posV.x = Pos.x;

		m_posR.y = 500.0f;
		m_posV.y = 500.0f;
	}

	//�f�o�b�O�\���̎擾
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();
	pDebugProc->Print("%f:%f:%f\n", m_posV.x, m_posV.y, m_posV.z);
	pDebugProc->Print("%f:%f:%f\n", m_posR.x, m_posR.y, m_posR.z);

}

//====================================================================
//�J�����̐ݒ菈��
//====================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//====================================================================
//�J�����̐ݒ菈��
//====================================================================
void CCamera::ResetCamera(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CameraDistance = CAMERA_DISTANCE;
	m_EventPosY = 0.0f;

	if (CScene::MODE_GAME == CScene::GetMode())
	{
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}