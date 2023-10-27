//============================================
//
//	�}�b�v�̒��̃X�C�b�` [MapSwitch.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPSWITCH_H_
#define _MAPSWITCH_H_

#include "main.h"
#include "objectXtex.h"

//�O���錾
class CMapDoor;

//�I�u�W�F�N�g�v���C���[�N���X
class CMapSwitch : public CObjectXtex
{
public:

	CMapSwitch(int nPriority = 3);
	~CMapSwitch();

	static CMapSwitch *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);

	CMapSwitch *GetSwitch(void) { return m_pSwitch; }
	CMapDoor *GetDoor(void) { return m_pDoor; }
	void SetDoorSwitch(D3DXVECTOR3 Pos) { m_SwitchPos = Pos; }
	void SetDoorPos(D3DXVECTOR3 Pos) { m_DoorPos = Pos; }

private:
	void OnCountDown(void);					//�I������I�t�ɂȂ�܂ł̃J�E���g

	static LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;				//�}�e���A���̐�
	static int m_nIdxXModel;				//X���f���̔ԍ�
	static D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	static bool m_bCollision;				//�����蔻��p�̍��W
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�

	CMapSwitch *m_pSwitch;					//�A������X�C�b�`
	D3DXVECTOR3 m_SwitchPos;				//�X�C�b�`�̍��W
	CMapDoor *m_pDoor;						//�A������h�A
	D3DXVECTOR3 m_DoorPos;					//�h�A�̍��W	
	D3DXVECTOR3 m_move;						//�ړ���	
	D3DXVECTOR3 m_rot;						//����	
	bool SwitchOn;							//�X�C�b�`���N�����Ă��邩�ǂ���
	int OnTime;								//�X�C�b�`�̋N������
	bool bSetDoor;							//�h�A��z�u�������ǂ���
};
#endif