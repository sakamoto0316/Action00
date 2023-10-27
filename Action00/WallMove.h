//============================================
//
//	�ړ����̕ǐ������� [WallMove.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _WALLMOVE_H_
#define _WALLMOVE_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CWallMove : public CObjectXtex
{
public:

	CWallMove(int nPriority = 3);
	~CWallMove();

	static CWallMove *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }

private:

	D3DXCOLOR m_BlockColor;
	float m_ColorA;
	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
	float m_fUpPos;							//�㏸��	
};
#endif