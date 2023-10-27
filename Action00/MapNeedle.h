//============================================
//
//	�Ƃ� [MapNeedle.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPNEEDLE_H_
#define _MAPNEEDLE_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CMapNeedle : public CObjectXtex
{
public:

	CMapNeedle(D3DXVECTOR3 StartPos,int nPriority = 0);
	~CMapNeedle();

	static CMapNeedle *Create(D3DXVECTOR3 StartPos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);
	void SetRotChange(bool bChange) { m_bRotChange = bChange; }
	bool GetRotChange(void) { return m_bRotChange; }
	void SetMoveSpeed(float fSpeed) { m_MoveSpeed = fSpeed; }
	float GetMoveSpeed(void) { return m_MoveSpeed; }
	void SetMoveWight(float fWight) { m_fMoveWight = fWight; }
	float GetMoveWight(void) { return m_fMoveWight; }

private:
	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	static D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	static bool m_bCollision;				//�����蔻��p�̍��W
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_StartPos;					//�J�n���̈ʒu	
	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
	float m_fMoveWight;						//�����_�܂ł̋���	
	bool m_bRotChange;						//�㉺���E�̌������	
	float m_MoveSpeed;						//�Ƃ��̈ړ��X�s�[�h	
};
#endif