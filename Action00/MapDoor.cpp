//============================================
//
//	�}�b�v�̒��̃h�A [MapDoor.cpp]
//	Author:sakamoto kai
//
//============================================
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
#include "PlayerLevel.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define DOOR_RANGE (100.0f)			//�h�A�J���̐U�ꕝ

LPD3DXMESH CMapDoor::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CMapDoor::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CMapDoor::m_dwNumMat = NULL;				//�}�e���A���̐�
int CMapDoor::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CMapDoor::m_CollisionPos = INITVECTOR3;
bool CMapDoor::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CMapDoor::CMapDoor(D3DXVECTOR3 Pos, int nPriority) : CObjectXtex(nPriority)
{
	m_StartPos = Pos;
	m_bOpen = false;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CMapDoor::~CMapDoor()
{

}

//====================================================================
//��������
//====================================================================
CMapDoor *CMapDoor::Create(D3DXVECTOR3 Pos)
{
	CMapDoor *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CMapDoor(Pos);
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapDoor.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(m_CollisionPos.x);
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
HRESULT CMapDoor::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPDOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CMapDoor::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CMapDoor::Update(void)
{
	if (m_bOpen == true)
	{
		DoorOpen();
	}
	else
	{ 
		DoorClose();
	}

	CollisionObject(D3DXVECTOR3(m_StartPos.x + 100.0f, m_StartPos.y, m_StartPos.z));

	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�h�A���J���鏈��
//====================================================================
void CMapDoor::DoorOpen(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (pos.y < m_StartPos.y + DOOR_RANGE)
	{
		m_move.y += 0.2f;
		pos.y += m_move.y;
	}
	else
	{
		pos.y = m_StartPos.y + DOOR_RANGE;
		m_move.y = 0.0f;
	}

	SetPos(pos);
}

//====================================================================
//�h�A��߂鏈��
//====================================================================
void CMapDoor::DoorClose(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (pos.y > m_StartPos.y)
	{
		m_move.y -= 0.2f;
		pos.y += m_move.y;
	}
	else
	{
		pos.y = m_StartPos.y;
		m_move.y = 0.0f;
	}

	SetPos(pos);
}

//====================================================================
//�`�揈��
//====================================================================
void CMapDoor::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapDoor::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();

	if (
		(pPos->x + fWidth > mtPos.x - myWight &&
			pPosOld.x + fWidth <= mtPos.x - myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//������߂荞�񂾎�
		pPos->x = mtPos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
		pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���

		//��
		m_bOpen = true;
	}

	if (
		(pPos->x - fWidth < mtPos.x + myWight &&
			pPosOld.x - fWidth >= mtPos.x + myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//�E����߂荞�񂾎�
		pPos->x = mtPos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
		pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���

		//��
		m_bOpen = false;
	}

	return bOn;
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapDoor::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();

	if (
		(pPos->x + fWidth > mtPos.x - myWight &&
			pPosOld.x + fWidth <= mtPos.x - myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//������߂荞�񂾎�
		pPos->x = mtPos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
		pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
		*bHit = true;
	}

	if (
		(pPos->x - fWidth < mtPos.x + myWight &&
			pPosOld.x - fWidth >= mtPos.x + myWight) &&
		pPos->y + fHeight > mtPos.y - myHeight &&
		pPos->y < mtPos.y + myHeight
		)
	{//�E����߂荞�񂾎�
		pPos->x = mtPos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
		pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
		*bHit = true;
	}

	return bOn;
}

//====================================================================
//�e�̓����蔻�菈��
//====================================================================
bool CMapDoor::CollisionObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();				//��ނ��擾
			D3DXVECTOR3 CollsionPos = pObj->GetPos();			//�ʒu���擾
			float CollsionWight = pObj->GetWight() * 0.5f;		//�����擾
			float CollsionHeight = pObj->GetHeight() * 0.5f;	//�������擾
			float fmyWight = GetWight() * 0.5f;					//���S����̕�
			float fmyHeight = GetHeight() * 0.5f;				//���S����̍���

			if (type == TYPE_PLAYER3D)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					CPlayerLevel *pPlayer = (CPlayerLevel*)pObj;

					pPlayer->SetReSpownPos(D3DXVECTOR3(pos.x, pos.y + 55.0f, pos.z));

					return true;
				}
			}

			pObj = pObjNext;
		}
	}
	return false;
}