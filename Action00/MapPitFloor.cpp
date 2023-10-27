//============================================
//
//	�}�b�v���̂��蔲���� [MapPitFloor.h]
//	Author:sakamoto kai
//
//============================================
#include "MapPitFloor.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"
#include "input.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CMapPitFloor::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CMapPitFloor::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CMapPitFloor::m_dwNumMat = NULL;				//�}�e���A���̐�
int CMapPitFloor::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CMapPitFloor::m_CollisionPos = INITVECTOR3;
bool CMapPitFloor::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CMapPitFloor::CMapPitFloor(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CMapPitFloor::~CMapPitFloor()
{

}

//====================================================================
//��������
//====================================================================
CMapPitFloor *CMapPitFloor::Create()
{
	CMapPitFloor *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CMapPitFloor();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\MapPtiFloor.x");

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
HRESULT CMapPitFloor::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPPITFLOOR);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CMapPitFloor::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CMapPitFloor::Update(void)
{
	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CMapPitFloor::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapPitFloor::CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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

		 //�L�[�{�[�h�̎擾
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
			CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

			if ((pInputKeyboard->GetPress(DIK_S) == false &&
				pInputKeyboard->GetPress(DIK_DOWN) == false &&
				pInputJoypad->GetPress(CInputJoypad::BUTTON_DOWN, 0) == false) &&
				0.01f > pInputJoypad->Get_Stick_Left(0).y)
			{
				bOn = true;
				pPos->y = mtPos.y + myHeight;		//�u���b�N�̂����ɂ�������
				pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
				*bHit = true;
			}
		}
	}

	return bOn;
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CMapPitFloor::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
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
		}
	}

	return bOn;
}