//============================================
//
//	�v���C���[�̏��� [playerlevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PLAYERLEVEL_H_
#define _PLAYERLEVEL_H_

#include "object.h"

//�O���錾
class CModel;
class CMotion;

//�I�u�W�F�N�g�v���C���[�N���X
class CPlayerLevel : public CObject
{
public:
	CPlayerLevel();
	~CPlayerLevel();

	//�v���C���[�̃��[�V����
	typedef enum
	{
		ACTION_WAIT = 0,
		ACTION_MOVE,
		ACTION_WALLATTACK,
		ACTION_JAMP,
		ACTION_MAX,

	}ACTION_TYPE;

	//�v���C���[�̃��[�V����
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DEATH,
		STATE_WAIT,
		STATE_NODAMAGE,
		STATE_MAX,
		
	}STATE;

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CPlayerLevel *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadLevelData(const char *pFilename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetWight(float Wight) { m_fWight = Wight; }
	float GetWight(void) { return m_fWight; }
	void SetHeight(float Height) { m_fHeight = Height; }
	float GetHeight(void) { return m_fHeight; }
	void SetReSpownPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetReSpownPos(void) { return m_ReSpownPos; }
	STATE GetState(void) { return m_State; }
	void HitDamage(void);								//�U�����󂯂����̏���

private:
	void EventManager(void);							//�Q�[�����C�x���g�̊Ǘ�
	void StateManager(void);							//��ԊǗ�
	void Move(void);									//�ړ�����
	void Rot(void);										//�ړ���������
	void ActionState(void);								//���[�V�����Ə�Ԃ̊Ǘ�
	void WallAttack(void);								//�ǂ𔭐������čU��
	void WallJamp(void);								//�ǂ𔭐������ăW�����v
	void WallMoveManager(void);							//�ړ����̊�G�t�F�N�g�̊Ǘ�
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	void CollisionBoss(void);							//�{�X�Ƃ̓����蔻��
	void DeleteMap(void);								//�}�b�v�̍폜
	
	ACTION_TYPE m_Action;
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_posOld;		//�ߋ��̈ʒu
	D3DXVECTOR3 m_ReSpownPos;	//�����n�_
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	bool m_bWallJump;			//�ǐ����W�����v
	bool m_bRight;				//�E������
	bool m_bAirAttack;			//�󒆂ōU�����������ǂ���
	int m_nJump;				//�W�����v�\�ȉ�
	int m_nActionCount;			//��Ԃ̃J�E���g
	int m_nAttackCount;			//�U���̃J�E���g
	int m_nWallMoveCount;		//�ړ��̃J�E���g
	int m_nActionNotCount;		//�s���s�\�̃J�E���g
	float m_fWight;				//��
	float m_fHeight;			//����
	STATE m_State;				//���
	int m_nStateCount;			//��ԊǗ��p�J�E���g
	bool m_bHit;				//�U��������������ǂ���
	bool m_GameEnd;				//�Q�[�����I��������ǂ���

	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;
};

#endif