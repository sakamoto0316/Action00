//============================================
//
//	マネージャ [manager.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "object.h"

//前方宣言
class CRenderer;
class CDebugProc;
class CInputKeyboard;
class CInputJoypad;
class CCamera;
class CLight;
class CTexture;
class CXModel;
class CLevelUP;
class CFade;
class CSound;

//シーンクラス
class CScene
{
public:
	CScene();
	~CScene();

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT
	}MODE;

	static CScene *Create(MODE mode);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }

private:
	static MODE m_mode;
};

//マネージャクラス
class CManager
{
public:
	CManager();
	~CManager();

	static CManager *GetInstance();
	static HRESULT Release(void);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); 	//返り値がHRESULTなのは頂点バッファの生成などに失敗したとき確認のため
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CRenderer *GetRenderer(void) { return m_pRenderer; }
	CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	CInputJoypad *GetInputJoyPad(void) { return m_pInputJoyPad; }
	CCamera *GetCamera(void) { return m_pCamera; }
	CTexture *GetTexture(void) { return m_pTexture; }
	CXModel *GetXModel(void) { return m_pXModel; }
	CScene *GetScene(void) { return m_pScene; }
	CFade *GetFade(void) { return m_Fade; }
	CSound *GetSound(void) { return m_pSound; }
	void SetScene(CScene *Scene) { m_pScene = Scene; }
	void SetLevelUP(CLevelUP *LevelUP) { m_LevelUP = LevelUP; }
	void SetEdit(bool bEdit) { m_bEdit = bEdit; }
	bool GetEdit(void) { return m_bEdit; }
	void SetStop(bool Set) { m_bStop = Set; }
	bool GetStop(void) { return m_bStop; }
	void SetPause(bool Set) { m_Pause = Set; }
	bool GetPause(void) { return m_Pause; }
	void SetEndScore(int Set) { m_EndScore = Set; }
	int GetEndScore(void) { return m_EndScore; }
	void SetTutorialStart(bool Set) { m_SetTutorial = Set; }
	bool GetTutorialStart(void) { return m_SetTutorial; }
	void SetScoreResult(bool Set) { m_SetScoreResult = Set; }
	bool GetScoreResult(void) { return m_SetScoreResult; }
	void SetSetTutorialPad(bool Set) { m_SetJoyPad = Set; }
	bool GetSetTutorialPad(void) { return m_SetJoyPad; }
	void SetPauseOK(bool Set) { m_PauseOK = Set; }
	bool GetPauseOK(void) { return m_PauseOK; }
	void SetUseJoyPad(bool Set) { m_bPad = Set; }
	bool GetUseJoyPad(void) { return m_bPad; }

private:
	static CManager *pManager;

	int m_EndScore;						//最終的なスコア
	bool m_SetTutorial;					//エディットモードかどうか
	bool m_bEdit;						//エディットモードかどうか
	bool m_bStop;						//画面停止状態かどうか
	bool m_Pause;						//ポーズ状態かどうか
	bool m_SetScoreResult;				//リザルトにスコア情報を入れるかどうか
	bool m_SetJoyPad;					//ジョイパッドで操作しているかどうか
	bool m_PauseOK;						//ポーズを押しても大丈夫か
	bool m_bPad;						//ジョイパッドを使用しているかどうか
	CRenderer *m_pRenderer;				//レンダラーのポインタ
	CDebugProc *m_pDebugProc;			//デバッグプロックのポインタ
	CInputKeyboard *m_pInputKeyboard;	//キーボードのポインタ
	CInputJoypad *m_pInputJoyPad;		//ジョイパッドのポインタ
	CCamera *m_pCamera;					//カメラのポインタ
	CLight *m_pLight;					//ライトのポインタ
	CTexture *m_pTexture;				//テクスチャのポインタ
	CXModel *m_pXModel;					//Xモデルのポインタ
	CScene *m_pScene;					//シーンのポインタ
	CLevelUP *m_LevelUP;				//レベルアップのポインタ
	CFade *m_Fade;						//フェードのポインタ
	CSound *m_pSound;					//サウンドのポインタ
};												

#endif