//============================================
//
//	�W�����v���̕ǐ������� [WallJump.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallJump.h"
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
#define BLOCK_WIGHT (40.0f)		//����
#define BLOCK_HEIGHT (40.0f)	//�c��
#define WALL_UPEND (30.0f)			//�㏸�ʒu

LPD3DXMESH CWallJump::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CWallJump::m_pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
DWORD CWallJump::m_dwNumMat = NULL;					//�}�e���A���̐�
int CWallJump::m_nIdxXModel = NULL;					//�}�e���A���̐�

//====================================================================
//�R���X�g���N�^
//====================================================================
CWallJump::CWallJump(int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;
	m_bUpEnd = false;

	SetMatChange(true);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CWallJump::~CWallJump()
{

}

//====================================================================
//��������
//====================================================================
CWallJump *CWallJump::Create()
{
	CWallJump *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CWallJump();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallJump.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CWallJump::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_WALLJUMP);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CWallJump::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CWallJump::Update(void)
{
	if (m_ColorA > 0.0f)
	{
		m_ColorA -= 0.01f;
	}
	m_BlockColor.a = m_ColorA;

	if (m_fUpPos < WALL_UPEND)
	{
		D3DXVECTOR3 pos = GetPos();

		pos.y += m_fUpPos;
		m_fUpPos += 5.0f;

		SetPos(pos);
	}

	if (m_bUpEnd == false)
	{
		CParticle::Create
		(
			D3DXVECTOR3(GetPos().x, GetPos().y + 75.0f, 0.0f),
			m_BlockColor,
			10,
			5.0f,
			4
		);

		m_bUpEnd = true;
	}

	//���_���̍X�V
	CObjectXtex::Update();

	if (m_ColorA < 0.0f)
	{
		Uninit();
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CWallJump::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}