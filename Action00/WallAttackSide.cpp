//============================================
//
//	�������ւ̕ǐ����U�� [WallAttackSide.cpp]
//	Author:sakamoto kai
//
//============================================
#include "WallAttackSide.h"
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
#define WALL_UPEND (30.0f)		//�㏸�ʒu
#define MAX_LIFE (60)			//�����̍ő�l

LPD3DXMESH CWallAttackSide::m_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER CWallAttackSide::m_pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
DWORD CWallAttackSide::m_dwNumMat = NULL;					//�}�e���A���̐�
int CWallAttackSide::m_nIdxXModel = NULL;					//�}�e���A���̐�
D3DXVECTOR3 CWallAttackSide::m_CollisionPos = INITVECTOR3;
bool CWallAttackSide::m_bCollision = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CWallAttackSide::CWallAttackSide(bool bRight, int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

	m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);

	m_fUpPos = 0.0f;

	m_bRight = bRight;

	SetMatChange(true);

	if (m_bRight == true)
	{
		m_move.x = WALL_UPEND;
	}
	else
	{
		m_move.x = -WALL_UPEND;
	}

	m_bFall = false;
	m_bBreak = false;
	m_nLife = MAX_LIFE;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CWallAttackSide::~CWallAttackSide()
{

}

//====================================================================
//��������
//====================================================================
CWallAttackSide *CWallAttackSide::Create(bool bRight)
{
	CWallAttackSide *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CWallAttackSide(bRight);
	}

	//X�t�@�C���̊��蓖��
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	m_nIdxXModel = pXModel->Regist("data\\MODEL\\WallAttackSample.x");

	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	if (m_bCollision == false)
	{
		m_CollisionPos = pPlayer->GetSize();
		m_bCollision = true;
	}
	pPlayer->SetWight(m_CollisionPos.x);
	pPlayer->SetHeight(m_CollisionPos.y);

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
HRESULT CWallAttackSide::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_WALL);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CWallAttackSide::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CWallAttackSide::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;

	//�����W��
	m_move.x = m_move.x * 0.7f;

	//���x�����ȉ��ɂȂ�Ɠ������~�߂ė���������
	if (m_move.x > -0.01f && m_move.x < 0.01f)
	{
		m_move.x = 0.0f;

		m_bFall = true;
	}

	if (m_bFall == true)
	{
		m_move.y -= 0.5f;
	}

	//�ʒu���̍X�V
	pos.x += m_move.x;
	CollisionObject(&pos, true);

	//�ʒu���̍X�V
	pos.y += m_move.y;
	CollisionObject(&pos, false);

	SetPos(pos);

	//���_���̍X�V
	CObjectXtex::Update();

	if (m_bBreak == true)
	{
		if (m_nLife > 0)
		{
			m_nLife--;
		}
		else
		{
			Uninit();
		}
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CWallAttackSide::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}

//====================================================================
//�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
bool CWallAttackSide::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLEUD ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPPITFLOOR ||
				type == TYPE_MAPCANNON)
			{//��ނ��u���b�N�̎�
				bool bJampMove = true;
				bool Hit = false;
				D3DXVECTOR3 MoveOld = m_move;

				pObj->Collision(pos, m_posOld, &m_move, GetHeight(), GetWight() * 0.5f, &bJampMove, &Hit, bX);

				if (Hit == true)
				{
					if (MoveOld.y < -5.0f)
					{
						Uninit();
						return true;
					}
					else
					{
						m_bBreak = true;
					}
				}
			}
			else if (type == TYPE_BOSSLEVEL)
			{
				bool bJampMove = true;
				bool Hit = false;
				D3DXVECTOR3 MoveOld = m_move;

				pObj->Collision(pos, m_posOld, &m_move, GetHeight(), GetWight() * 0.5f, &bJampMove, &Hit, bX);

				if (Hit == true)
				{
					Uninit();
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}