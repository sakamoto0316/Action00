//============================================
//
//	���S���̃u���b�N���o [BlockDeath.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BLOCKDEATH_H_
#define _BLOCKDEATH_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CBlockDeath : public CObjectXtex
{
public:

	CBlockDeath(int nPriority = 3);
	~CBlockDeath();

	static CBlockDeath *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
};
#endif