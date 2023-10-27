//============================================
//
//	�}�b�v�̒��̃`�F�b�N�|�C���g [MapCheckPoint.cpp]
//	Author:sakamoto kai
//
//============================================
#include "MapCheckPoint.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "Map2D.h"
#include "Particle.h"
#include "PlayerLevel.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CMapCheckPoint::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CMapCheckPoint::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CMapCheckPoint::m_dwNumMat = NULL;				//�}�e���A���̐�
int CMapCheckPoint::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CMapCheckPoint::m_CollisionPos = INITVECTOR3;
bool CMapCheckPoint::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CMapCheckPoint::CMapCheckPoint(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CMapCheckPoint::~CMapCheckPoint()
{

}

//====================================================================
//��������
//====================================================================
CMapCheckPoint *CMapCheckPoint::Create()
{
	CMapCheckPoint *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CMapCheckPoint();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\CheckPoint.x");

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
HRESULT CMapCheckPoint::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_MAPCHECKPOINT);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CMapCheckPoint::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CMapCheckPoint::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	CollisionObject(pos);

	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CMapCheckPoint::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�e�̓����蔻�菈��
//====================================================================
bool CMapCheckPoint::CollisionObject(D3DXVECTOR3 pos)
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