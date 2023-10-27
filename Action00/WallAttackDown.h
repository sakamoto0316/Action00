//============================================
//
//	�������ւ̕ǐ����U�� [WallAttackDown.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _WALLATTACKDOWN_H_
#define _WALLATTACKDOWN_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CWallAttackDown : public CObjectXtex
{
public:

	CWallAttackDown(int nPriority = 3);
	~CWallAttackDown();

	static CWallAttackDown *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }

private:
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//�I�u�W�F�N�g�Ƃ̓����蔻��

	D3DXCOLOR m_BlockColor;
	float m_ColorA;
	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�
	static D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	static bool m_bCollision;				//�����蔻��p�̍��W

	D3DXVECTOR3 m_posOld;					//�ߋ��̈ʒu	
	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
	float m_fUpPos;							//�㏸��	
};
#endif