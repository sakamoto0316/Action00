//============================================
//
//	�}�b�v�̒��̃`�F�b�N�|�C���g [MapCheckPoint.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPCHECKPOINT_H_
#define _MAPCHECKPOINT_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CMapCheckPoint : public CObjectXtex
{
public:

	CMapCheckPoint(int nPriority = 3);
	~CMapCheckPoint();

	static CMapCheckPoint *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionObject(D3DXVECTOR3 pos);	//�I�u�W�F�N�g�Ƃ̓����蔻��

private:
	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	static D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	static bool m_bCollision;		//�����蔻��p�̍��W
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
};
#endif