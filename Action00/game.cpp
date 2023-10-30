//============================================
//
//	ゲーム画面 [game.cpp]
//	Author:sakamoto kai
//
//============================================
#include "game.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object.h"
#include "object2D.h"
#include "map2D.h"
#include "score.h"
#include "playerlevel.h"
#include "break_block3D.h"
#include "Edit.h"
#include "TutorialUI.h"
#include "ForeGround2D.h"
#include "Pause.h"
#include "ranking.h"
#include "camera.h"
#include "Break.h"
#include "game.h"
#include "sound.h"
#include "MapBlock.h"
#include "MapNeedle.h"
#include "MapNeedleUD.h"
#include "MapNeedleLR.h"
#include "MapDoor.h"
#include "MapSwitch.h"
#include "time.h"
#include "bosslevel.h"
#include "debugproc.h"

//静的メンバ変数宣言
CTutorialUI *CGame::m_pTutorialUI = NULL;
CPlayer3D *CGame::m_pPlayer3D = NULL;
CPlayerLevel *CGame::m_pPlayerLevel = NULL;
CBossLevel *CGame::m_pBossLevel = NULL;
CBreak_Block3D *CGame::m_pBlock3D = NULL;
CEdit *CGame::m_pEdit = NULL;
CPause *CGame::m_pPause = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
bool CGame::m_bBossEvent = false;
bool CGame::m_bGameEnd = false;
int CGame::m_nGameEndTime = 0;
int CGame::m_nTutorialCount = 0;
int CGame::m_nDeathCount = 0;
bool CGame::m_bTextColor = false;
bool CGame::m_bTutorial = false;
float CGame::m_fTextColor = 0.0f;
float CGame::m_StartPosX = 0.0f;

//====================================================================
//コンストラクタ
//====================================================================
CGame::CGame()
{
	m_bBossEvent = false;
	m_nTutorialCount = 0;
	m_bTutorial = false;
	m_StartPosX = 0.0f;
	m_nDeathCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CGame::~CGame()
{

}

//====================================================================
//初期化処理
//====================================================================
HRESULT CGame::Init(void)
{
	//ゲームのBGMを再生する
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);

	//m_pScoreText = CObject2D::Create();
	//m_pScoreText->SetPos(D3DXVECTOR3(975.0f, 60.0f, 0.0f));
	//m_pScoreText->SetWight(300.0f);
	//m_pScoreText->SetHeight(70.0f);
	//m_pScoreText->SetTexture("data\\TEXTURE\\SCORE_UI.png");

	////スコアの生成
	//m_pScore = CScore::Create();
	//m_pScore->SetPos(D3DXVECTOR3(780.0f, 140.0f, 0.0f));
	//m_pScore->SetWight(90.0f);
	//m_pScore->SetHeight(90.0f);
	//m_pScore->SetScore(0);

	//m_pTime = CTime::Create();

	//////3Dオブジェクトの生成
	////CObject3D *Obj3D = CObject3D::Create();

	//////ビルボードの生成
	////CObjectBillboard *ObjBillboard = CObjectBillboard::Create();
	////ObjBillboard->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//階層構造のプレイヤーモデルの生成
	m_pPlayerLevel = CPlayerLevel::Create();
	m_pPlayerLevel->SetPos(D3DXVECTOR3(3300.0f, 100.0f, 0.0f));
	//m_pPlayerLevel->SetPos(D3DXVECTOR3(18700.0f, 500.0f, 0.0f));
	m_pPlayerLevel->SetReSpownPos(D3DXVECTOR3(3300.0f, 155.0f, 0.0f));
	m_StartPosX = 3300.0f;

	//////BGMの再生
	//m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	//エディットモードの生成
	if (m_pEdit == NULL)
	{
		m_pEdit = CEdit::Create();
		m_pEdit->LoadData(DATA_NAME, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\ShortMap00", D3DXVECTOR3(4100.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\Short01Map", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\ALLMap", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\TutorialMap", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\GameMap", D3DXVECTOR3(1900.0f, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage00", D3DXVECTOR3(1900.0f * 0, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage01", D3DXVECTOR3(1900.0f * 1, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage03", D3DXVECTOR3(1900.0f * 2, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage04", D3DXVECTOR3(1900.0f * 3, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage05", D3DXVECTOR3(1900.0f * 4, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage06", D3DXVECTOR3(1900.0f * 5, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage02", D3DXVECTOR3(1900.0f * 6, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\stage07", D3DXVECTOR3(1900.0f * 7, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\BossMap", D3DXVECTOR3(1900.0f * 8, 0.0f, 0.0f));
		//m_pEdit->LoadData("data\\TXT\\BossMap", D3DXVECTOR3(19500.0f, 0.0f, 0.0f));
	}

	m_bGameEnd = false;
	CManager::GetInstance()->GetInstance()->SetStop(false);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CGame::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	if (m_pPause != NULL)
	{
		delete m_pPause;
		m_pPause = NULL;
	}

	if (m_pEdit != NULL)
	{
		//エディットモードの終了処理
		m_pEdit->Uninit();

		delete m_pEdit;
		m_pEdit = NULL;
	}

	if (m_pTutorialUI != NULL)
	{
		delete m_pTutorialUI;
		m_pTutorialUI = NULL;
	}
}

//====================================================================
//終了処理
//====================================================================
void CGame::DeleteTutorial(void)
{
	if (m_pTutorialUI != NULL)
	{
		delete m_pTutorialUI;
		m_pTutorialUI = NULL;
	}
}

//====================================================================
//更新処理
//====================================================================
void CGame::Update(void)
{
#if _DEBUG
	//リセット処理
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_R) == true)
	{
		ReSetGame();
	}

#endif

	if (m_pTutorialUI != NULL)
	{
		m_pTutorialUI->Update();
	}

	if (m_bTutorial == false)
	{
		switch (m_nTutorialCount)
		{
		case 0:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX -100.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}
			break;

		case 1:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 100.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}
			break;

		case 2:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 500.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}
			break;

		case 3:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 1000.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}

		case 4:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 2850.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}

		case 5:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 3650.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}

		case 6:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 5650.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}

		case 7:
			if (m_pPlayerLevel->GetPos().x >= m_StartPosX + 8550.0f)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}
			break;

		case 8:
			if (false)
			{
				m_pTutorialUI = CTutorialUI::Create(m_nTutorialCount);
				m_nTutorialCount++;
				m_bTutorial = true;
			}
			break;
		}
	}

	//ポーズの更新処理
	m_pPause->Update();

	//エディットモードのオンオフ
	if (CManager::GetInstance()->GetEdit() == true)
	{
		//エディットモードの更新処理
		m_pEdit->Update();
	}
	else
	{

	}

	//ゲームモード終了処理
	if (m_bGameEnd == true)
	{
		if (m_nGameEndTime > 0)
		{
			m_nGameEndTime--;
		}
		else
		{
			CRanking::ChangeRanking(true);
			CFade::SetFade(CScene::MODE_RESULT);
		}
	}

	CManager::GetInstance()->GetDebugProc()->Print("チュートリアルの段階[%d]\n", m_nTutorialCount - 1);

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_G) == true)
	{
		CRanking::ChangeRanking(true);
		CManager::GetInstance()->GetInstance()->SetScoreResult(true);
		CFade::SetFade(CScene::MODE_RESULT);
	}

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		CFade::SetFade(CScene::MODE_RESULT);
	}
}

//====================================================================
//ボスイベント処理
//====================================================================
void CGame::SetBossEvent(bool bSet)
{
	m_bBossEvent = bSet;

	if (bSet == true)
	{
		m_pBossLevel = CBossLevel::Create();
		m_pBossLevel->SetPos(D3DXVECTOR3(20000.0f, 600.0f, 0.0f));
		CManager::GetInstance()->GetSound()->StopSound();
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_BOSS);
	}
}

//====================================================================
//リセット処理
//====================================================================
void CGame::ReSetGame(void)
{

}

//====================================================================
//チュートリアルの呼び出し処理
//====================================================================
void CGame::SetTutorial(void)
{

}

//====================================================================
//チュートリアルの呼び出し処理
//====================================================================
void CGame::SetTutorialUnderText(char *cName)
{

}


//====================================================================
//描画処理
//====================================================================
void CGame::Draw(void)
{

}
