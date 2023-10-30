//============================================
//
//	�}�b�v�̒��̃X�C�b�` [MapSwitch.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapSwitch.h"
#include "MapDoor.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"
#include "sound.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CMapSwitch::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CMapSwitch::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CMapSwitch::m_dwNumMat = NULL;				//�}�e���A���̐�
int CMapSwitch::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CMapSwitch::m_CollisionPos = INITVECTOR3;
bool CMapSwitch::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CMapSwitch::CMapSwitch(int nPriority) : CObjectXtex(nPriority)
{
	SwitchOn = false;
	SetTexOne(true);
	OnTime = 0;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CMapSwitch::~CMapSwitch()
{

}

//====================================================================
//��������
//====================================================================
CMapSwitch *CMapSwitch::Create()
{
	CMapSwitch *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CMapSwitch();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapSwitch.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(48.0f);
	pBlock->SetHeight(m_CollisionPos.y);

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pBlock->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pBlock;
}

//====================================================================
//����������
//====================================================================
HRESULT CMapSwitch::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPSWITCH);

	m_pDoor = CMapDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pDoor->SetType(CObject::TYPE_MAPSDOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CMapSwitch::Uninit(void)
{
	m_pDoor->Uninit();

	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CMapSwitch::Update(void)
{
	D3DXVECTOR3 Pos = GetPos();
	D3DXVECTOR3 Rot = GetRot();

	if (bSetDoor == false)
	{
		m_pDoor->SetStartPos(m_DoorPos);
		m_pDoor->SetPos(m_DoorPos);

		bSetDoor = true;
	}

	Rot.y += 0.02f;

	SetRot(Rot);

	if (SwitchOn == false)
	{
		CTexture *pTexture = CManager::GetInstance()->GetTexture();;
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
	}
	else
	{
		CTexture *pTexture = CManager::GetInstance()->GetTexture();;
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0_1.png");

		OnCountDown();
	}

	m_pDoor->SetOpen(SwitchOn);

	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�X�V����
//====================================================================
void CMapSwitch::OnCountDown(void)
{
	if (OnTime > 0)
	{
		OnTime--;
	}
	else
	{
		SwitchOn = false;
	}
}


//====================================================================
//�`�揈��
//====================================================================
void CMapSwitch::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapSwitch::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
				pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//�ォ��߂荞�񂾎�
			bOn = true;
			pPos->y = mtPos.y + myHeight;		//�u���b�N�̂����ɂ�������
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
				pPosOld.y <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//������߂荞�񂾎�
			*bJumpMove = false;
			pPos->y = mtPos.y - myHeight - fHeight;		//�u���b�N�̉��Ŏ~�߂�
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
				pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y  < mtPos.y + myHeight
			)
		{//������߂荞�񂾎�
			pPos->x = mtPos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//�E����߂荞�񂾎�
			pPos->x = mtPos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
		}
	}

	return bOn;
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapSwitch::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
				pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//�ォ��߂荞�񂾎�
			bOn = true;
			pPos->y = mtPos.y + myHeight;		//�u���b�N�̂����ɂ�������
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			//��
			if (SwitchOn == false)
			{
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
				SwitchOn = true;
			}
			OnTime = 120;
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
				pPosOld.y <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//������߂荞�񂾎�
			*bJumpMove = false;
			pPos->y = mtPos.y - myHeight - fHeight;		//�u���b�N�̉��Ŏ~�߂�
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
				pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y  < mtPos.y + myHeight
			)
		{//������߂荞�񂾎�
			pPos->x = mtPos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			//��
			SwitchOn = true;
			OnTime = 120;
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight  > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//�E����߂荞�񂾎�
			pPos->x = mtPos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;

			//��
			SwitchOn = true;
			OnTime = 120;
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);
		}
	}

	return bOn;
}