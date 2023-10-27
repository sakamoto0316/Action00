//============================================
//
//	�G�f�B�b�g [Edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Edit.h"
#include "object.h"
#include "MapBlock.h"
#include "renderer.h"
#include "break_block3D.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "debugproc.h"
#include "Map2D.h"
#include "MapNeedleUD.h"
#include "MapNeedleLR.h"
#include "MapDoor.h"
#include "MapSwitch.h"
#include "MapPitFloor.h"
#include "MapCannon.h"
#include "MapNeedle.h"
#include "MapCheckPoint.h"
#include "Effect.h"
#include "debugproc.h"

//�}�N����`
#define SPOWN_MAP (1000)
#define GAME_WIGHT (240.0f)					//��ʉ��̈ړ�����
#define NUM_OBJECT (8)						//�}�b�v�ɏo���I�u�W�F�N�g�̎�ސ�
#define START_OK ("STARTSETSTAGE")			//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F
#define END_SET_OK ("ENDSETSTAGE")			//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define BLOCK_SET ("STARTSETBLOCK")			//�u���b�N�̃Z�b�g���b�Z�[�W
#define NEEDLE_SET ("STARTSETNEEDLE")		//�Ƃ��̃Z�b�g���b�Z�[�W
#define NEEDLEUD_SET ("STARTSETNEEDLEUD")	//�㉺�Ƃ��̃Z�b�g���b�Z�[�W
#define NEEDLELR_SET ("STARTSETNEEDLELR")	//���E�Ƃ��̃Z�b�g���b�Z�[�W
#define DOOR_SET ("STARTSETDOOR")			//�h�A�̃Z�b�g���b�Z�[�W
#define SWITCH_SET ("STARTSETSWITCH")		//�X�C�b�`�̃Z�b�g���b�Z�[�W
#define PITFLOOR_SET ("STARTSETPITFLOOR")	//���蔲�����̃Z�b�g���b�Z�[�W
#define CANNON_SET ("STARTSETCANNON")		//��C�̃Z�b�g���b�Z�[�W
#define CHECKPOINT_SET ("STARTCHECKPOINT")	//�`�F�b�N�|�C���g�̃Z�b�g���b�Z�[�W
#define DELETE_WIGHT (45.0f)				//�폜�����̉��̍폜�͈�
#define DELETE_HEIGHT (45.0f)				//�폜�����̏c�̍폜�͈�
#define SIDE_PRESSCOUNT (30)				//���ɑf�����ړ�����܂ł̃J�E���g

//�ÓI�����o�ϐ��錾
CMapBlock *CEdit::m_EditBlock = NULL;			//�u���b�N�ւ̃|�C���^
CMapNeedle *CEdit::m_EditNeedle = NULL;			//���Ƃ��̃|�C���^
CMapNeedleUD *CEdit::m_EditNeedleUD = NULL;		//���Ƃ��̃|�C���^
CMapNeedleLR *CEdit::m_EditNeedleLR = NULL;		//�c�Ƃ��̃|�C���^
CMapDoor *CEdit::m_EditDoor = NULL;				//�h�A�ւ̃|�C���^
CMapSwitch *CEdit::m_EditSwitch = NULL;			//�X�C�b�`�ւ̃|�C���^
CMapPitFloor *CEdit::m_EditPitFloor = NULL;		//���蔲�����ւ̃|�C���^
CMapCannon *CEdit::m_EditCannon = NULL;			//��C�ւ̃|�C���^
CMapCheckPoint *CEdit::m_EditCheckPoint = NULL;	//�`�F�b�N�|�C���g�ւ̃|�C���^

//====================================================================
//�R���X�g���N�^
//====================================================================
CEdit::CEdit()
{
	m_EditPos = INITVECTOR3;
	m_EditPos2 = INITVECTOR3;

	m_HeightNumber = 0;					//�c�̔ԍ�

	ObjectType = 0;
	m_RotChange = false;
	m_RotSelecet = 0;
	m_fNeedleMoveWight = 100.0f;
	m_fNeedleMoveSpeed = 0.005f;
	m_nSideCount = 0;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CEdit::~CEdit()
{

}

//====================================================================
//��������
//====================================================================
CEdit *CEdit::Create()
{
	CEdit *pMap = NULL;

	if (pMap == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMap = new CEdit();
	}

	m_EditBlock = CMapBlock::Create();
	m_EditBlock->SetType(CObject::TYPE_EDIT);

	return pMap;
}

//====================================================================
//�I������
//====================================================================
void CEdit::Uninit(void)
{

}


//====================================================================
//�X�V����
//====================================================================
void CEdit::Update(void)
{
	CMapBlock *pEditBlock = NULL;
	CMapNeedle *pEditNeedle = NULL;
	CMapNeedleUD *pEditNeedleUD = NULL;
	CMapNeedleLR *pEditNeedleLR = NULL;
	CMapDoor *pEditDoor = NULL;
	CMapSwitch *pEditSwitch = NULL;
	CMapPitFloor *pEditPitFloor = NULL;
	CMapCannon *pEditCannon = NULL;
	CMapCheckPoint *pEditCheckPoint = NULL;

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�G�f�B�b�g�̈ʒu�𓮂���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		m_EditPos.y += 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		m_EditPos.y -= 100.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_EditPos.x -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_EditPos.x += 100.0f;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x -= 100.0f;
		}
		m_nSideCount++;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x += 100.0f;
		}
		m_nSideCount++;
	}

	if (pInputKeyboard->GetRerease(DIK_A) == true ||
		pInputKeyboard->GetRerease(DIK_D) == true)
	{
		m_nSideCount = 0;
	}

	//�G�f�B�b�g�̈ʒu�𓮂���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		m_EditPos2.y += 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		m_EditPos2.y -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		m_EditPos2.x -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		m_EditPos2.x += 100.0f;
	}

	//�I�u�W�F�N�g�؂�ւ�----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		switch (ObjectType)
		{
		case 0://�u���b�N
			m_EditBlock->Uninit();
			m_EditBlock = NULL;

			m_EditNeedleUD = CMapNeedleUD::Create(m_RotChange);
			m_EditNeedleUD->SetType(CObject::TYPE_EDIT);
			break;

		case 1://�㉺�Ƃ�
			m_EditNeedleUD->Uninit();
			m_EditNeedleUD = NULL;

			m_EditNeedleLR = CMapNeedleLR::Create(m_RotChange);
			m_EditNeedleLR->SetType(CObject::TYPE_EDIT);
			break;

		case 2://���E�Ƃ�
			m_EditNeedleLR->Uninit();
			m_EditNeedleLR = NULL;

			m_EditDoor = CMapDoor::Create(m_EditPos);
			m_EditDoor->SetType(CObject::TYPE_EDIT);
			break;

		case 3://�h�A
			m_EditDoor->Uninit();
			m_EditDoor = NULL;

			m_EditSwitch = CMapSwitch::Create();
			m_EditSwitch->SetType(CObject::TYPE_EDIT);
			break;

		case 4://�X�C�b�`
			m_EditSwitch->Uninit();
			m_EditSwitch = NULL;

			m_EditPitFloor = CMapPitFloor::Create();
			m_EditPitFloor->SetType(CObject::TYPE_EDIT);
			break;

		case 5://���蔲����
			m_EditPitFloor->Uninit();
			m_EditPitFloor = NULL;

			m_EditCannon = CMapCannon::Create();
			m_EditCannon->SetType(CObject::TYPE_EDIT);
			break;

		case 6://��C
			m_EditCannon->Uninit();
			m_EditCannon = NULL;

			m_EditNeedle = CMapNeedle::Create(INITVECTOR3);
			m_EditNeedle->SetType(CObject::TYPE_EDIT);
			break;

		case 7://�Ƃ�
			m_EditNeedle->Uninit();
			m_EditNeedle = NULL;

			m_EditCheckPoint = CMapCheckPoint::Create();
			m_EditCheckPoint->SetType(CObject::TYPE_EDIT);
			break;

		case 8://�`�F�b�N�|�C���g
			m_EditCheckPoint->Uninit();
			m_EditCheckPoint = NULL;

			m_EditBlock = CMapBlock::Create();
			m_EditBlock->SetType(CObject::TYPE_EDIT);
			break;

		default:
			break;
		}

		ObjectType++;

		if (ObjectType > NUM_OBJECT)
		{
			ObjectType = 0;
		}
	}

	//�����ƈʒu�̐؂�ւ�----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_9) == true)
	{
		m_RotChange = m_RotChange ? false : true;

		m_RotSelecet++;

		if (m_RotSelecet == 4)
		{
			m_RotSelecet = 0;
		}
	}

	//�Ƃ��̈ړ��͈͒���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_8) == true)
	{
		m_fNeedleMoveWight += 50.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{
		m_fNeedleMoveWight -= 50.0f;
	}

	//�ʒu�X�V----------------------------------------------------------
	switch (ObjectType)
	{
	case 0://�u���b�N
		m_EditBlock->SetPos(m_EditPos);
		break;

	case 1://�㉺�Ƃ�
		if (m_RotChange == false)
		{
			m_EditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_EditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
		}
		else
		{
			m_EditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
			m_EditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + 50.0f, m_EditPos.z));
		}
		break;

	case 2://���E�Ƃ�
		if (m_RotChange == false)
		{
			m_EditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_EditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x + 50.0f, m_EditPos.y, m_EditPos.z));
		}
		else
		{
			m_EditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
			m_EditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x - 50.0f, m_EditPos.y, m_EditPos.z));
		}
		break;

	case 3://�h�A
		m_EditDoor->SetPos(m_EditPos);
		break;

	case 4://�X�C�b�`
		m_EditSwitch->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
		m_EditSwitch->GetDoor()->SetPos(m_EditPos2);
		break;

	case 5://���蔲����
		m_EditPitFloor->SetPos(m_EditPos);
		break;

	case 6://��C
		m_EditCannon->SetPos(m_EditPos);

		if (m_RotSelecet == 0)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.0f));
		}
		else if (m_RotSelecet == 1)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f));
		}
		else if (m_RotSelecet == 2)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 1.0f));
		}
		else if (m_RotSelecet == 3)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));
		}
		break;

	case 7://�Ƃ�
		m_EditNeedle->SetPos(m_EditPos);

		if (m_RotChange == false)
		{
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CEffect *pEffect = CEffect::Create();
				pEffect->SetPos(D3DXVECTOR3(m_EditPos.x + m_fNeedleMoveWight * ((nCnt * 2) - 1), m_EditPos.y, m_EditPos.z));
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CEffect *pEffect = CEffect::Create();
				pEffect->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + m_fNeedleMoveWight * ((nCnt * 2) - 1), m_EditPos.z));
			}
		}
		break;

	case 8://�`�F�b�N�|�C���g
		m_EditCheckPoint->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y, m_EditPos.z));
		break;

	default:
		break;
	}

	//�I�u�W�F�N�g�ݒu----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		for (int nCnt = 0; nCnt < 19; nCnt++)
		{
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(D3DXVECTOR3(-900.0f + nCnt * 100.0f, 0.0f, 0.0f));
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(D3DXVECTOR3(-900.0f + nCnt * 100.0f, 1000.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		switch (ObjectType)
		{
		case 0://�u���b�N
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(m_EditPos);
			break;

		case 1://�㉺�Ƃ�
			pEditNeedleUD = CMapNeedleUD::Create(m_RotChange);

			if (m_RotChange == false)
			{
				pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pEditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
			}
			else
			{
				pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
				pEditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + 50.0f, m_EditPos.z));
			}
			break;

		case 2://���E�Ƃ�
			pEditNeedleLR = CMapNeedleLR::Create(m_RotChange);

			if (m_RotChange == false)
			{
				pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pEditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x + 50.0f, m_EditPos.y, m_EditPos.z));
			}
			else
			{
				pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
				pEditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x - 50.0f, m_EditPos.y, m_EditPos.z));
			}
			break;

		case 3://�h�A
			pEditDoor = CMapDoor::Create(m_EditPos);
			pEditDoor->SetPos(m_EditPos);
			break;

		case 4://�X�C�b�`
			pEditSwitch = CMapSwitch::Create();
			pEditSwitch->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
			pEditSwitch->GetDoor()->SetPos(m_EditPos2);
			pEditSwitch->SetDoorPos(m_EditPos2);
			break;

		case 5://���蔲����
			pEditPitFloor = CMapPitFloor::Create();
			pEditPitFloor->SetPos(m_EditPos);
			break;

		case 6://��C
			pEditCannon = CMapCannon::Create();
			pEditCannon->SetPos(m_EditPos);
			if (m_RotSelecet == 0)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.0f));
			}
			else if (m_RotSelecet == 1)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f));
			}
			else if (m_RotSelecet == 2)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 1.0f));
			}
			else if (m_RotSelecet == 3)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));
			}
			break;

		case 7://�Ƃ�
			pEditNeedle = CMapNeedle::Create(m_EditPos);
			pEditNeedle->SetPos(D3DXVECTOR3(m_EditPos));
			pEditNeedle->SetRotChange(m_RotChange);
			pEditNeedle->SetMoveWight(m_fNeedleMoveWight);
			pEditNeedle->SetMoveSpeed(m_fNeedleMoveSpeed);
			break;

		case 8://�`�F�b�N�|�C���g
			pEditCheckPoint = CMapCheckPoint::Create();
			pEditCheckPoint->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y, m_EditPos.z + 50.0f));
			break;

		default:
			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		DeleteObject(m_EditPos);
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}

	DebugObject();
}

//====================================================================
//�폜����
//====================================================================
void CEdit::DeleteObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == CObject::TYPE_MAPBLOCK ||
				type == CObject::TYPE_MAPDOOR ||
				type == CObject::TYPE_MAPSWITCH ||
				type == CObject::TYPE_MAPNEEDLE ||
				type == CObject::TYPE_MAPNEEDLELR ||
				type == CObject::TYPE_MAPNEEDLEUD ||
				type == CObject::TYPE_MAPPITFLOOR ||
				type == CObject::TYPE_MAPCANNON ||
				type == CObject::TYPE_MAPCHECKPOINT)
			{//��ނ��u���b�N�̎�

				CObject::TYPE type = pObj->GetType();				//��ނ��擾
				D3DXVECTOR3 CollsionPos = pObj->GetPos();			//�ʒu���擾
				float CollsionWight = pObj->GetWight() * 0.5f;		//�����擾
				float CollsionHeight = pObj->GetHeight() * 0.5f;	//�������擾
				float fmyWight = DELETE_WIGHT;						//���S����̕�
				float fmyHeight = DELETE_HEIGHT;					//���S����̍���

				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					pObj->Uninit();
				}

			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�f�o�b�O�\��
//====================================================================
void CEdit::DebugObject(void)
{
	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "�[�[�[�[�[�G�f�B�b�g���[�h�[�[�[�[�[");

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "��������[�[");
	//�������
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�ړ��F[W],[A],[S],[D]");
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�؂�ւ��F[�O]");
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g��]�F[�X]");

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "�[�[�G�f�B�b�g���[�[");
	//�I�u�W�F�N�g
	switch (ObjectType)
	{
	case 0://�u���b�N
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�u���b�N]");
		break;

	case 1://�㉺�Ƃ�
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�㉺�Ƃ�]");
		break;

	case 2://���E�Ƃ�
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[���E�Ƃ�]");
		break;

	case 3://�h�A
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�h�A]");
		break;

	case 4://�X�C�b�`
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�X�C�b�`]");
		break;

	case 5://���蔲����
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[���蔲����]");
		break;

	case 6://��C
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[��C]");
		break;

	case 7://�Ƃ�
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�Ƃ�]");
		break;

	case 8://�`�F�b�N�|�C���g
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g�F[�`�F�b�N�|�C���g]");
		break;
	}

	//���]�I���I�t
	if (m_RotChange == false)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "���]�F[OFF]");
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "���]�F[ON]");
	}

	//�㉺���E�̌���
	if (m_RotSelecet == 0)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�����F[��]");
	}
	else if (m_RotSelecet == 1)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�����F[��]");
	}
	else if (m_RotSelecet == 2)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�����F[�E]");
	}
	else if (m_RotSelecet == 3)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "�����F[��]");
	}

	//�Ƃ��̈ړ��͈�
	CManager::GetInstance()->GetDebugProc()->Print("�Ƃ��̈ړ��͈�:[%f]\n",m_fNeedleMoveWight);

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "�[�[�[�[�[�G�f�B�b�g���[�h�[�[�[�[�[");
}

//====================================================================
//�ۑ�����
//====================================================================
void CEdit::SaveData(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(DATA_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�X�e�[�W���Z�[�u����J�n�̍��}
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//��ނ��擾

				if (type == CObject::TYPE_MAPBLOCK)
				{//��ނ��u���b�N�̎�
					CMapBlock *m_pBlock = (CMapBlock*)pObj;

					fprintf(pFile, "%s\n", BLOCK_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pBlock->GetPos().x);
					fprintf(pFile, "%f ", m_pBlock->GetPos().y);
					fprintf(pFile, "%f\n", m_pBlock->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
				}
				else if (type == CObject::TYPE_MAPNEEDLE)
				{
					CMapNeedle *m_pNeedle = (CMapNeedle*)pObj;

					fprintf(pFile, "%s\n", NEEDLE_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pNeedle->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedle->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedle->GetPos().z);
					if (m_pNeedle->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%f\n", m_pNeedle->GetMoveWight());
					fprintf(pFile, "%f\n", m_pNeedle->GetMoveSpeed());

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLE");
				}
				else if (type == CObject::TYPE_MAPNEEDLEUD)
				{
					CMapNeedleUD *m_pNeedleUD = (CMapNeedleUD*)pObj;

					fprintf(pFile, "%s\n", NEEDLEUD_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pNeedleUD->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedleUD->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedleUD->GetPos().z);
					if (m_pNeedleUD->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLEUD");
				}
				else if (type == CObject::TYPE_MAPNEEDLELR)
				{
					CMapNeedleLR *m_pNeedleLR = (CMapNeedleLR*)pObj;

					fprintf(pFile, "%s\n", NEEDLELR_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pNeedleLR->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedleLR->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedleLR->GetPos().z);
					if (m_pNeedleLR->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLELR");
				}
				else if (type == CObject::TYPE_MAPDOOR)
				{
					CMapDoor *m_pMapdoor = (CMapDoor*)pObj;

					fprintf(pFile, "%s\n", DOOR_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pMapdoor->GetPos().x);
					fprintf(pFile, "%f ", m_pMapdoor->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapdoor->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETDOOR");
				}
				else if (type == CObject::TYPE_MAPSWITCH)
				{
					CMapSwitch *m_pMapSwitch = (CMapSwitch*)pObj;

					fprintf(pFile, "%s\n", SWITCH_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pMapSwitch->GetPos().x);
					fprintf(pFile, "%f ", m_pMapSwitch->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapSwitch->GetPos().z);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pMapSwitch->GetDoor()->GetPos().x);
					fprintf(pFile, "%f ", m_pMapSwitch->GetDoor()->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapSwitch->GetDoor()->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETSWITCH");
				}
				else if (type == CObject::TYPE_MAPPITFLOOR)
				{
					CMapPitFloor *m_pMapPitFloor = (CMapPitFloor*)pObj;

					fprintf(pFile, "%s\n", PITFLOOR_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pMapPitFloor->GetPos().x);
					fprintf(pFile, "%f ", m_pMapPitFloor->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapPitFloor->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETPITFLOOR");
				}
				else if (type == CObject::TYPE_MAPCANNON)
				{
					CMapCannon *m_pMapCannon = (CMapCannon*)pObj;

					fprintf(pFile, "%s\n", CANNON_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pMapCannon->GetPos().x);
					fprintf(pFile, "%f ", m_pMapCannon->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapCannon->GetPos().z);

					fprintf(pFile, "%f ", m_pMapCannon->GetRot().x);
					fprintf(pFile, "%f ", m_pMapCannon->GetRot().y);
					fprintf(pFile, "%f\n", m_pMapCannon->GetRot().z);

					fprintf(pFile, "%s\n\n", "ENDSETCANNON");
				}
				else if (type == CObject::TYPE_MAPCHECKPOINT)
				{
					CMapCheckPoint *m_pCheckPoint = (CMapCheckPoint*)pObj;

					fprintf(pFile, "%s\n", CHECKPOINT_SET);

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "%f ", m_pCheckPoint->GetPos().x);
					fprintf(pFile, "%f ", m_pCheckPoint->GetPos().y);
					fprintf(pFile, "%f\n", m_pCheckPoint->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETCHECKPOINT");
				}

				pObj = pObjNext;
			}
		}

		//�X�e�[�W���Z�[�u�����I���̍��}
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//====================================================================
//�}�b�v��S�Ė��߂Đ���
//====================================================================
void CEdit::LoadData(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		CMapBlock *pEditBlock = NULL;
		CMapNeedle *pEditNeedle = NULL;
		CMapNeedleUD *pEditNeedleUD = NULL;
		CMapNeedleLR *pEditNeedleLR = NULL;
		CMapDoor *pEditDoor = NULL;
		CMapSwitch *pEditSwitch = NULL;
		CMapPitFloor *pEditPitFloor = NULL;
		CMapCannon *pEditCannon = NULL;
		CMapCheckPoint *pEditCheckPoint = NULL;
		
		D3DXVECTOR3 SetPos = INITVECTOR3;
		D3DXVECTOR3 SetPos2 = INITVECTOR3;
		D3DXVECTOR3 SetRot = INITVECTOR3;
		int SetChangeRot = false;
		float SetMoveWight = 0.0f;
		float SetMoveSpeed = 0.0f;
		char aString[128] = {};			//�S�~��
		char aStartMessage[32] = {};	//�X�^�[�g���b�Z�[�W
		char aSetMessage[32] = {};		//�Z�b�g���b�Z�[�W
		char aEndMessage[32] = {};		//�I�����b�Z�[�W
		char aType[32] = {};			//��ޔ��ʃ��b�Z�[�W

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
				else if (strcmp(&aSetMessage[0], BLOCK_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditBlock = CMapBlock::Create();
					pEditBlock->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], NEEDLE_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%f", &SetMoveWight);
					fscanf(pFile, "%f", &SetMoveSpeed);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedle = CMapNeedle::Create(pos + SetPos);
					pEditNeedle->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedle->SetRotChange(true);
					}
					else
					{
						pEditNeedle->SetRotChange(false);
					}
					pEditNeedle->SetMoveWight(SetMoveWight);
					pEditNeedle->SetMoveSpeed(SetMoveSpeed);
				}
				else if (strcmp(&aSetMessage[0], NEEDLEUD_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedleUD = CMapNeedleUD::Create(false);
					pEditNeedleUD->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
						pEditNeedleUD->SetRotChange(true);
					}
				}
				else if (strcmp(&aSetMessage[0], NEEDLELR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedleLR = CMapNeedleLR::Create(false);
					pEditNeedleLR->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
						pEditNeedleLR->SetRotChange(true);
					}
				}
				else if (strcmp(&aSetMessage[0], DOOR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditDoor = CMapDoor::Create(D3DXVECTOR3(pos + SetPos));
					pEditDoor->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], SWITCH_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%f", &SetPos2.x);
					fscanf(pFile, "%f", &SetPos2.y);
					fscanf(pFile, "%f", &SetPos2.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditSwitch = CMapSwitch::Create();
					pEditSwitch->SetPos(D3DXVECTOR3(pos + SetPos));
					pEditSwitch->SetDoorPos(pos + SetPos2);
				}
				else if (strcmp(&aSetMessage[0], PITFLOOR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditPitFloor = CMapPitFloor::Create();
					pEditPitFloor->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], CANNON_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);

					fscanf(pFile, "%f", &SetRot.x);
					fscanf(pFile, "%f", &SetRot.y);
					fscanf(pFile, "%f", &SetRot.z);

					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditCannon = CMapCannon::Create();
					pEditCannon->SetPos(D3DXVECTOR3(pos + SetPos));
					pEditCannon->SetRot(D3DXVECTOR3(SetRot));
				}
				else if (strcmp(&aSetMessage[0], CHECKPOINT_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);

					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditCheckPoint = CMapCheckPoint::Create();
					pEditCheckPoint->SetPos(D3DXVECTOR3(pos + SetPos));
				}
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}