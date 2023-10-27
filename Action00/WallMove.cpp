//============================================
//
//	�ړ����̕ǐ������� [WallMove.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallMove.h"
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
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CWallMove::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CWallMove::m_pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
DWORD CWallMove::m_dwNumMat = NULL;					//�}�e���A���̐�
int CWallMove::m_nIdxXModel = NULL;					//�}�e���A���̐�

//====================================================================
//�R���X�g���N�^
//====================================================================
CWallMove::CWallMove(int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;

	SetMatChange(true);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CWallMove::~CWallMove()
{

}

//====================================================================
//��������
//====================================================================
CWallMove *CWallMove::Create()
{
	CWallMove *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CWallMove();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallMove.x");

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
HRESULT CWallMove::Init(void)
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
void CWallMove::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CWallMove::Update(void)
{
	if (m_ColorA > 0.0f)
	{
		m_ColorA -= 0.03f;
	}
	m_BlockColor.a = m_ColorA;

	if (m_fUpPos < WALL_UPEND)
	{
		D3DXVECTOR3 pos = GetPos();

		pos.y += m_fUpPos;
		m_fUpPos += 5.0f;

		SetPos(pos);
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
void CWallMove::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}