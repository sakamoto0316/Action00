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
	static void SetGameEnd(int Time) { m_bGameEnd = true; m_bGameEndTime = Time; }
	static void DeleteTutorial(void);
	static void SetTutorial(void);
	static void SetTutorialUnderText(char *cName);
	static void SetBossEvent(bool bSet);
	static bool GetBossEvent(void) { return m_bBossEvent; }

private:
	static bool m_bBossEvent;				//�{�X�C�x���g��Ԃ��ǂ���
	static bool m_bGameEnd;					//�Q�[���I����Ԃ��ǂ���
	static int m_bGameEndTime;				//�Q�[���I������t�F�[�h�J�n�܂ł̎���
	static CPlayer3D *m_pPlayer3D;			//�v���C���[�̃|�C���^
	static CPlayerLevel *m_pPlayerLevel;	//�v���C���[�̃��x���̃|�C���^
	static CBossLevel *m_pBossLevel;		//�K�w�\���̃{�X�̃|�C���^
	static CBreak_Block3D *m_pBlock3D;		//�u���b�N�̃|�C���^
	static CEdit *m_pEdit;					//�G�f�B�b�g���[�h�̃|�C���^
	static CTutorialUI *m_pTutorialUI;		//�`���[�g���A����ʉ���UI�̃|�C���^
	static CObject2D *m_pTutorialBG;		//�`���[�g���A����ʉ��̔w�i�̃|�C���^
	static CObject2D *m_pTutorialText;		//�`���[�g���A����ʉ��̃e�L�X�g�̃|�C���^
	static CPause *m_pPause;				//�|�[�Y�̃|�C���^
	static CObject2D *m_pScoreText;			//�X�R�A�p�̃e�L�X�g
	static CScore *m_pScore;				//�X�R�A�̃|�C���^
	static CTime *m_pTime;
	static bool m_bTextColor;				//�e�L�X�g���Z���Ȃ��Ă��邩�����Ȃ��Ă��邩
	static float m_fTextColor;				//�e�L�X�g�̕s�����x
};
#endif