//============================================
//
//	�Q�[����� [game.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"

//�O���錾
class CTutorialUI;
class CPlayer3D;
class CMap2D;
class CPlayerLevel;
class CBossLevel;
class CBreak_Block3D;
class CEdit;
class CTutorialUI;
class CObject2D;
class CPause;
class CScore;
class CTime;

//�V�[���N���X
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void ReSetGame(void);
	static CPlayer3D *GetPlayer3D(void) { return m_pPlayer3D; }
	static CPlayerLevel *GetPlayerLevel(void) { return m_pPlayerLevel; }
	static CBossLevel *GetBossLevel(void) { return m_pBossLevel; }
	static CPause *GetPause(void) { return m_pPause; }
	static CScore *GetScore(void) { return m_pScore; }
	static CEdit *GetEdit(void) { return m_pEdit; }
	static CTime *GetTime(void) { return m_pTime; }
	static void SetGameEnd(int Time) { m_bGameEnd = true; m_nGameEndTime = Time; }
	static void DeleteTutorial(void);
	static void SetTutorial(void);
	static void SetTutorialUnderText(char *cName);
	static void SetBossEvent(bool bSet);
	static bool GetBossEvent(void) { return m_bBossEvent; }
	static void SetTutorial(bool Set) { m_bTutorial = Set; }
	static float GetStartPosX(void) { return m_StartPosX; }
	static int GetDeathCount(void) { return m_nDeathCount; }
	static void AddDeathCount(void) { m_nDeathCount++; }

private:
	static bool m_bBossEvent;				//�{�X�C�x���g��Ԃ��ǂ���
	static bool m_bGameEnd;					//�Q�[���I����Ԃ��ǂ���
	static int m_nGameEndTime;				//�Q�[���I������t�F�[�h�J�n�܂ł̎���
	static int m_nTutorialCount;			//�Q�[����ʂ���`���[�g���A���𐶐�������
	static bool m_bTutorial;				//�`���[�g���A����\�����Ă��邩�ۂ�
	static CTutorialUI *m_pTutorialUI;		//�`���[�g���A��UI�̃|�C���^
	static CPlayer3D *m_pPlayer3D;			//�v���C���[�̃|�C���^
	static CPlayerLevel *m_pPlayerLevel;	//�v���C���[�̃��x���̃|�C���^
	static CBossLevel *m_pBossLevel;		//�K�w�\���̃{�X�̃|�C���^
	static CBreak_Block3D *m_pBlock3D;		//�u���b�N�̃|�C���^
	static CEdit *m_pEdit;					//�G�f�B�b�g���[�h�̃|�C���^
	static CPause *m_pPause;				//�|�[�Y�̃|�C���^
	static CScore *m_pScore;				//�X�R�A�̃|�C���^
	static CTime *m_pTime;
	static bool m_bTextColor;				//�e�L�X�g���Z���Ȃ��Ă��邩�����Ȃ��Ă��邩
	static float m_fTextColor;				//�e�L�X�g�̕s�����x
	static float m_StartPosX;				//�J�n����X���W
	static int m_nDeathCount;				//���S��
};
#endif