//============================================
//
//	ゲーム画面 [game.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"

//前方宣言
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

//シーンクラス
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
	static bool m_bBossEvent;				//ボスイベント状態かどうか
	static bool m_bGameEnd;					//ゲーム終了状態かどうか
	static int m_bGameEndTime;				//ゲーム終了からフェード開始までの時間
	static CPlayer3D *m_pPlayer3D;			//プレイヤーのポインタ
	static CPlayerLevel *m_pPlayerLevel;	//プレイヤーのレベルのポインタ
	static CBossLevel *m_pBossLevel;		//階層構造のボスのポインタ
	static CBreak_Block3D *m_pBlock3D;		//ブロックのポインタ
	static CEdit *m_pEdit;					//エディットモードのポインタ
	static CTutorialUI *m_pTutorialUI;		//チュートリアル画面下のUIのポインタ
	static CObject2D *m_pTutorialBG;		//チュートリアル画面下の背景のポインタ
	static CObject2D *m_pTutorialText;		//チュートリアル画面下のテキストのポインタ
	static CPause *m_pPause;				//ポーズのポインタ
	static CObject2D *m_pScoreText;			//スコア用のテキスト
	static CScore *m_pScore;				//スコアのポインタ
	static CTime *m_pTime;
	static bool m_bTextColor;				//テキストが濃くなっているか薄くなっているか
	static float m_fTextColor;				//テキストの不透明度
};
#endif