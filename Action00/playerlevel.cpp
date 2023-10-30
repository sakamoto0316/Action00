//============================================
//
//	�v���C���[�̏��� [playerlevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "playerlevel.h"
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "sound.h"
#include "EMPManager.h"
#include "EffectMovePolygon.h"
#include "Effect.h"
#include "WallJump.h"
#include "WallMove.h"
#include "WallAttackSide.h"
#include "WallAttackDown.h"
#include "game.h"
#include "time.h"
#include "MapBlock.h"
#include "MapPitFloor.h"
#include "bosslevel.h"

#define PLAYER_SPEED (10.0f)		//�v���C���[�̑���
#define PLAYER_JAMPPOWER (15.0f)	//�v���C���[�̃W�����v��
#define PLAYER_JAMPWALL (4.0f)		//�W�����v�܂ł̗͂̐U�蕝
#define JAMP_ACTIONNOT (4)			//�W�����v����s���o����܂�
#define WIDTH_COLLISION (40.0f)		//���̓����蔻��
#define HEIGHT_COLLISION (180.0f)	//�c�̓����蔻��
#define BOSSEVENT_POS (19600.0f)	//�{�X�킪�n�܂���W

//====================================================================
//�R���X�g���N�^
//====================================================================
CPlayerLevel::CPlayerLevel()
{
	SetWight(WIDTH_COLLISION);
	SetHeight(HEIGHT_COLLISION * 0.5f);
	m_pos = INITVECTOR3;
	m_move = INITVECTOR3;
	m_rot = D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f);
	m_bWallJump = false;
	m_nJump = 2;
	m_nActionCount = 0;
	m_Action = ACTION_WAIT;
	m_nAttackCount = 0;
	m_bRight = true;
	m_State = STATE_NORMAL;
	m_nStateCount = 0;
	m_ReSpownPos = INITVECTOR3;
	m_GameEnd = false;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CPlayerLevel::~CPlayerLevel()
{

}

//====================================================================
//��������
//====================================================================
CPlayerLevel *CPlayerLevel::Create()
{
	CPlayerLevel *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�v���C���[�̐���
		pPlayer = new CPlayerLevel();
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
HRESULT CPlayerLevel::Init(void)
{
	//���f���̐���
	LoadLevelData("data\\TXT\\motion_WallKnight.txt");

	//���[�V�����̐���
	if (m_pMotion == NULL)
	{
		//���[�V�����̐���
		m_pMotion = new CMotion;
	}
	//����������
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_WallKnight.txt");

	SetType(CObject::TYPE_PLAYER3D);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CPlayerLevel::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_apModel[nCntModel]->Uninit();
		delete m_apModel[nCntModel];
		m_apModel[nCntModel] = NULL;
	}

	//���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CPlayerLevel::Update(void)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		//�L�[�{�[�h�̎擾
		CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		//�ߋ��̈ʒu���L�^����
		m_posOld = m_pos;

		//�����蔻���L���ɂ���
		m_bHit = false;

		//�d��
		m_move.y -= 0.98f;

		//�������x�����ȏ�ɂȂ����ꍇ�W�����v��s�\�ɂ���
		if (m_move.y < -5.0f)
		{
			if (m_nJump == 2)
			{
				m_nJump = 1;
			}
		}
		//�ړ�����
		Move();

		if (m_nJump == 2)
		{
			//�ړ���������
			Rot();
		}

		//�ǂ𐶐����čU��
		WallAttack();

		//�s���s�\���Ԃ̃J�E���g
		m_nActionNotCount--;

		if (m_bWallJump == true)
		{
			//�ǂ𐶐����ăW�����v
			WallJamp();
		}

		//�����W��
		m_move.x = m_move.x * 0.5f;
		if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
		{
			m_move.x = 0.0f;
		}

		//X���̈ʒu�X�V
		m_pos.x += m_move.x;

		//�����蔻��
		CollisionObject(&m_pos, true);
		CollisionBoss();

		//Y���̈ʒu�X�V
		m_pos.y += m_move.y;

		//�����蔻��
		CollisionObject(&m_pos, false);
		CollisionBoss();

		//Z���̈ʒu�X�V
		m_pos.z += m_move.z;

		//��ʊO����
		if (m_pos.y < 0.0f)
		{
			HitDamage();
		}

		EventManager();
	}

	//���[�V�����̊Ǘ�
	ActionState();

	//��Ԃ̊Ǘ�
	StateManager();

	//���[�V�����̍X�V
	m_pMotion->Update();
}

//====================================================================
//��ԊǗ�
//====================================================================
void CPlayerLevel::EventManager(void)
{
	if (m_pos.x >= BOSSEVENT_POS)
	{
		if (CGame::GetBossEvent() == false)
		{
			CGame::SetBossEvent(true);
			SetReSpownPos(D3DXVECTOR3(19550.0f, 850.0f, 0.0f));
			DeleteMap();

			for (int nCnt = 0; nCnt <= 12; nCnt++)
			{
				CMapBlock *pBlock = CMapBlock::Create();
				pBlock->SetPos(D3DXVECTOR3(18800.0f, 1200.0f + nCnt * -100.0f, 0.0f));
			}

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CMapPitFloor *pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19200.0f + nCnt * 900.0f, 600.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19200.0f + 100.0f + nCnt * 900.0f, 600.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19500.0f + nCnt * 300.0f, 700.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19500.0f + 100.0f + nCnt * 300.0f, 700.0f, 0.0f));
			}
		}
	}
}

//====================================================================
//��ԊǗ�
//====================================================================
void CPlayerLevel::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DEATH:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_WAIT;
			m_nStateCount = 60;
		}
		break;

	case STATE_WAIT:
		if (m_nStateCount <= 0)
		{
			if (CGame::GetBossEvent() == false)
			{
				m_State = STATE_NORMAL;
				m_nStateCount = 0;
			}
			else
			{
				m_State = STATE_NODAMAGE;
				m_nStateCount = 120;
				for (int nCnt = 0; nCnt < 64; nCnt++)
				{
					if (m_apModel[nCnt] != NULL)
					{
						m_apModel[nCnt]->SetColorChange(true);
						m_apModel[nCnt]->SetColor(D3DXCOLOR(0.9f, 0.3f, 0.0f, 0.5f));
					}
				}
			}
		}
		break;

	case STATE_NODAMAGE:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_NORMAL;
			m_nStateCount = 0;

			for (int nCnt = 0; nCnt < 64; nCnt++)
			{
				if (m_apModel[nCnt] != NULL)
				{
					m_apModel[nCnt]->SetColorChange(false);
				}
			}
		}
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//�ړ�����
//====================================================================
void CPlayerLevel::Move(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true) &&
		m_nJump != 0 &&
		(m_Action != ACTION_WALLATTACK)
		)
	{//�U��������Ȃ����ɃW�����v�{�^�����������Ƃ�

		//SE
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);
		
		if (m_nJump == 2)
		{
			//�W�����v�̋����J�n�ƃW�����v����
			m_bWallJump = true;

			//�W�����v���̕ǐ���
			CWallJump *pWallJump = CWallJump::Create();
			pWallJump->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 5.0f, m_pos.y - 70.0f, 0.0f));
		}
		else
		{
			m_pMotion->Set(ACTION_JAMP);
			m_move.y = PLAYER_JAMPPOWER * 0.75f;

			//�W�����v���̕ǐ���
			CWallAttackDown *pWallDown = CWallAttackDown::Create();
			pWallDown->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 5.0f, m_pos.y + 10.0f, 0.0f));
		}

		m_nJump--;

		//�W�����v����͍U���Ȃǂ̃A�N�V�������s���Ȃ�
		m_nActionNotCount = JAMP_ACTIONNOT;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true)
	{//���ړ��{�^�����������Ƃ�

		//�󒆂��Ɣw�������ւ̈ړ����x���Ȃ�
		if (m_nJump <= 1 && m_bRight == true)
		{
			m_move.x -= PLAYER_SPEED * 0.5f;
		}
		else
		{
			m_move.x -= PLAYER_SPEED;
		}

		//�ړ����̕ǐ����̊Ǘ�
		WallMoveManager();
	}

	if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true)
	{//�E�{�^�����������Ƃ�

		//�󒆂��Ɣw�������ւ̈ړ����x���Ȃ�
		if (m_nJump <= 1 && m_bRight == false)
		{
			m_move.x += PLAYER_SPEED * 0.5f;
		}
		else
		{
			m_move.x += PLAYER_SPEED;
		}

		//�ړ����̕ǐ����̊Ǘ�
		WallMoveManager();
	}

	if (pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_LEFT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == false &&
		pInputKeyboard->GetPress(DIK_D) == false &&
		pInputKeyboard->GetPress(DIK_RIGHT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == false)
	{//�ړ��{�^���̓��͂��Ȃ��ꍇ�̂݃X�e�B�b�N�ł̈ړ����󂯕t����
		m_move.x += pInputJoypad->Get_Stick_Left(0).x * PLAYER_SPEED;
	}
}

//====================================================================
//�ړ���������
//====================================================================
void CPlayerLevel::Rot(void)
{
	if (m_move.x > 0.1f)
	{
		m_rot.y = D3DX_PI * -0.5f;
		m_bRight = true;
	}
	else if (m_move.x < -0.1f)
	{
		m_rot.y = D3DX_PI * 0.5f;
		m_bRight = false;
	}
}

//====================================================================
//�U�����󂯂����̏���
//====================================================================
void CPlayerLevel::HitDamage(void)
{
	if (m_State == STATE_NORMAL)
	{
		CEffect *pEffect = CEffect::Create();
		pEffect->SetPos(m_pos);
		pEffect->SetRadius(500.0f);
		pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_State = STATE_DEATH;
		m_nStateCount = 1;
		m_pos = D3DXVECTOR3(m_ReSpownPos.x, m_ReSpownPos.y + -100.0f, m_ReSpownPos.z);
		m_move = INITVECTOR3;
		m_Action = ACTION_WAIT;
		m_nAttackCount = 0;
		m_pMotion->Set(ACTION_WAIT);
		CGame::AddDeathCount();
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
	}
}

//====================================================================
//���[�V�����Ə�Ԃ̊Ǘ�
//====================================================================
void CPlayerLevel::ActionState(void)
{
	//�U�����[�V����
	if (m_nAttackCount > 0)
	{
		if (m_Action != ACTION_WALLATTACK)
		{
			m_Action = ACTION_WALLATTACK;
			m_pMotion->Set(ACTION_WALLATTACK);
		}
	}
	//�W�����v���[�V����
	else if (m_nJump != 2)
	{
		if (m_Action != ACTION_JAMP)
		{
			m_Action = ACTION_JAMP;
			m_pMotion->Set(ACTION_JAMP);
		}
	}
	//�ړ����[�V����
	else if (m_move.x > 0.1f || m_move.x < -0.1f)
	{
		if (m_Action != ACTION_MOVE)
		{
			m_Action = ACTION_MOVE;
			m_pMotion->Set(ACTION_MOVE);
		}
	}
	//�j���[�g�������[�V����
	else
	{
		if (m_Action != ACTION_WAIT)
		{
			m_Action = ACTION_WAIT;
			m_pMotion->Set(ACTION_WAIT);
		}
	}
}

//====================================================================
//�ǂ𐶐����čU��
//====================================================================
void CPlayerLevel::WallAttack(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_B, 0) == true) &&
		m_nAttackCount <= 0 &&
		m_bAirAttack == false &&
		m_nActionNotCount <= 0
		)
	{
		m_nAttackCount = 25;
		m_bAirAttack = true;
	}

	if (m_nAttackCount > 0)
	{
		m_move.x *= 0.1f;
		m_move.y = 0.0f;
		m_bWallJump = false;
		m_nAttackCount--;
	}

	if (m_nAttackCount == 8)
	{
		CWallAttackSide *pWallAttack = CWallAttackSide::Create(m_bRight);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
		if (m_bRight == true)
		{
			pWallAttack->SetPos(D3DXVECTOR3(m_pos.x + 10.0f, m_pos.y, m_pos.z));
		}
		else
		{
			pWallAttack->SetPos(D3DXVECTOR3(m_pos.x - 10.0f, m_pos.y, m_pos.z));
		}
	}
}

//====================================================================
//�ǂ𐶐����ăW�����v
//====================================================================
void CPlayerLevel::WallJamp(void)
{
	if (m_move.y < PLAYER_JAMPPOWER)
	{
		m_move.y += PLAYER_JAMPWALL;
	}
	else
	{
		m_move.y = PLAYER_JAMPPOWER;
		m_bWallJump = false;
	}
}

//====================================================================
//�ǂ𐶐����Ĉړ�
//====================================================================
void CPlayerLevel::WallMoveManager(void)
{
	if (m_Action == ACTION_MOVE)
	{
		m_nWallMoveCount++;

		if (m_nWallMoveCount % 2 == 0)
		{
			int nRandZ = rand() % 50;
			int nRandRotZ = rand() % 31;

			CWallMove *pWallMove = CWallMove::Create();
			pWallMove->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 3.5f, m_pos.y - 20.0f, (float)nRandZ - 25.0f));
			if (m_bRight == true)
			{
				pWallMove->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * ((float)nRandRotZ * 0.01f), D3DX_PI * ((float)nRandRotZ * 0.01f)));
			}
			else
			{
				pWallMove->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -((float)nRandRotZ * 0.01f), D3DX_PI * -((float)nRandRotZ * 0.01f)));
			}
		}
	}
	
}

//====================================================================
//�ǂ𐶐����Ĉړ�
//====================================================================
void CPlayerLevel::SetReSpownPos(D3DXVECTOR3 pos)
{
	m_ReSpownPos = pos;

	CGame::GetTime()->SetTime(10);
	CGame::GetTime()->ReSetCount();
}

//====================================================================
//�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//====================================================================
bool CPlayerLevel::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (m_State != STATE_NODAMAGE)
			{
				if (type == TYPE_MAPBLOCK ||
					type == TYPE_MAPDOOR ||
					type == TYPE_MAPSWITCH ||
					type == TYPE_MAPSDOOR ||
					type == TYPE_MAPSSWITCH ||
					type == TYPE_MAPNEEDLE ||
					type == TYPE_MAPNEEDLELR ||
					type == TYPE_MAPNEEDLEUD ||
					type == TYPE_MAPPITFLOOR ||
					type == TYPE_MAPCANNON)
				{//��ނ��u���b�N�̎�

					if (pObj->CollisionPlayer(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, &m_bWallJump, &m_bHit, bX) == true)
					{
						m_nJump = 2;
						m_bAirAttack = false;
						m_move.y = 0.0f;

						return true;
					}

					if (m_bHit == true)
					{
						return true;
					}
				}
			}
			else
			{
				if (type == TYPE_MAPBLOCK ||
					type == TYPE_MAPPITFLOOR)
				{//��ނ��u���b�N�̎�

					if (pObj->CollisionPlayer(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, &m_bWallJump, &m_bHit, bX) == true)
					{
						m_nJump = 2;
						m_bAirAttack = false;
						m_move.y = 0.0f;

						return true;
					}

					if (m_bHit == true)
					{
						return true;
					}
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//�}�b�v�̍폜����
//====================================================================
void CPlayerLevel::DeleteMap(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPNEEDLEUD ||
				type == TYPE_MAPCANNON ||
				type == TYPE_MAPCHECKPOINT)
			{//��ނ��u���b�N�̎�

				D3DXVECTOR3 ObjPos = pObj->GetPos();

				if (ObjPos.x <= 18800.0f)
				{
					pObj->Uninit();
				}
			}
			else if (type == TYPE_MAPPITFLOOR)
			{
				pObj->Uninit();
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
void CPlayerLevel::CollisionBoss(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_BOSSLEVEL)
			{//��ނ��u���b�N�̎�

				CBossLevel *pBoss = (CBossLevel*)pObj;

				D3DXVECTOR3 ObjPos = pBoss->GetPos();
				float fSize = pBoss->GetWight();
				float myWight = GetWight();
				float myHeight = GetWight();

				if (pBoss->GetState() != CBossLevel::STATE_SPAWN)
				{
					if (m_pos.x + myWight > ObjPos.x - fSize * 0.5f &&
						m_pos.x - myWight < ObjPos.x + fSize * 0.5f &&
						m_pos.y + myHeight > ObjPos.y - fSize &&
						m_pos.y < ObjPos.y + fSize * 2
						)
					{
						HitDamage();
					}
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CPlayerLevel::Draw(void)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���f���̕`��(�S�p�[�c)
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			m_apModel[nCntModel]->Draw();
		}
	}
}

//====================================================================
//���[�h����
//====================================================================
void CPlayerLevel::LoadLevelData(const char *pFilename)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		int ModelParent = 0;
		D3DXVECTOR3 ModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ModelRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		char ModelName[128] = {};
		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//�S�~��
		char aMessage[128] = {};			//�X�^�[�g�ƃG���h�̃��b�Z�[�W
		char aBool[128] = {};				//bool�ϊ��p���b�Z�[�W

		// �ǂݍ��݊J�n-----------------------------------------------------
		while (1)
		{//�uSCRIPT�v��T��
			fscanf(pFile, "%s", &aMessage[0]);
			if (strcmp(&aMessage[0], "SCRIPT") == 0)
			{
				// ���f�����ǂݍ���-----------------------------------------------------
				while (1)
				{//�uNUM_MODEL�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_nNumModel);		//���f�����̐ݒ�
						break;
					}
				}

				//���f���t�@�C���̓ǂݍ���
				while (1)
				{//�uMODEL_FILENAME�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%s", &ModelName[0]);		//�ǂݍ��ރ��f���̃p�X���擾

						m_apModel[nCntModel] = CModel::Create(&ModelName[0]);
						nCntModel++;
					}
					if (nCntModel >= m_nNumModel)
					{
						nCntModel = 0;
						break;
					}
				}

				// �L�����N�^�[���ǂݍ���-----------------------------------------------------
				while (1)
				{//�uPARTSSET�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aMessage[0]);
							if (strcmp(&aMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//�C���f�b�N�X��ݒ�
							}
							if (strcmp(&aMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &ModelParent);	//�e���f���̃C���f�b�N�X��ݒ�

								if (ModelParent == -1)
								{
									m_apModel[nCntModel]->SetParent(NULL);
								}
								else
								{
									m_apModel[nCntModel]->SetParent(m_apModel[ModelParent]);
								}
							}
							if (strcmp(&aMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelPos.x);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &ModelPos.y);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &ModelPos.z);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�

								m_apModel[nCntModel]->SetPos(ModelPos);
								m_apModel[nCntModel]->SetStartPos(ModelPos);
							}
							if (strcmp(&aMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelRot.x);				////�����̏����ݒ�
								fscanf(pFile, "%f", &ModelRot.y);				////�����̏����ݒ�
								fscanf(pFile, "%f", &ModelRot.z);				////�����̏����ݒ�

								m_apModel[nCntModel]->SetRot(ModelRot);
								m_apModel[nCntModel]->SetStartRot(ModelRot);
							}
							if (strcmp(&aMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= m_nNumModel)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}