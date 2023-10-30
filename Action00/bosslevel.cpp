//============================================
//
//	ボスの処理 [bosslevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bosslevel.h"
#include "object.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "player3D.h"
#include "effect.h"
#include "playerlevel.h"
#include "CannonBullet.h"
#include "MapNeedle.h"
#include "MapNeedleUD.h"
#include "MapNeedleLR.h"
#include "MapCannon.h"
#include "Edit.h"

#define COLLISION_BOSS (50.0f) //ボスの当たり判定

//====================================================================
//コンストラクタ
//====================================================================
CBossLevel::CBossLevel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = COLLISION_BOSS;
	m_bHit = false;

	m_bRight = false;
	m_AttackCount = 0;
	m_bAttack = false;
	m_bJump = false;
	m_bBullet = false;
	m_bNeedle = false;
	m_BulletCount = 0;
	m_NeedleCount = 0;
	m_NeedleSet = 0;
	m_State = STATE_NORMAL;
	m_FallCount = 0;
	m_HitCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CBossLevel::~CBossLevel()
{

}

//====================================================================
//生成処理
//====================================================================
CBossLevel *CBossLevel::Create()
{
	CBossLevel *pBoss = NULL;

	if (pBoss == NULL)
	{
		//ボスの生成
		pBoss = new CBossLevel();
	}

	//オブジェクトの初期化処理
	if (FAILED(pBoss->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pBoss;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CBossLevel::Init(void)
{
	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);

	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//モデルの生成
	LoadLevelData("data\\TXT\\motion_Boss.txt");

	//モーションの生成
	if (m_pMotion == NULL)
	{
		//モーションの生成
		m_pMotion = new CMotion;
	}
	//初期化処理
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_Boss.txt");

	SetType(CObject::TYPE_BOSSLEVEL);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBossLevel::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//終了処理
//====================================================================
void CBossLevel::SetNULL(void)
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
}

//====================================================================
//更新処理
//====================================================================
void CBossLevel::Update(void)
{
	//過去の位置を記録する
	m_posOld = m_pos;

	//重力
	m_move.y -= 0.98f;

	//減衰係数
	m_move.x = m_move.x * 0.5f;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	if (m_bJump == false)
	{
		Rot();
	}

	if (m_bJump == true)
	{
		D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();
		if (m_bRight == false)
		{
			if (m_bMiniJump == true)
			{
				m_move.x += -3.0f;
			}
			else
			{
				m_move.x += -7.5f;
			}
		}
		else
		{
			if (m_bMiniJump == true)
			{
				m_move.x += 3.0f;
			}
			else
			{
				m_move.x += 7.5f;
			}
		}
	}

	if (m_bRoundATK == true)
	{
		AtkNoDamage();
	}
	else
	{
		if (m_State == STATE_NORMAL)
		{
			//攻撃パターン
			AttackPattern();
		}
	}

	//弾生成攻撃
	if (m_bBullet == true)
	{
		SetBullet();
	}

	//とげ生成攻撃
	if (m_bNeedle == true)
	{
		SetNeedle();
	}

	//X軸の位置更新
	m_pos.x += m_move.x;

	//当たり判定
	CollisionObject(&m_pos, true);

	//Y軸の位置更新
	m_pos.y += m_move.y;

	//当たり判定
	CollisionObject(&m_pos, false);

	//Z軸の位置更新
	m_pos.z += m_move.z;

	if (m_pos.y <= -100.0f && m_State != STATE_WAIT)
	{
		m_State = STATE_WAIT;
		m_nStateCount = 120;
		m_FallCount++;
	}

	//状態管理
	StateManager();

	//モーションの管理
	if (m_MotionCount > 0)
	{
		m_MotionCount--;
		if (m_MotionCount == 0)
		{
			m_pMotion->Set(ACTION_WAIT1);
		}
	}

	//モーションの更新
	m_pMotion->Update();
}

//====================================================================
//状態管理
//====================================================================
void CBossLevel::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DEATH:
		break;

	case STATE_WAIT:
		if (m_nStateCount <= 0)
		{
			if (m_FallCount == 3)
			{
				CGame::SetGameEnd(20);
				m_State = STATE_DEATH;
				CManager::GetInstance()->GetInstance()->SetEndScore(CGame::GetDeathCount());
			}
			else
			{
				m_State = STATE_SPAWN;
				m_nStateCount = 45;

				D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();
				m_pos = D3DXVECTOR3(PlayerPos.x, 300.0f, -650.0f);
				m_move = D3DXVECTOR3(0.0f, 40.0f, 0.0f);

				if (m_FallCount == 1)
				{
					CGame::GetEdit()->LoadData("data\\TXT\\BossRound1", D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else if (m_FallCount == 2)
				{
					//とげの生成
					for (int nCnt = 0; nCnt <= 2; nCnt++)
					{
						CMapNeedle *pNeedle = CMapNeedle::Create(D3DXVECTOR3(19100.0f + nCnt * 1200.0f, 600.0f, 0.0f));
						pNeedle->SetPos(D3DXVECTOR3(19100.0f + nCnt * 1200.0f, 600.0f, 0.0f));
						pNeedle->SetRotChange(true);
						pNeedle->SetMoveWight(300.0f);
						pNeedle->SetMoveSpeed(0.006f);
					}
				}
			}
		}
		break;

	case STATE_SPAWN:
		if (m_nStateCount <= 0)
		{
			m_nStateCount = 0;
			m_AttackCount = 0;
			m_bAttack = false;
			m_pos = D3DXVECTOR3(19700.0f, 900.0f, 0.0f);

			m_pMotion->Set(ACTION_JAMPATTACK);
			m_State = STATE_NODAMAGE;
			m_bRoundATK = true;
			m_nNoDamageCount = 600;
			m_MotionCount = 600;
		}
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//攻撃パターン
//====================================================================
void CBossLevel::AttackPattern(void)
{
	if (m_bAttack == false && m_MotionCount == 0)
	{
		m_AttackCount++;
		if (m_AttackCount >= 120)
		{
			m_bAttack = true;
			int nRandAttack = rand() % 101;
			

			if (m_HitCount >= 5)
			{
				if (nRandAttack >= 70)
				{
					AtkJump();
				}
				else if (nRandAttack >= 40)
				{
					AtkMiniJump();
				}
				else if (nRandAttack >= 20)
				{
					AtkBullet();
				}
				else
				{
					if (m_bNeedle == false)
					{
						AtkNeedle();
					}
					else
					{
						m_bAttack = false;
					}
				}

				m_HitCount = 0;
			}
			else
			{
				if (nRandAttack >= 90)
				{
					AtkJump();
				}
				else if (nRandAttack >= 80)
				{
					AtkMiniJump();
				}
				else if (nRandAttack >= 40)
				{
					AtkBullet();
				}
				else
				{
					if (m_bNeedle == false)
					{
						AtkNeedle();
					}
					else
					{
						m_bAttack = false;
					}
				}
			}
		}
	}
}

//====================================================================
//ジャンプ攻撃
//====================================================================
void CBossLevel::AtkMiniJump(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 15.0f;

	m_bMiniJump = true;
	m_bJump = true;
	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//ジャンプ攻撃
//====================================================================
void CBossLevel::AtkJump(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 20.0f;

	m_bJump = true;
	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//射撃攻撃
//====================================================================
void CBossLevel::AtkBullet(void)
{
	m_pMotion->Set(ACTION_BULLETATTACK);
	m_MotionCount = 440;
	m_BulletCount = 441;
	m_bBullet = true;
}

//====================================================================
//弾の生成
//====================================================================
void CBossLevel::SetBullet(void)
{
	if (m_BulletCount > 0)
	{
		m_BulletCount--;
		if (m_BulletCount <= 340 && m_BulletCount >= 50)
		{

			if (m_BulletCount % 80 == 0)
			{
				if (m_bRight == false)
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 70.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				}
				else
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 70.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
				}
			}

			if ((m_BulletCount + 40) % 80 == 0)
			{
				if (m_bRight == false)
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				}
				else
				{
					CCannonBullet *pBullet = CCannonBullet::Create();
					pBullet->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 150.0f, m_pos.z));
					pBullet->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
				}
			}
		}
		if (m_BulletCount == 0)
		{
			m_MotionCount = 0;
			m_bBullet = false;
			m_bAttack = false;
			m_AttackCount = 0;
		}
	}
}


//====================================================================
//とげ攻撃
//====================================================================
void CBossLevel::AtkNeedle(void)
{
	m_pMotion->Set(ACTION_JAMPATTACK);
	m_MotionCount = 40;

	m_move.y = 30.0f;
	m_bNeedle = true;
	m_fNeedleSet = m_pos.x;

	m_bAttack = false;
	m_AttackCount = 0;
}

//====================================================================
//とげの生成
//====================================================================
void CBossLevel::SetNeedle(void)
{
	m_NeedleCount++;

	if (m_NeedleCount >= 70)
	{
		CMapNeedle *pNeedle = CMapNeedle::Create(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * -300.0f, 400.0f, 0.0f));
		pNeedle->SetPos(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * -300.0f, 400.0f, 0.0f));
		pNeedle->SetRotChange(true);
		pNeedle->SetMoveWight(400.0f);
		pNeedle->SetMoveSpeed(0.006f);

		pNeedle = CMapNeedle::Create(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * 300.0f, 400.0f, 0.0f));
		pNeedle->SetPos(D3DXVECTOR3(m_fNeedleSet + m_NeedleSet * 300.0f, 400.0f, 0.0f));
		pNeedle->SetRotChange(true);
		pNeedle->SetMoveWight(400.0f);
		pNeedle->SetMoveSpeed(0.006f);

		m_NeedleCount = 0;
		m_NeedleSet++;

		if (m_NeedleSet >= 4)
		{
			m_NeedleSet = 0;
			m_bNeedle = false;
			m_bAttack = false;
			m_AttackCount = 0;
		}
	}
}

//====================================================================
//無敵攻撃
//====================================================================
void CBossLevel::AtkNoDamage(void)
{
	if (m_nNoDamageCount > 0)
	{
		m_nNoDamageCount--;

		D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();

		if (PlayerPos.x < m_pos.x - 10.0f)
		{
			m_move.x -= 2.0f;
		}
		else if(PlayerPos.x > m_pos.x + 10.0f)
		{
			m_move.x += 2.0f;
		}

		if (m_FallCount == 2)
		{
			if (m_nNoDamageCount % 80 == 0)
			{
				m_move.y = 23.0f;
			}
		}

		if (m_nNoDamageCount == 0)
		{
 			m_bRoundATK = false;
			m_pMotion->Set(ACTION_WAIT1);
			m_State = STATE_NORMAL;
		}
	}
}

//====================================================================
//移動処理
//====================================================================
void CBossLevel::Move(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();


	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true))
	{//攻撃中じゃない時にジャンプボタンを押したとき


			m_move.y = 15.0f;

	}

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true)
	{//左移動ボタンを押したとき
		m_move.x -= 10.0f;
	}

	if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true)
	{//右ボタンを押したとき
		m_move.x += 10.0f;
	}
}

//====================================================================
//向き処理
//====================================================================
void CBossLevel::Rot(void)
{
	D3DXVECTOR3 PlayerPos = CGame::GetPlayerLevel()->GetPos();

	if (PlayerPos.x < m_pos.x)
	{
		m_bRight = false;
		m_rot.y = 0.0f;
	}
	else
	{
		m_bRight = true;
		m_rot.y = 3.14f;
	}
}

//====================================================================
//ヒット処理
//====================================================================
void CBossLevel::HitDamage(void)
{
	if (m_State == STATE_NORMAL)
	{
		m_pMotion->Set(ACTION_DAMAGE);
		m_MotionCount = 28;
		m_BulletCount = 0;
		m_HitCount++;
		m_bBullet = false;
		m_bAttack = false;
	}
}


//====================================================================
//オブジェクトとの当たり判定処理
//====================================================================
bool CBossLevel::CollisionObject(D3DXVECTOR3 *pos, bool bX)
{
	if (m_State == STATE_NORMAL || m_State == STATE_NODAMAGE)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();			//種類を取得

				if (type == TYPE_MAPBLOCK)
				{//種類がブロックの時

					D3DXVECTOR3 Objpos = pObj->GetPos();
					float ObjWight = pObj->GetWight();
					float ObjHeight = pObj->GetHeight();

					if (bX == false)
					{
						if (
							(pos->y < Objpos.y + ObjHeight &&
								m_posOld.y >= Objpos.y + ObjHeight) &&
							pos->x + m_Size > Objpos.x - ObjWight &&
							pos->x - m_Size < Objpos.x + ObjWight
							)
						{//上からめり込んだ時
							pos->y = Objpos.y + ObjHeight;		//ブロックのうえにたたせる
							m_move.y = 0.0f;					//移動量を０にする
							m_bMiniJump = false;
							m_bJump = false;
						}

						if (
							(pos->y + m_Size > Objpos.y - ObjHeight &&
								m_posOld.y <= Objpos.y - ObjHeight) &&
							pos->x + m_Size > Objpos.x - ObjWight &&
							pos->x - m_Size < Objpos.x + ObjWight
							)
						{//下からめり込んだ時
							pos->y = Objpos.y - ObjHeight - m_Size;		//ブロックの下で止める
							m_move.y = 0.0f;					//移動量を０にする
						}
					}
					else
					{
						if (
							(pos->x + m_Size > Objpos.x - ObjWight &&
								m_posOld.x + m_Size <= Objpos.x - ObjWight) &&
							pos->y + m_Size > Objpos.y - ObjHeight &&
							pos->y < Objpos.y + ObjHeight
							)
						{//左からめり込んだ時
							pos->x = Objpos.x - ObjWight - m_Size;		//ブロックの左で止める
							m_move.x = 0.0f;					//移動量を０にする
						}

						if (
							(pos->x - m_Size < Objpos.x + ObjWight &&
								m_posOld.x - m_Size >= Objpos.x + ObjWight) &&
							pos->y + m_Size > Objpos.y - ObjHeight &&
							pos->y < Objpos.y + ObjHeight
							)
						{//右からめり込んだ時
							pos->x = Objpos.x + ObjWight + m_Size;		//ブロックの右で止める
							m_move.x = 0.0f;					//移動量を０にする
						}
					}
				}

				pObj = pObjNext;
			}
		}
	}
	return false;
}

//====================================================================
//当たり判定処理
//====================================================================
bool CBossLevel::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX)
{
	bool bOn = false;

	float myWight = m_Size;
	float myHeight = m_Size;


	if (bX == false)
	{
		if (
			(pPos->y < m_pos.y + myHeight &&
			pPosOld.y >= m_pos.y + myHeight) &&
			pPos->x + fWidth > m_pos.x - myWight &&
			pPos->x - fWidth < m_pos.x + myWight
			)
		{//上からめり込んだ時
			bOn = true;
			pPos->y = m_pos.y + myHeight;		//ブロックのうえにたたせる
			pMove->y = 0.0f;					//移動量を０にする
			*bHit = true;

			HitDamage();
		}

		if (
			(pPos->y + fHeight > m_pos.y - myHeight &&
				pPosOld.y <= m_pos.y - myHeight) &&
			pPos->x + fWidth > m_pos.x - myWight &&
			pPos->x - fWidth < m_pos.x + myWight
			)
		{//下からめり込んだ時
			*bJumpMove = false;
			pPos->y = m_pos.y - myHeight - fHeight;		//ブロックの下で止める
			pMove->y = 0.0f;					//移動量を０にする
			*bHit = true;
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > m_pos.x - myWight &&
				pPosOld.x + fWidth <= m_pos.x - myWight) &&
			pPos->y + fHeight  > m_pos.y - myHeight &&
			pPos->y  < m_pos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = m_pos.x - myWight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
			*bHit = true;

			if (m_State != STATE_NODAMAGE)
			{
				m_move.x = 100.0f;
				m_move.y = 10.0f;
			}

			HitDamage();
		}

		if (
			(pPos->x - fWidth < m_pos.x + myWight &&
				pPosOld.x - fWidth >= m_pos.x + myWight) &&
			pPos->y + fHeight  > m_pos.y - myHeight &&
			pPos->y < m_pos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = m_pos.x + myWight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
			*bHit = true;

			if (m_State != STATE_NODAMAGE)
			{
				m_move.x = -100.0f;
				m_move.y = 10.0f;
			}

			HitDamage();
		}
	}

	return bOn;
}

//====================================================================
//描画処理
//====================================================================
void CBossLevel::Draw(void)
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

//====================================================================
//描画処理
//====================================================================
void CBossLevel::LoadLevelData(const char *pFilename)
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