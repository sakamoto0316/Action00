//============================================
//
//	�{�X�̏��� [bosslevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bosslevel.h"
#include "object.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "player3D.h"
#include "effect.h"
#include "playerlevel.h"
#include "CannonBullet.h"
#include "MapNeedle.h"
#include "MapNeedleUD.h"
#include "MapNeedleLR.h"
#include "MapCannon.h"
#include "Edit.h"

#define COLLISION_BOSS (50.0f) //�{�X�̓����蔻��

//====================================================================
//�R���X�g���N�^
//====================================================================
CBossLevel::CBossLevel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = COLLISION_BOSS;
	m_bHit = false;

	m_bRight = false;
	m_AttackCount = 0;
	m_bAttack = false;
	m_bJump = false;
	m_bBullet = false;
	m_bNeedle = false;
	m_BulletCount = 0;
	m_NeedleCount = 0;
	m_NeedleSet = 0;
	m_State = STATE_NORMAL;
	m_FallCount = 0;
	m_HitCount = 0;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CBossLevel::~CBossLevel()
{

}

//====================================================================
//��������
//====================================================================
CBossLevel *CBossLevel::Create()
{
	CBossLevel *pBoss = NULL;

	if (pBoss == NULL)
	{
		//�{�X�̐���
		pBoss = new CBossLevel();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pBoss->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pBoss;
}

//====================================================================
//����������
//====================================================================
HRESULT CBossLevel::Init(void)
{
	//�ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);

	//�����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���f���̐���
	LoadLevelData("data\\TXT\\motion_Boss.txt");

	//���[�V�����̐���
	if (m_pMotion == NULL)
	{
		//���[�V�����̐���
		m_pMotion = new CMotion;
	}
	//����������
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_Boss.txt");

	SetType(CObject::TYPE_BOSSLEVEL);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CBossLevel::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//�I������
//====================================================================
void CBossLevel::SetNULL(void)
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
}

//====================================================================
//�X�V����
//====================================================================
void CBossLevel::Update(void)
{
	//�ߋ��̈ʒu���L�^����
	m_posOld = m_pos;

	//�d��
	m_move.y -= 0.98f;

	//�����W��
	m_move.x = m_move.x * 0.5f;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	if (m_bJump == false)
	{
		Rot();
	}

	if (m_bJump == true)
	{
		D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();
		if (m_bRight == false)
		{
			if (m_bMiniJump == true)
			{
				m_move.x += -3.0f;
			}
			else
			{
				m_move.x += -7.5f;
			}
		}
		else
		{
			if (m_bMiniJump == true)
			{
				m_move.x += 3.0f;
			}
			else
			{
				m_move.x += 7.5f;
			}
		}
	}

	if (m_bRoundATK == true)
	{
		AtkNoDamage();
	}
	else
	{
		if (m_State == STATE_NORMAL)
		{
			//�U���p�^�[��
			AttackPattern();
		}
	}

	//�e�����U��
	if (m_bBullet == true)
	{
		SetBullet();
	}

	//�Ƃ������U��
	if (m_bNeedle == true)
	{
		SetNeedle();
	}

	//X���̈ʒu�X�V
	m_pos.x += m_move.x;

	//�����蔻��
	CollisionObject(&m_pos, true);

	//Y���̈ʒu�X�V
	m_pos.y += m_move.y;

	//�����蔻��
	CollisionObject(&m_pos, false);

	//Z���̈ʒu�X�V
	m_pos.z += m_move.z;

	if (m_pos.y <= -100.0f && m_State != STATE_WAIT)
	{
		m_State = STATE_WAIT;
		m_nStateCount = 120;
		m_FallCount++;
	}

	//��ԊǗ�
	StateManager();

	//���[�V�����̊Ǘ�
	if (m_MotionCount > 0)
	{
		m_MotionCount--;
		if (m_MotionCount == 0)
		{
			m_pMotion->Set(ACTION_WAIT1);
		}
	}

	//���[�V�����̍X�V
	m_pMotion->Update();
}

//====================================================================
//��ԊǗ�
//====================================================================
void CBossLevel::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DEATH:
		break;

	case STATE_WAIT:
		if (m_nStateCount <= 0)
		{
			if (m_FallCount == 3)
			{
				CGame::SetGameEnd(20);
				m_State = STATE_DEATH;
				CManager::GetInstance()->GetInstance()->SetEndScore(CGame::GetDeathCount());
			}
			else
			{
				m_State = STATE_SPAWN;
				m_nStateCount = 45;

				D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();
				m_pos = D3DXVECTOR3(PlayerPos.x, 300.0f, -650.0f);
				m_move = D3DXVECTOR3(0.0f, 40.0f, 0.0f);

				if (m_FallCount == 1)
				{
					CGame::GetEdit()->LoadData("data\\TXT\\BossRound1", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else if (m_FallCount == 2)
				{
					//�Ƃ��̐���
					for (int nCnt = 0; nCnt <= 2; nCnt++)
					{
						CMapNeedle *pNeedle = CMapNeedle::Create(D3DXVECTOR3(19100.0f + nCnt * 1200.0f, 600.0f, 0.0f));
						pNeedle->SetPos(D3DXVECTOR3(19100.0f + nCnt * 1200.0f, 600.0f, 0.0f));
						pNeedle->SetRotChange(true);
						pNeedle->SetMoveWight(300.0f);
						pNeedle->SetMoveSpeed(0.006f);
					}
				}
			}
		}
		break;

	case STATE_SPAWN:
		if (m_nStateCount <= 0)
		{
			m_nStateCount = 0;
			m_AttackCount = 0;
			m_bAttack = false;
			m_pos = D3DXVECTOR3(19700.0f, 900.0f, 0.0f);

			m_pMotion->Set(ACTION_JAMPATTACK);
			m_State = STATE_NODAMAGE;
			m_bRoundATK = true;
			m_nNoDamageCount = 600;
			m_MotionCount = 600;
		}
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//�U���p�^�[��
//====================================================================
void CBossLevel::AttackPattern(void)
{
	if (m_bAttack == false && m_MotionCount == 0)
	{
		m_AttackCount++;
		if (m_AttackCount >= 120)
		{
			m_bAttack = true;
			int nRandAttack = rand() % 101;
			

			if (m_HitCount >= 5)
			{
				if (nRandAttack >= 70)
				{
					AtkJump();
				}
				else if (nRandAttack >= 40)
				{
					AtkMiniJump();
				}
				else if (nRandAttack >= 20)
				{
					AtkBullet();
				}
				else
				{
					if (m_bNeedle == false)
					{
						AtkNeedle();
					}
					else
					{
						m_bAttack = false;
					}
				}

				m_HitCount = 0;
			}
			else
			{
				if (nRandAttack >= 90)
				{
					AtkJump();
				}
				else if (nRandAttack >= 80)
				{
					AtkMiniJump();
				}
				else if (nRandAttack >= 40)
				{
					AtkBullet();
				}
				else
				{
					if (m_bNeedle == false)
					{
						AtkNeedle();
					}
					else
					{
						m_bAttack = false;
					}
				}
			}
		}
	}
}

//====================================================================
//�W�����v�U��
//====================================================================
void CBossLevel::AtkMiniJump(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 15.0f;

	m_bMiniJump = true;
	m_bJump = true;
	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//�W�����v�U��
//====================================================================
void CBossLevel::AtkJump(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 20.0f;

	m_bJump = true;
	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//�ˌ��U��
//====================================================================
void CBossLevel::AtkBullet(void)
{
	m_pMotion->Set(ACTION_BULLETATTACK);
	m_MotionCount = 440;
	m_BulletCount = 441;
	m_bBullet = true;
}

//====================================================================
//�e�̐���
//====================================================================
void CBossLevel::SetBullet(void)
{
	if (m_BulletCount > 0)
	{
		m_BulletCount--;
		if (m_BulletCount <= 340 && m_BulletCount >= 50)
		{

			if (m_BulletCount % 80 == 0)
			{
				if (m_bRight == false)
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 70.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				}
				else
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 70.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
				}
			}

			if ((m_BulletCount + 40) % 80 == 0)
			{
				if (m_bRight == false)
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				}
				else
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
				}
			}
		}
		if (m_BulletCount == 0)
		{
			m_MotionCount = 0;
			m_bBullet = false;
			m_bAttack = false;
			m_AttackCount = 0;
		}
	}
}


//====================================================================
//�Ƃ��U��
//====================================================================
void CBossLevel::AtkNeedle(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 30.0f;
	m_bNeedle = true;
	m_fNeedleSet = m_pos.x;

	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//�Ƃ��̐���
//====================================================================
void CBossLevel::SetNeedle(void)
{
	m_NeedleCount++;

	if (m_NeedleCount >= 70)
	{
		CMapNeedle *pNeedle = CMapNeedle::Create(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * -300.0f, 400.0f, 0.0f));
		pNeedle->SetPos(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * -300.0f, 400.0f, 0.0f));
		pNeedle->SetRotChange(true);
		pNeedle->SetMoveWight(400.0f);
		pNeedle->SetMoveSpeed(0.006f);

		pNeedle = CMapNeedle::Create(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * 300.0f, 400.0f, 0.0f));
		pNeedle->SetPos(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * 300.0f, 400.0f, 0.0f));
		pNeedle->SetRotChange(true);
		pNeedle->SetMoveWight(400.0f);
		pNeedle->SetMoveSpeed(0.006f);

		m_NeedleCount = 0;
		m_NeedleSet++;

		if (m_NeedleSet >= 4)
		{
			m_NeedleSet = 0;
			m_bNeedle = false;
			m_bAttack = false;
			m_AttackCount = 0;
		}
	}
}

//====================================================================
//���G�U��
//====================================================================
void CBossLevel::AtkNoDamage(void)
{
	if (m_nNoDamageCount > 0)
	{
		m_nNoDamageCount--;

		D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();

		if (PlayerPos.x < m_pos.x - 10.0f)
		{
			m_move.x -= 2.0f;
		}
		else if(PlayerPos.x > m_pos.x + 10.0f)
		{
			m_move.x += 2.0f;
		}

		if (m_FallCount == 2)
		{
			if (m_nNoDamageCount % 80 == 0)
			{
				m_move.y = 23.0f;
			}
		}

		if (m_nNoDamageCount == 0)
		{
 			m_bRoundATK = false;
			m_pMotion->Set(ACTION_WAIT1);
			m_State = STATE_NORMAL;
		}
	}
}

//====================================================================
//�ړ�����
//====================================================================
void CBossLevel::Move(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();


	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true))
	{//�U��������Ȃ����ɃW�����v�{�^�����������Ƃ�


			m_move.y = 15.0f;

	}

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true)
	{//���ړ��{�^�����������Ƃ�
		m_move.x -= 10.0f;
	}

	if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true)
	{//�E�{�^�����������Ƃ�
		m_move.x += 10.0f;
	}
}

//====================================================================
//��������
//====================================================================
void CBossLevel::Rot(void)
{
	D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();

	if (PlayerPos.x < m_pos.x)
	{
		m_bRight = false;
		m_rot.y = 0.0f;
	}
	else
	{
		m_bRight = true;
		m_rot.y = 3.14f;
	}
}

//====================================================================
//�q�b�g����
//====================================================================
void CBossLevel::HitDamage(void)
{
	if (m_State == STATE_NORMAL)
	{
		m_pMotion->Set(ACTION_DAMAGE);
		m_MotionCount = 28;
		m_BulletCount = 0;
		m_HitCount++;
		m_bBullet = false;
		m_bAttack = false;
	}
}


//====================================================================
//�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//====================================================================
bool CBossLevel::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();			//��ނ��擾

				if (type == TYPE_MAPBLOCK)
				{//��ނ��u���b�N�̎�

					D3DXVECTOR3 Objpos = pObj->GetPos();
					float ObjWight = pObj->GetWight();
					float ObjHeight = pObj->GetHeight();

					if (bX == false)
					{
						if (
							(pos->y < Objpos.y + ObjHeight &&
								m_posOld.y >= Objpos.y + ObjHeight) &&
							pos->x + m_Size > Objpos.x - ObjWight &&
							pos->x - m_Size < Objpos.x + ObjWight
							)
						{//�ォ��߂荞�񂾎�
							pos->y = Objpos.y + ObjHeight;		//�u���b�N�̂����ɂ�������
							m_move.y = 0.0f;					//�ړ��ʂ��O�ɂ���
							m_bMiniJump = false;
							m_bJump = false;
						}

						if (
							(pos->y + m_Size > Objpos.y - ObjHeight &&
								m_posOld.y <= Objpos.y - ObjHeight) &&
							pos->x + m_Size > Objpos.x - ObjWight &&
							pos->x - m_Size < Objpos.x + ObjWight
							)
						{//������߂荞�񂾎�
							pos->y = Objpos.y - ObjHeight - m_Size;		//�u���b�N�̉��Ŏ~�߂�
							m_move.y = 0.0f;					//�ړ��ʂ��O�ɂ���
						}
					}
					else
					{
						if (
							(pos->x + m_Size > Objpos.x - ObjWight &&
								m_posOld.x + m_Size <= Objpos.x - ObjWight) &&
							pos->y + m_Size > Objpos.y - ObjHeight &&
							pos->y < Objpos.y + ObjHeight
							)
						{//������߂荞�񂾎�
							pos->x = Objpos.x - ObjWight - m_Size;		//�u���b�N�̍��Ŏ~�߂�
							m_move.x = 0.0f;					//�ړ��ʂ��O�ɂ���
						}

						if (
							(pos->x - m_Size < Objpos.x + ObjWight &&
								m_posOld.x - m_Size >= Objpos.x + ObjWight) &&
							pos->y + m_Size > Objpos.y - ObjHeight &&
							pos->y < Objpos.y + ObjHeight
							)
						{//�E����߂荞�񂾎�
							pos->x = Objpos.x + ObjWight + m_Size;		//�u���b�N�̉E�Ŏ~�߂�
							m_move.x = 0.0f;					//�ړ��ʂ��O�ɂ���
						}
					}
				}

				pObj = pObjNext;
			}
		}
	}
	return false;
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CBossLevel::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = m_Size;
	float myHeight = m_Size;


	if (bX == false)
	{
		if (
			(pPos->y < m_pos.y + myHeight &&
			pPosOld.y >= m_pos.y + myHeight) &&
			pPos->x + fWidth > m_pos.x - myWight &&
			pPos->x - fWidth < m_pos.x + myWight
			)
		{//�ォ��߂荞�񂾎�
			bOn = true;
			pPos->y = m_pos.y + myHeight;		//�u���b�N�̂����ɂ�������
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			HitDamage();
		}

		if (
			(pPos->y + fHeight > m_pos.y - myHeight &&
				pPosOld.y <= m_pos.y - myHeight) &&
			pPos->x + fWidth > m_pos.x - myWight &&
			pPos->x - fWidth < m_pos.x + myWight
			)
		{//������߂荞�񂾎�
			*bJumpMove = false;
			pPos->y = m_pos.y - myHeight - fHeight;		//�u���b�N�̉��Ŏ~�߂�
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > m_pos.x - myWight &&
				pPosOld.x + fWidth <= m_pos.x - myWight) &&
			pPos->y + fHeight  > m_pos.y - myHeight &&
			pPos->y  < m_pos.y + myHeight
			)
		{//������߂荞�񂾎�
			pPos->x = m_pos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			if (m_State != STATE_NODAMAGE)
			{
				m_move.x = 100.0f;
				m_move.y = 10.0f;
			}

			HitDamage();
		}

		if (
			(pPos->x - fWidth < m_pos.x + myWight &&
				pPosOld.x - fWidth >= m_pos.x + myWight) &&
			pPos->y + fHeight  > m_pos.y - myHeight &&
			pPos->y < m_pos.y + myHeight
			)
		{//�E����߂荞�񂾎�
			pPos->x = m_pos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			if (m_State != STATE_NODAMAGE)
			{
				m_move.x = -100.0f;
				m_move.y = 10.0f;
			}

			HitDamage();
		}
	}

	return bOn;
}

//====================================================================
//�`�揈��
//====================================================================
void CBossLevel::Draw(void)
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

//====================================================================
//�`�揈��
//====================================================================
void CBossLevel::LoadLevelData(const char *pFilename)
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