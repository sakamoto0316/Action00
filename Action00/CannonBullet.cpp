//============================================
//
//	�}�b�v�̒��̑�C [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "CannonBullet.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "Map2D.h"
#include "Particle.h"
#include "Effect.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

LPD3DXMESH CCannonBullet::m_pMesh = NULL;			//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CCannonBullet::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CCannonBullet::m_dwNumMat = NULL;				//�}�e���A���̐�
int CCannonBullet::m_nIdxXModel = NULL;				//�}�e���A���̐�
D3DXVECTOR3 CCannonBullet::m_CollisionPos = INITVECTOR3;
bool CCannonBullet::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CCannonBullet::CCannonBullet(int nPriority) : CObjectXtex(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CCannonBullet::~CCannonBullet()
{

}

//====================================================================
//��������
//====================================================================
CCannonBullet *CCannonBullet::Create()
{
	CCannonBullet *pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CCannonBullet();
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\CannonBullet.x");

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
HRESULT CCannonBullet::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_CANNONBULLET);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CCannonBullet::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CCannonBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	pos += m_move;

	CollisionObject(pos);

	CEffect *pEffect = CEffect::Create();
	pEffect->SetPos(pos);
	pEffect->SetRadius(50.0f);
	pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pEffect->SetLife(500);
	pEffect->SetDel(10.0f);

	SetPos(pos);

	//���_���̍X�V
	CObjectXtex::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CCannonBullet::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//�e�̓����蔻�菈��
//====================================================================
bool CCannonBullet::CollisionObject(D3DXVECTOR3 pos)
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
			float CollsionHeight = pObj->GetHeight() * 0.5f;			//�������擾
			float fmyWight = GetWight() * 0.5f;					//���S����̕�
			float fmyHeight = GetHeight() * 0.5f;				//���S����̍���

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPNEEDLEUD)
			{//��ނ��}�b�v�I�u�W�F�N�g�̎�
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_WALL)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_PLAYER3D)
			{
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight * 2.0f)
				{
					pObj->HitDamage();

					Uninit();

					return true;
				}
			}

			pObj = pObjNext;
		}
	}
	return false;
}
