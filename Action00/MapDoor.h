//============================================
//
//	�}�b�v�̒��̃h�A [MapDoor.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPDOOR_H_
#define _MAPDOOR_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
class CMapDoor : public CObjectXtex
{
public:

	CMapDoor(D3DXVECTOR3 Pos, int nPriority = 3);
	~CMapDoor();

	static CMapDoor *Create(D3DXVECTOR3 Pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool GetOpen(void) { return m_bOpen; }
	void SetOpen(bool Set) { m_bOpen = Set; }
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; }
	void SetStartPos(D3DXVECTOR3 Pos) { m_StartPos = Pos; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);
	bool CollisionObject(D3DXVECTOR3 pos);	//�I�u�W�F�N�g�Ƃ̓����蔻��

private:
	void DoorOpen(void);
	void DoorClose(void);

	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	static D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	static bool m_bCollision;				//�����蔻��p�̍��W
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_StartPos;					//�o�����̈ʒu	
	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
	bool m_bOpen;							//�h�A���J���Ă��邩�ǂ���
};
#endif