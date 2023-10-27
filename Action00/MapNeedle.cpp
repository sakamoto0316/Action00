//============================================
//
//	�㉺�ɍ�p����Ƃ� [MapNeedleUD.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapNeedle.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "playerlevel.h"
#include "Map2D.h"
#include "Particle.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CMapNeedle::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CMapNeedle::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CMapNeedle::m_dwNumMat = NULL;				//�}�e���A���̐�
int CMapNeedle::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CMapNeedle::m_CollisionPos = INITVECTOR3;
bool CMapNeedle::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CMapNeedle::CMapNeedle(D3DXVECTOR3 StartPos, int nPriority) : CObjectXtex(nPriority)
{
	m_StartPos = StartPos;
	m_bRotChange = true;
	m_fMoveWight = 300.0f;
	m_MoveSpeed = 0.005f;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CMapNeedle::~CMapNeedle()
{

}

//====================================================================
//��������
//====================================================================
CMapNeedle *CMapNeedle::Create(D3DXVECTOR3 StartPos)
{
	CMapNeedle *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CMapNeedle(StartPos);
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapNeedle.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pBlock->GetSize();
		m_bCollision = true;
	}
	pBlock->SetWight(m_CollisionPos.x * 0.5f);
	pBlock->SetHeight(m_CollisionPos.y * 0.5f);

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
HRESULT CMapNeedle::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPNEEDLE);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CMapNeedle::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CMapNeedle::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	m_move.x += m_MoveSpeed;

	if (m_bRotChange == false)
	{
		pos.x = m_StartPos.x + sinf(D3DX_PI * m_move.x) * m_fMoveWight;
	}
	else
	{
		pos.y = m_StartPos.y + sinf(D3DX_PI * m_move.x) * m_fMoveWight;
	}


	rot.x += 0.04f;
	rot.y += 0.04f;
	rot.z += 0.04f;

	if (CManager::GetInstance()->GetEdit() == true)
	{
		pos = m_StartPos;
	}

	if (pos.y <= 0.0f)
	{
		Uninit();
		return;
	}

	SetPos(pos);
	SetRot(rot);

	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CMapNeedle::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapNeedle::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight() * 1.5f;
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

			CGame::GetPlayerLevel()->HitDamage();
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

			CGame::GetPlayerLevel()->HitDamage();
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

			CGame::GetPlayerLevel()->HitDamage();
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

			CGame::GetPlayerLevel()->HitDamage();
		}
	}

	return bOn;
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapNeedle::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight() * 1.5f;
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
		}
	}

	return bOn;
}