//============================================
//
//	プレイヤーの処理 [playerlevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "playerlevel.h"
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "sound.h"
#include "EMPManager.h"
#include "EffectMovePolygon.h"
#include "Effect.h"
#include "WallJump.h"
#include "WallMove.h"
#include "WallAttackSide.h"
#include "WallAttackDown.h"
#include "game.h"
#include "time.h"
#include "MapBlock.h"
#include "MapPitFloor.h"
#include "bosslevel.h"

#define PLAYER_SPEED (10.0f)		//プレイヤーの速さ
#define PLAYER_JAMPPOWER (15.0f)	//プレイヤーのジャンプ力
#define PLAYER_JAMPWALL (4.0f)		//ジャンプまでの力の振り幅
#define JAMP_ACTIONNOT (4)			//ジャンプから行動出来るまで
#define WIDTH_COLLISION (40.0f)		//横の当たり判定
#define HEIGHT_COLLISION (180.0f)	//縦の当たり判定
#define BOSSEVENT_POS (19600.0f)	//ボス戦が始まる座標

//====================================================================
//コンストラクタ
//====================================================================
CPlayerLevel::CPlayerLevel()
{
	SetWight(WIDTH_COLLISION);
	SetHeight(HEIGHT_COLLISION * 0.5f);
	m_pos = INITVECTOR3;
	m_move = INITVECTOR3;
	m_rot = D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f);
	m_bWallJump = false;
	m_nJump = 2;
	m_nActionCount = 0;
	m_Action = ACTION_WAIT;
	m_nAttackCount = 0;
	m_bRight = true;
	m_State = STATE_NORMAL;
	m_nStateCount = 0;
	m_ReSpownPos = INITVECTOR3;
	m_GameEnd = false;
}

//====================================================================
//デストラクタ
//====================================================================
CPlayerLevel::~CPlayerLevel()
{

}

//====================================================================
//生成処理
//====================================================================
CPlayerLevel *CPlayerLevel::Create()
{
	CPlayerLevel *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//プレイヤーの生成
		pPlayer = new CPlayerLevel();
	}

	//オブジェクトの初期化処理
	if (FAILED(pPlayer->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CPlayerLevel::Init(void)
{
	//モデルの生成
	LoadLevelData("data\\TXT\\motion_WallKnight.txt");

	//モーションの生成
	if (m_pMotion == NULL)
	{
		//モーションの生成
		m_pMotion = new CMotion;
	}
	//初期化処理
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_WallKnight.txt");

	SetType(CObject::TYPE_PLAYER3D);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CPlayerLevel::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_apModel[nCntModel]->Uninit();
		delete m_apModel[nCntModel];
		m_apModel[nCntModel] = NULL;
	}

	//モーションの終了処理
	if (m_pMotion != NULL)
	{
		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//更新処理
//====================================================================
void CPlayerLevel::Update(void)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		//キーボードの取得
		CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		//過去の位置を記録する
		m_posOld = m_pos;

		//当たり判定を有効にする
		m_bHit = false;

		//重力
		m_move.y -= 0.98f;

		//落下速度が一定以上になった場合ジャンプを不能にする
		if (m_move.y < -5.0f)
		{
			if (m_nJump == 2)
			{
				m_nJump = 1;
			}
		}
		//移動処理
		Move();

		if (m_nJump == 2)
		{
			//移動方向処理
			Rot();
		}

		//壁を生成して攻撃
		WallAttack();

		//行動不能時間のカウント
		m_nActionNotCount--;

		if (m_bWallJump == true)
		{
			//壁を生成してジャンプ
			WallJamp();
		}

		//減衰係数
		m_move.x = m_move.x * 0.5f;
		if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
		{
			m_move.x = 0.0f;
		}

		//X軸の位置更新
		m_pos.x += m_move.x;

		//当たり判定
		CollisionObject(&m_pos, true);
		CollisionBoss();

		//Y軸の位置更新
		m_pos.y += m_move.y;

		//当たり判定
		CollisionObject(&m_pos, false);
		CollisionBoss();

		//Z軸の位置更新
		m_pos.z += m_move.z;

		//画面外判定
		if (m_pos.y < 0.0f)
		{
			HitDamage();
		}

		EventManager();
	}

	//モーションの管理
	ActionState();

	//状態の管理
	StateManager();

	//モーションの更新
	m_pMotion->Update();
}

//====================================================================
//状態管理
//====================================================================
void CPlayerLevel::EventManager(void)
{
	if (m_pos.x >= BOSSEVENT_POS)
	{
		if (CGame::GetBossEvent() == false)
		{
			CGame::SetBossEvent(true);
			SetReSpownPos(D3DXVECTOR3(19550.0f, 850.0f, 0.0f));
			DeleteMap();

			for (int nCnt = 0; nCnt <= 12; nCnt++)
			{
				CMapBlock *pBlock = CMapBlock::Create();
				pBlock->SetPos(D3DXVECTOR3(18800.0f, 1200.0f + nCnt * -100.0f, 0.0f));
			}

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CMapPitFloor *pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19200.0f + nCnt * 900.0f, 600.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19200.0f + 100.0f + nCnt * 900.0f, 600.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19500.0f + nCnt * 300.0f, 700.0f, 0.0f));

				pFloor = CMapPitFloor::Create();
				pFloor->SetPos(D3DXVECTOR3(19500.0f + 100.0f + nCnt * 300.0f, 700.0f, 0.0f));
			}
		}
	}
}

//====================================================================
//状態管理
//====================================================================
void CPlayerLevel::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DEATH:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_WAIT;
			m_nStateCount = 60;
		}
		break;

	case STATE_WAIT:
		if (m_nStateCount <= 0)
		{
			if (CGame::GetBossEvent() == false)
			{
				m_State = STATE_NORMAL;
				m_nStateCount = 0;
			}
			else
			{
				m_State = STATE_NODAMAGE;
				m_nStateCount = 120;
				for (int nCnt = 0; nCnt < 64; nCnt++)
				{
					if (m_apModel[nCnt] != NULL)
					{
						m_apModel[nCnt]->SetColorChange(true);
						m_apModel[nCnt]->SetColor(D3DXCOLOR(0.9f, 0.3f, 0.0f, 0.5f));
					}
				}
			}
		}
		break;

	case STATE_NODAMAGE:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_NORMAL;
			m_nStateCount = 0;

			for (int nCnt = 0; nCnt < 64; nCnt++)
			{
				if (m_apModel[nCnt] != NULL)
				{
					m_apModel[nCnt]->SetColorChange(false);
				}
			}
		}
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//移動処理
//====================================================================
void CPlayerLevel::Move(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true) &&
		m_nJump != 0 &&
		(m_Action != ACTION_WALLATTACK)
		)
	{//攻撃中じゃない時にジャンプボタンを押したとき

		//SE
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);
		
		if (m_nJump == 2)
		{
			//ジャンプの挙動開始とジャンプ消費
			m_bWallJump = true;

			//ジャンプ時の壁生成
			CWallJump *pWallJump = CWallJump::Create();
			pWallJump->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 5.0f, m_pos.y - 70.0f, 0.0f));
		}
		else
		{
			m_pMotion->Set(ACTION_JAMP);
			m_move.y = PLAYER_JAMPPOWER * 0.75f;

			//ジャンプ時の壁生成
			CWallAttackDown *pWallDown = CWallAttackDown::Create();
			pWallDown->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 5.0f, m_pos.y + 10.0f, 0.0f));
		}

		m_nJump--;

		//ジャンプ直後は攻撃などのアクションを行えない
		m_nActionNotCount = JAMP_ACTIONNOT;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true)
	{//左移動ボタンを押したとき

		//空中だと背中方向への移動が遅くなる
		if (m_nJump <= 1 && m_bRight == true)
		{
			m_move.x -= PLAYER_SPEED * 0.5f;
		}
		else
		{
			m_move.x -= PLAYER_SPEED;
		}

		//移動中の壁生成の管理
		WallMoveManager();
	}

	if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true)
	{//右ボタンを押したとき

		//空中だと背中方向への移動が遅くなる
		if (m_nJump <= 1 && m_bRight == false)
		{
			m_move.x += PLAYER_SPEED * 0.5f;
		}
		else
		{
			m_move.x += PLAYER_SPEED;
		}

		//移動中の壁生成の管理
		WallMoveManager();
	}

	if (pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_LEFT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == false &&
		pInputKeyboard->GetPress(DIK_D) == false &&
		pInputKeyboard->GetPress(DIK_RIGHT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == false)
	{//移動ボタンの入力がない場合のみスティックでの移動を受け付ける
		m_move.x += pInputJoypad->Get_Stick_Left(0).x * PLAYER_SPEED;
	}
}

//====================================================================
//移動方向処理
//====================================================================
void CPlayerLevel::Rot(void)
{
	if (m_move.x > 0.1f)
	{
		m_rot.y = D3DX_PI * -0.5f;
		m_bRight = true;
	}
	else if (m_move.x < -0.1f)
	{
		m_rot.y = D3DX_PI * 0.5f;
		m_bRight = false;
	}
}

//====================================================================
//攻撃を受けた時の処理
//====================================================================
void CPlayerLevel::HitDamage(void)
{
	if (m_State == STATE_NORMAL)
	{
		CEffect *pEffect = CEffect::Create();
		pEffect->SetPos(m_pos);
		pEffect->SetRadius(500.0f);
		pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_State = STATE_DEATH;
		m_nStateCount = 1;
		m_pos = D3DXVECTOR3(m_ReSpownPos.x, m_ReSpownPos.y + -100.0f, m_ReSpownPos.z);
		m_move = INITVECTOR3;
		m_Action = ACTION_WAIT;
		m_nAttackCount = 0;
		m_pMotion->Set(ACTION_WAIT);
		CGame::AddDeathCount();
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
	}
}

//====================================================================
//モーションと状態の管理
//====================================================================
void CPlayerLevel::ActionState(void)
{
	//攻撃モーション
	if (m_nAttackCount > 0)
	{
		if (m_Action != ACTION_WALLATTACK)
		{
			m_Action = ACTION_WALLATTACK;
			m_pMotion->Set(ACTION_WALLATTACK);
		}
	}
	//ジャンプモーション
	else if (m_nJump != 2)
	{
		if (m_Action != ACTION_JAMP)
		{
			m_Action = ACTION_JAMP;
			m_pMotion->Set(ACTION_JAMP);
		}
	}
	//移動モーション
	else if (m_move.x > 0.1f || m_move.x < -0.1f)
	{
		if (m_Action != ACTION_MOVE)
		{
			m_Action = ACTION_MOVE;
			m_pMotion->Set(ACTION_MOVE);
		}
	}
	//ニュートラルモーション
	else
	{
		if (m_Action != ACTION_WAIT)
		{
			m_Action = ACTION_WAIT;
			m_pMotion->Set(ACTION_WAIT);
		}
	}
}

//====================================================================
//壁を生成して攻撃
//====================================================================
void CPlayerLevel::WallAttack(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_B, 0) == true) &&
		m_nAttackCount <= 0 &&
		m_bAirAttack == false &&
		m_nActionNotCount <= 0
		)
	{
		m_nAttackCount = 25;
		m_bAirAttack = true;
	}

	if (m_nAttackCount > 0)
	{
		m_move.x *= 0.1f;
		m_move.y = 0.0f;
		m_bWallJump = false;
		m_nAttackCount--;
	}

	if (m_nAttackCount == 8)
	{
		CWallAttackSide *pWallAttack = CWallAttackSide::Create(m_bRight);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
		if (m_bRight == true)
		{
			pWallAttack->SetPos(D3DXVECTOR3(m_pos.x + 10.0f, m_pos.y, m_pos.z));
		}
		else
		{
			pWallAttack->SetPos(D3DXVECTOR3(m_pos.x - 10.0f, m_pos.y, m_pos.z));
		}
	}
}

//====================================================================
//壁を生成してジャンプ
//====================================================================
void CPlayerLevel::WallJamp(void)
{
	if (m_move.y < PLAYER_JAMPPOWER)
	{
		m_move.y += PLAYER_JAMPWALL;
	}
	else
	{
		m_move.y = PLAYER_JAMPPOWER;
		m_bWallJump = false;
	}
}

//====================================================================
//壁を生成して移動
//====================================================================
void CPlayerLevel::WallMoveManager(void)
{
	if (m_Action == ACTION_MOVE)
	{
		m_nWallMoveCount++;

		if (m_nWallMoveCount % 2 == 0)
		{
			int nRandZ = rand() % 50;
			int nRandRotZ = rand() % 31;

			CWallMove *pWallMove = CWallMove::Create();
			pWallMove->SetPos(D3DXVECTOR3(m_pos.x + m_move.x * 3.5f, m_pos.y - 20.0f, (float)nRandZ - 25.0f));
			if (m_bRight == true)
			{
				pWallMove->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * ((float)nRandRotZ * 0.01f), D3DX_PI * ((float)nRandRotZ * 0.01f)));
			}
			else
			{
				pWallMove->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -((float)nRandRotZ * 0.01f), D3DX_PI * -((float)nRandRotZ * 0.01f)));
			}
		}
	}
	
}

//====================================================================
//壁を生成して移動
//====================================================================
void CPlayerLevel::SetReSpownPos(D3DXVECTOR3 pos)
{
	m_ReSpownPos = pos;

	CGame::GetTime()->SetTime(10);
	CGame::GetTime()->ReSetCount();
}

//====================================================================
//オブジェクトとの当たり判定処理
//====================================================================
bool CPlayerLevel::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (m_State != STATE_NODAMAGE)
			{
				if (type == TYPE_MAPBLOCK ||
					type == TYPE_MAPDOOR ||
					type == TYPE_MAPSWITCH ||
					type == TYPE_MAPSDOOR ||
					type == TYPE_MAPSSWITCH ||
					type == TYPE_MAPNEEDLE ||
					type == TYPE_MAPNEEDLELR ||
					type == TYPE_MAPNEEDLEUD ||
					type == TYPE_MAPPITFLOOR ||
					type == TYPE_MAPCANNON)
				{//種類がブロックの時

					if (pObj->CollisionPlayer(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, &m_bWallJump, &m_bHit, bX) == true)
					{
						m_nJump = 2;
						m_bAirAttack = false;
						m_move.y = 0.0f;

						return true;
					}

					if (m_bHit == true)
					{
						return true;
					}
				}
			}
			else
			{
				if (type == TYPE_MAPBLOCK ||
					type == TYPE_MAPPITFLOOR)
				{//種類がブロックの時

					if (pObj->CollisionPlayer(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, &m_bWallJump, &m_bHit, bX) == true)
					{
						m_nJump = 2;
						m_bAirAttack = false;
						m_move.y = 0.0f;

						return true;
					}

					if (m_bHit == true)
					{
						return true;
					}
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//マップの削除処理
//====================================================================
void CPlayerLevel::DeleteMap(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == TYPE_MAPBLOCK ||
				type == TYPE_MAPDOOR ||
				type == TYPE_MAPSWITCH ||
				type == TYPE_MAPSDOOR ||
				type == TYPE_MAPSSWITCH ||
				type == TYPE_MAPNEEDLE ||
				type == TYPE_MAPNEEDLELR ||
				type == TYPE_MAPNEEDLEUD ||
				type == TYPE_MAPCANNON ||
				type == TYPE_MAPCHECKPOINT)
			{//種類がブロックの時

				D3DXVECTOR3 ObjPos = pObj->GetPos();

				if (ObjPos.x <= 18800.0f)
				{
					pObj->Uninit();
				}
			}
			else if (type == TYPE_MAPPITFLOOR)
			{
				pObj->Uninit();
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
void CPlayerLevel::CollisionBoss(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == TYPE_BOSSLEVEL)
			{//種類がブロックの時

				CBossLevel *pBoss = (CBossLevel*)pObj;

				D3DXVECTOR3 ObjPos = pBoss->GetPos();
				float fSize = pBoss->GetWight();
				float myWight = GetWight();
				float myHeight = GetWight();

				if (pBoss->GetState() != CBossLevel::STATE_SPAWN)
				{
					if (m_pos.x + myWight > ObjPos.x - fSize * 0.5f &&
						m_pos.x - myWight < ObjPos.x + fSize * 0.5f &&
						m_pos.y + myHeight > ObjPos.y - fSize &&
						m_pos.y < ObjPos.y + fSize * 2
						)
					{
						HitDamage();
					}
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CPlayerLevel::Draw(void)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//モデルの描画(全パーツ)
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			m_apModel[nCntModel]->Draw();
		}
	}
}

//====================================================================
//ロード処理
//====================================================================
void CPlayerLevel::LoadLevelData(const char *pFilename)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		int ModelParent = 0;
		D3DXVECTOR3 ModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ModelRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		char ModelName[128] = {};
		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//ゴミ箱
		char aMessage[128] = {};			//スタートとエンドのメッセージ
		char aBool[128] = {};				//bool変換用メッセージ

		// 読み込み開始-----------------------------------------------------
		while (1)
		{//「SCRIPT」を探す
			fscanf(pFile, "%s", &aMessage[0]);
			if (strcmp(&aMessage[0], "SCRIPT") == 0)
			{
				// モデル数読み込み-----------------------------------------------------
				while (1)
				{//「NUM_MODEL」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_nNumModel);		//モデル数の設定
						break;
					}
				}

				//モデルファイルの読み込み
				while (1)
				{//「MODEL_FILENAME」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%s", &ModelName[0]);		//読み込むモデルのパスを取得

						m_apModel[nCntModel] = CModel::Create(&ModelName[0]);
						nCntModel++;
					}
					if (nCntModel >= m_nNumModel)
					{
						nCntModel = 0;
						break;
					}
				}

				// キャラクター情報読み込み-----------------------------------------------------
				while (1)
				{//「PARTSSET」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//各種変数を探す
							fscanf(pFile, "%s", &aMessage[0]);
							if (strcmp(&aMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//インデックスを設定
							}
							if (strcmp(&aMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &ModelParent);	//親モデルのインデックスを設定

								if (ModelParent == -1)
								{
									m_apModel[nCntModel]->SetParent(NULL);
								}
								else
								{
									m_apModel[nCntModel]->SetParent(m_apModel[ModelParent]);
								}
							}
							if (strcmp(&aMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelPos.x);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &ModelPos.y);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &ModelPos.z);				//位置(オフセット)の初期設定

								m_apModel[nCntModel]->SetPos(ModelPos);
								m_apModel[nCntModel]->SetStartPos(ModelPos);
							}
							if (strcmp(&aMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelRot.x);				////向きの初期設定
								fscanf(pFile, "%f", &ModelRot.y);				////向きの初期設定
								fscanf(pFile, "%f", &ModelRot.z);				////向きの初期設定

								m_apModel[nCntModel]->SetRot(ModelRot);
								m_apModel[nCntModel]->SetStartRot(ModelRot);
							}
							if (strcmp(&aMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= m_nNumModel)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}