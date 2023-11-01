//============================================
//
//	���S���̃u���b�N���o [BlockDeath.cpp]
//	Author:sakamoto kai
//
//============================================
#include "BlockDeath.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"
#include "Particle.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CBlockDeath::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CBlockDeath::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CBlockDeath::m_dwNumMat = NULL;				//�}�e���A���̐�
int CBlockDeath::m_nIdxXModel = NULL;				//�}�e���A���̐�

//====================================================================
//�R���X�g���N�^
//====================================================================
CBlockDeath::CBlockDeath(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CBlockDeath::~CBlockDeath()
{

}

//====================================================================
//��������
//====================================================================
CBlockDeath *CBlockDeath::Create()
{
	CBlockDeath *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CBlockDeath();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\Block_Death.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CBlockDeath::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_EFFECT);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CBlockDeath::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CBlockDeath::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	//�d��
	m_move.y -= 0.98f;

	//�����W��
	m_move.x = m_move.x * 0.9f;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	//X���̈ʒu�X�V
	pos.x += m_move.x;

	//Y���̈ʒu�X�V
	pos.y += m_move.y;

	SetPos(pos);

	//���_���̍X�V
	CObjectXtex::Update();

	if (pos.y < 0.0f)
	{
		Uninit();
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CBlockDeath::Draw(void)
{
	CObjectXtex::Draw();
}