//============================================
//
//	�{�X�̏��� [bosslevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BOSSLEVEL_H_
#define _BOSSLEVEL_H_

#include "object.h"

//�O���錾
class CModel;
class CMotion;
class CObject2D; 
class CLifeGauge;

//�I�u�W�F�N�g�v���C���[�N���X
class CBossLevel : public CObject
{
public:
	CBossLevel();
	~CBossLevel();

	//�{�X�̃��[�V����
	typedef enum
	{
		ACTION_WAIT1 = 0,
		ACTION_DAMAGE,
		ACTION_BULLETATTACK,
		ACTION_JAMPATTACK,
		ACTION_MAX,

	}ACTION_TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_NODAMAGE,
		STATE_WAIT,
		STATE_SPAWN,
		STATE_DEATH,
		STATE_SET,
		STATE_MAX,
	}STATE;

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CBossLevel *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadLevelData(const char *pFilename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	STATE GetState(void) { return m_State; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetSize(float Size) { m_Size = Size; }
	float GetSize(void) { return m_Size; }
	float GetWight(void) { return m_Size; }
	void SetNULL(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);

private:
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	void Move(void);									//�ړ�����
	void Rot(void);										//��������
	void HitDamage(void);								//�ړ�����
	void StateManager(void);							//��ԊǗ�
	void SetBullet(void);								//�e�̐���
	void SetNeedle(void);								//�Ƃ��̐���
	void AttackPattern(void);							//�U���p�^�[��
	void AtkMiniJump(void);								//���W�����v�U��
	void AtkJump(void);									//�W�����v�U��
	void AtkBullet(void);								//�ˌ��U��
	void AtkNeedle(void);								//�Ƃ��U��
	void AtkNoDamage(void);								//���G�U��

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_NeedlePos;//�ʒu
	int m_nNeedleEffect;	//�ʒu
	float m_Size;			//�傫��
	D3DXVECTOR3 m_posOld;	//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	bool m_bHit;			//�������Ă��邩�ǂ���
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	int m_MotionCount;		//���[�V�����J�E���g
	int m_nLife;			//�̗�
	int m_AttackCount;		//�U���̃J�E���g
	int m_BulletCount;		//�U���̃J�E���g
	int m_NeedleCount;		//�Ƃ������̃J�E���g
	int m_NeedleSet;		//�Ƃ������̂���
	bool m_bAttack;			//�U�������ۂ�
	bool m_bJump;			//�W�����v�����ۂ�
	bool m_bMiniJump;		//�W�����v�����ۂ�
	bool m_bRight;			//�E�������ǂ���
	bool m_bBullet;			//�ˌ������ǂ���
	bool m_bNeedle;			//�Ƃ����������ǂ���
	bool m_bRoundATK;		//���E���h���Ƃ̖��G�U��
	int m_nNoDamageCount;	//���G�U���̎���
	float m_fNeedleSet;		//�Ƃ������ʒu�̐ݒ�
	STATE m_State;			//�{�X�̏��
	int m_nStateCount;		//��ԃJ�E���g
	int m_FallCount;		//�����J�E���g
	int m_HitCount;			//��e�J�E���g

	CLifeGauge *m_pLifeGauge;		//�̗̓Q�[�W
	CLifeGauge *m_pLifeFG;			//�̗̓Q�[�W�̑O�ʃ|���S��
	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;

	CObject2D *m_pLife;
};

#endif