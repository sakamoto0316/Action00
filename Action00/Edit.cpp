//============================================
//
//	エディット [Edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Edit.h"
#include "object.h"
#include "MapBlock.h"
#include "renderer.h"
#include "break_block3D.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "debugproc.h"
#include "Map2D.h"
#include "MapNeedleUD.h"
#include "MapNeedleLR.h"
#include "MapDoor.h"
#include "MapSwitch.h"
#include "MapPitFloor.h"
#include "MapCannon.h"
#include "MapNeedle.h"
#include "MapCheckPoint.h"
#include "Effect.h"
#include "debugproc.h"

//マクロ定義
#define SPOWN_MAP (1000)
#define GAME_WIGHT (240.0f)					//画面横の移動制限
#define NUM_OBJECT (8)						//マップに出すオブジェクトの種類数
#define START_OK ("STARTSETSTAGE")			//スタートメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETSTAGE")			//エンドメッセージがあるかどうかの確認
#define BLOCK_SET ("STARTSETBLOCK")			//ブロックのセットメッセージ
#define NEEDLE_SET ("STARTSETNEEDLE")		//とげのセットメッセージ
#define NEEDLEUD_SET ("STARTSETNEEDLEUD")	//上下とげのセットメッセージ
#define NEEDLELR_SET ("STARTSETNEEDLELR")	//左右とげのセットメッセージ
#define DOOR_SET ("STARTSETDOOR")			//ドアのセットメッセージ
#define SWITCH_SET ("STARTSETSWITCH")		//スイッチのセットメッセージ
#define PITFLOOR_SET ("STARTSETPITFLOOR")	//すり抜け床のセットメッセージ
#define CANNON_SET ("STARTSETCANNON")		//大砲のセットメッセージ
#define CHECKPOINT_SET ("STARTCHECKPOINT")	//チェックポイントのセットメッセージ
#define DELETE_WIGHT (45.0f)				//削除処理の横の削除範囲
#define DELETE_HEIGHT (45.0f)				//削除処理の縦の削除範囲
#define SIDE_PRESSCOUNT (30)				//横に素早く移動するまでのカウント

//静的メンバ変数宣言
CMapBlock *CEdit::m_EditBlock = NULL;			//ブロックへのポインタ
CMapNeedle *CEdit::m_EditNeedle = NULL;			//横とげのポインタ
CMapNeedleUD *CEdit::m_EditNeedleUD = NULL;		//横とげのポインタ
CMapNeedleLR *CEdit::m_EditNeedleLR = NULL;		//縦とげのポインタ
CMapDoor *CEdit::m_EditDoor = NULL;				//ドアへのポインタ
CMapSwitch *CEdit::m_EditSwitch = NULL;			//スイッチへのポインタ
CMapPitFloor *CEdit::m_EditPitFloor = NULL;		//すり抜け床へのポインタ
CMapCannon *CEdit::m_EditCannon = NULL;			//大砲へのポインタ
CMapCheckPoint *CEdit::m_EditCheckPoint = NULL;	//チェックポイントへのポインタ

//====================================================================
//コンストラクタ
//====================================================================
CEdit::CEdit()
{
	m_EditPos = INITVECTOR3;
	m_EditPos2 = INITVECTOR3;

	m_HeightNumber = 0;					//縦の番号

	ObjectType = 0;
	m_RotChange = false;
	m_RotSelecet = 0;
	m_fNeedleMoveWight = 100.0f;
	m_fNeedleMoveSpeed = 0.005f;
	m_nSideCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CEdit::~CEdit()
{

}

//====================================================================
//生成処理
//====================================================================
CEdit *CEdit::Create()
{
	CEdit *pMap = NULL;

	if (pMap == NULL)
	{
		//オブジェクト2Dの生成
		pMap = new CEdit();
	}

	m_EditBlock = CMapBlock::Create();
	m_EditBlock->SetType(CObject::TYPE_EDIT);

	return pMap;
}

//====================================================================
//終了処理
//====================================================================
void CEdit::Uninit(void)
{

}


//====================================================================
//更新処理
//====================================================================
void CEdit::Update(void)
{
	CMapBlock *pEditBlock = NULL;
	CMapNeedle *pEditNeedle = NULL;
	CMapNeedleUD *pEditNeedleUD = NULL;
	CMapNeedleLR *pEditNeedleLR = NULL;
	CMapDoor *pEditDoor = NULL;
	CMapSwitch *pEditSwitch = NULL;
	CMapPitFloor *pEditPitFloor = NULL;
	CMapCannon *pEditCannon = NULL;
	CMapCheckPoint *pEditCheckPoint = NULL;

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//エディットの位置を動かす----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		m_EditPos.y += 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		m_EditPos.y -= 100.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_EditPos.x -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_EditPos.x += 100.0f;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x -= 100.0f;
		}
		m_nSideCount++;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x += 100.0f;
		}
		m_nSideCount++;
	}

	if (pInputKeyboard->GetRerease(DIK_A) == true ||
		pInputKeyboard->GetRerease(DIK_D) == true)
	{
		m_nSideCount = 0;
	}

	//エディットの位置を動かす----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		m_EditPos2.y += 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		m_EditPos2.y -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		m_EditPos2.x -= 100.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		m_EditPos2.x += 100.0f;
	}

	//オブジェクト切り替え----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		switch (ObjectType)
		{
		case 0://ブロック
			m_EditBlock->Uninit();
			m_EditBlock = NULL;

			m_EditNeedleUD = CMapNeedleUD::Create(m_RotChange);
			m_EditNeedleUD->SetType(CObject::TYPE_EDIT);
			break;

		case 1://上下とげ
			m_EditNeedleUD->Uninit();
			m_EditNeedleUD = NULL;

			m_EditNeedleLR = CMapNeedleLR::Create(m_RotChange);
			m_EditNeedleLR->SetType(CObject::TYPE_EDIT);
			break;

		case 2://左右とげ
			m_EditNeedleLR->Uninit();
			m_EditNeedleLR = NULL;

			m_EditDoor = CMapDoor::Create(m_EditPos);
			m_EditDoor->SetType(CObject::TYPE_EDIT);
			break;

		case 3://ドア
			m_EditDoor->Uninit();
			m_EditDoor = NULL;

			m_EditSwitch = CMapSwitch::Create();
			m_EditSwitch->SetType(CObject::TYPE_EDIT);
			break;

		case 4://スイッチ
			m_EditSwitch->Uninit();
			m_EditSwitch = NULL;

			m_EditPitFloor = CMapPitFloor::Create();
			m_EditPitFloor->SetType(CObject::TYPE_EDIT);
			break;

		case 5://すり抜け床
			m_EditPitFloor->Uninit();
			m_EditPitFloor = NULL;

			m_EditCannon = CMapCannon::Create();
			m_EditCannon->SetType(CObject::TYPE_EDIT);
			break;

		case 6://大砲
			m_EditCannon->Uninit();
			m_EditCannon = NULL;

			m_EditNeedle = CMapNeedle::Create(INITVECTOR3);
			m_EditNeedle->SetType(CObject::TYPE_EDIT);
			break;

		case 7://とげ
			m_EditNeedle->Uninit();
			m_EditNeedle = NULL;

			m_EditCheckPoint = CMapCheckPoint::Create();
			m_EditCheckPoint->SetType(CObject::TYPE_EDIT);
			break;

		case 8://チェックポイント
			m_EditCheckPoint->Uninit();
			m_EditCheckPoint = NULL;

			m_EditBlock = CMapBlock::Create();
			m_EditBlock->SetType(CObject::TYPE_EDIT);
			break;

		default:
			break;
		}

		ObjectType++;

		if (ObjectType > NUM_OBJECT)
		{
			ObjectType = 0;
		}
	}

	//向きと位置の切り替え----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_9) == true)
	{
		m_RotChange = m_RotChange ? false : true;

		m_RotSelecet++;

		if (m_RotSelecet == 4)
		{
			m_RotSelecet = 0;
		}
	}

	//とげの移動範囲調整----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_8) == true)
	{
		m_fNeedleMoveWight += 50.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{
		m_fNeedleMoveWight -= 50.0f;
	}

	//位置更新----------------------------------------------------------
	switch (ObjectType)
	{
	case 0://ブロック
		m_EditBlock->SetPos(m_EditPos);
		break;

	case 1://上下とげ
		if (m_RotChange == false)
		{
			m_EditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_EditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
		}
		else
		{
			m_EditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
			m_EditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + 50.0f, m_EditPos.z));
		}
		break;

	case 2://左右とげ
		if (m_RotChange == false)
		{
			m_EditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_EditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x + 50.0f, m_EditPos.y, m_EditPos.z));
		}
		else
		{
			m_EditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
			m_EditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x - 50.0f, m_EditPos.y, m_EditPos.z));
		}
		break;

	case 3://ドア
		m_EditDoor->SetPos(m_EditPos);
		break;

	case 4://スイッチ
		m_EditSwitch->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
		m_EditSwitch->GetDoor()->SetPos(m_EditPos2);
		break;

	case 5://すり抜け床
		m_EditPitFloor->SetPos(m_EditPos);
		break;

	case 6://大砲
		m_EditCannon->SetPos(m_EditPos);

		if (m_RotSelecet == 0)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.0f));
		}
		else if (m_RotSelecet == 1)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f));
		}
		else if (m_RotSelecet == 2)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 1.0f));
		}
		else if (m_RotSelecet == 3)
		{
			m_EditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));
		}
		break;

	case 7://とげ
		m_EditNeedle->SetPos(m_EditPos);

		if (m_RotChange == false)
		{
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CEffect *pEffect = CEffect::Create();
				pEffect->SetPos(D3DXVECTOR3(m_EditPos.x + m_fNeedleMoveWight * ((nCnt * 2) - 1), m_EditPos.y, m_EditPos.z));
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				CEffect *pEffect = CEffect::Create();
				pEffect->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + m_fNeedleMoveWight * ((nCnt * 2) - 1), m_EditPos.z));
			}
		}
		break;

	case 8://チェックポイント
		m_EditCheckPoint->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y, m_EditPos.z));
		break;

	default:
		break;
	}

	//オブジェクト設置----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		for (int nCnt = 0; nCnt < 19; nCnt++)
		{
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(D3DXVECTOR3(-900.0f + nCnt * 100.0f, 0.0f, 0.0f));
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(D3DXVECTOR3(-900.0f + nCnt * 100.0f, 1000.0f, 0.0f));
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		switch (ObjectType)
		{
		case 0://ブロック
			pEditBlock = CMapBlock::Create();
			pEditBlock->SetPos(m_EditPos);
			break;

		case 1://上下とげ
			pEditNeedleUD = CMapNeedleUD::Create(m_RotChange);

			if (m_RotChange == false)
			{
				pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pEditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
			}
			else
			{
				pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
				pEditNeedleUD->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y + 50.0f, m_EditPos.z));
			}
			break;

		case 2://左右とげ
			pEditNeedleLR = CMapNeedleLR::Create(m_RotChange);

			if (m_RotChange == false)
			{
				pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pEditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x + 50.0f, m_EditPos.y, m_EditPos.z));
			}
			else
			{
				pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
				pEditNeedleLR->SetPos(D3DXVECTOR3(m_EditPos.x - 50.0f, m_EditPos.y, m_EditPos.z));
			}
			break;

		case 3://ドア
			pEditDoor = CMapDoor::Create(m_EditPos);
			pEditDoor->SetPos(m_EditPos);
			break;

		case 4://スイッチ
			pEditSwitch = CMapSwitch::Create();
			pEditSwitch->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y - 50.0f, m_EditPos.z));
			pEditSwitch->GetDoor()->SetPos(m_EditPos2);
			pEditSwitch->SetDoorPos(m_EditPos2);
			break;

		case 5://すり抜け床
			pEditPitFloor = CMapPitFloor::Create();
			pEditPitFloor->SetPos(m_EditPos);
			break;

		case 6://大砲
			pEditCannon = CMapCannon::Create();
			pEditCannon->SetPos(m_EditPos);
			if (m_RotSelecet == 0)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.0f));
			}
			else if (m_RotSelecet == 1)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f));
			}
			else if (m_RotSelecet == 2)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 1.0f));
			}
			else if (m_RotSelecet == 3)
			{
				pEditCannon->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));
			}
			break;

		case 7://とげ
			pEditNeedle = CMapNeedle::Create(m_EditPos);
			pEditNeedle->SetPos(D3DXVECTOR3(m_EditPos));
			pEditNeedle->SetRotChange(m_RotChange);
			pEditNeedle->SetMoveWight(m_fNeedleMoveWight);
			pEditNeedle->SetMoveSpeed(m_fNeedleMoveSpeed);
			break;

		case 8://チェックポイント
			pEditCheckPoint = CMapCheckPoint::Create();
			pEditCheckPoint->SetPos(D3DXVECTOR3(m_EditPos.x, m_EditPos.y, m_EditPos.z + 50.0f));
			break;

		default:
			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		DeleteObject(m_EditPos);
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}

	DebugObject();
}

//====================================================================
//削除処理
//====================================================================
void CEdit::DeleteObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == CObject::TYPE_MAPBLOCK ||
				type == CObject::TYPE_MAPDOOR ||
				type == CObject::TYPE_MAPSWITCH ||
				type == CObject::TYPE_MAPNEEDLE ||
				type == CObject::TYPE_MAPNEEDLELR ||
				type == CObject::TYPE_MAPNEEDLEUD ||
				type == CObject::TYPE_MAPPITFLOOR ||
				type == CObject::TYPE_MAPCANNON ||
				type == CObject::TYPE_MAPCHECKPOINT)
			{//種類がブロックの時

				CObject::TYPE type = pObj->GetType();				//種類を取得
				D3DXVECTOR3 CollsionPos = pObj->GetPos();			//位置を取得
				float CollsionWight = pObj->GetWight() * 0.5f;		//幅を取得
				float CollsionHeight = pObj->GetHeight() * 0.5f;	//高さを取得
				float fmyWight = DELETE_WIGHT;						//中心からの幅
				float fmyHeight = DELETE_HEIGHT;					//中心からの高さ

				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					pObj->Uninit();
				}

			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//デバッグ表示
//====================================================================
void CEdit::DebugObject(void)
{
	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "ーーーーーエディットモードーーーーー");

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "操作説明ーー");
	//操作説明
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "移動：[W],[A],[S],[D]");
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト切り替え：[０]");
	CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト回転：[９]");

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "ーーエディット情報ーー");
	//オブジェクト
	switch (ObjectType)
	{
	case 0://ブロック
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[ブロック]");
		break;

	case 1://上下とげ
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[上下とげ]");
		break;

	case 2://左右とげ
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[左右とげ]");
		break;

	case 3://ドア
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[ドア]");
		break;

	case 4://スイッチ
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[スイッチ]");
		break;

	case 5://すり抜け床
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[すり抜け床]");
		break;

	case 6://大砲
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[大砲]");
		break;

	case 7://とげ
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[とげ]");
		break;

	case 8://チェックポイント
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "オブジェクト：[チェックポイント]");
		break;
	}

	//反転オンオフ
	if (m_RotChange == false)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "反転：[OFF]");
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "反転：[ON]");
	}

	//上下左右の向き
	if (m_RotSelecet == 0)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "向き：[左]");
	}
	else if (m_RotSelecet == 1)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "向き：[上]");
	}
	else if (m_RotSelecet == 2)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "向き：[右]");
	}
	else if (m_RotSelecet == 3)
	{
		CManager::GetInstance()->GetDebugProc()->Print("%s\n", "向き：[下]");
	}

	//とげの移動範囲
	CManager::GetInstance()->GetDebugProc()->Print("とげの移動範囲:[%f]\n",m_fNeedleMoveWight);

	CManager::GetInstance()->GetDebugProc()->Print("\n%s\n", "ーーーーーエディットモードーーーーー");
}

//====================================================================
//保存処理
//====================================================================
void CEdit::SaveData(void)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(DATA_NAME, "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ステージをセーブする開始の合図
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//種類を取得

				if (type == CObject::TYPE_MAPBLOCK)
				{//種類がブロックの時
					CMapBlock *m_pBlock = (CMapBlock*)pObj;

					fprintf(pFile, "%s\n", BLOCK_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pBlock->GetPos().x);
					fprintf(pFile, "%f ", m_pBlock->GetPos().y);
					fprintf(pFile, "%f\n", m_pBlock->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
				}
				else if (type == CObject::TYPE_MAPNEEDLE)
				{
					CMapNeedle *m_pNeedle = (CMapNeedle*)pObj;

					fprintf(pFile, "%s\n", NEEDLE_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pNeedle->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedle->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedle->GetPos().z);
					if (m_pNeedle->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%f\n", m_pNeedle->GetMoveWight());
					fprintf(pFile, "%f\n", m_pNeedle->GetMoveSpeed());

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLE");
				}
				else if (type == CObject::TYPE_MAPNEEDLEUD)
				{
					CMapNeedleUD *m_pNeedleUD = (CMapNeedleUD*)pObj;

					fprintf(pFile, "%s\n", NEEDLEUD_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pNeedleUD->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedleUD->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedleUD->GetPos().z);
					if (m_pNeedleUD->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLEUD");
				}
				else if (type == CObject::TYPE_MAPNEEDLELR)
				{
					CMapNeedleLR *m_pNeedleLR = (CMapNeedleLR*)pObj;

					fprintf(pFile, "%s\n", NEEDLELR_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pNeedleLR->GetPos().x);
					fprintf(pFile, "%f ", m_pNeedleLR->GetPos().y);
					fprintf(pFile, "%f\n", m_pNeedleLR->GetPos().z);
					if (m_pNeedleLR->GetRotChange() == false)
					{
						fprintf(pFile, "%s\n", "0");
					}
					else
					{
						fprintf(pFile, "%s\n", "1");
					}

					fprintf(pFile, "%s\n\n", "ENDSETNEEDLELR");
				}
				else if (type == CObject::TYPE_MAPDOOR)
				{
					CMapDoor *m_pMapdoor = (CMapDoor*)pObj;

					fprintf(pFile, "%s\n", DOOR_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pMapdoor->GetPos().x);
					fprintf(pFile, "%f ", m_pMapdoor->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapdoor->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETDOOR");
				}
				else if (type == CObject::TYPE_MAPSWITCH)
				{
					CMapSwitch *m_pMapSwitch = (CMapSwitch*)pObj;

					fprintf(pFile, "%s\n", SWITCH_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pMapSwitch->GetPos().x);
					fprintf(pFile, "%f ", m_pMapSwitch->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapSwitch->GetPos().z);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pMapSwitch->GetDoor()->GetPos().x);
					fprintf(pFile, "%f ", m_pMapSwitch->GetDoor()->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapSwitch->GetDoor()->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETSWITCH");
				}
				else if (type == CObject::TYPE_MAPPITFLOOR)
				{
					CMapPitFloor *m_pMapPitFloor = (CMapPitFloor*)pObj;

					fprintf(pFile, "%s\n", PITFLOOR_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pMapPitFloor->GetPos().x);
					fprintf(pFile, "%f ", m_pMapPitFloor->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapPitFloor->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETPITFLOOR");
				}
				else if (type == CObject::TYPE_MAPCANNON)
				{
					CMapCannon *m_pMapCannon = (CMapCannon*)pObj;

					fprintf(pFile, "%s\n", CANNON_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pMapCannon->GetPos().x);
					fprintf(pFile, "%f ", m_pMapCannon->GetPos().y);
					fprintf(pFile, "%f\n", m_pMapCannon->GetPos().z);

					fprintf(pFile, "%f ", m_pMapCannon->GetRot().x);
					fprintf(pFile, "%f ", m_pMapCannon->GetRot().y);
					fprintf(pFile, "%f\n", m_pMapCannon->GetRot().z);

					fprintf(pFile, "%s\n\n", "ENDSETCANNON");
				}
				else if (type == CObject::TYPE_MAPCHECKPOINT)
				{
					CMapCheckPoint *m_pCheckPoint = (CMapCheckPoint*)pObj;

					fprintf(pFile, "%s\n", CHECKPOINT_SET);

					//ステージをセーブした終了の合図
					fprintf(pFile, "%f ", m_pCheckPoint->GetPos().x);
					fprintf(pFile, "%f ", m_pCheckPoint->GetPos().y);
					fprintf(pFile, "%f\n", m_pCheckPoint->GetPos().z);

					fprintf(pFile, "%s\n\n", "ENDSETCHECKPOINT");
				}

				pObj = pObjNext;
			}
		}

		//ステージをセーブした終了の合図
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CEdit::LoadData(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		CMapBlock *pEditBlock = NULL;
		CMapNeedle *pEditNeedle = NULL;
		CMapNeedleUD *pEditNeedleUD = NULL;
		CMapNeedleLR *pEditNeedleLR = NULL;
		CMapDoor *pEditDoor = NULL;
		CMapSwitch *pEditSwitch = NULL;
		CMapPitFloor *pEditPitFloor = NULL;
		CMapCannon *pEditCannon = NULL;
		CMapCheckPoint *pEditCheckPoint = NULL;
		
		D3DXVECTOR3 SetPos = INITVECTOR3;
		D3DXVECTOR3 SetPos2 = INITVECTOR3;
		D3DXVECTOR3 SetRot = INITVECTOR3;
		int SetChangeRot = false;
		float SetMoveWight = 0.0f;
		float SetMoveSpeed = 0.0f;
		char aString[128] = {};			//ゴミ箱
		char aStartMessage[32] = {};	//スタートメッセージ
		char aSetMessage[32] = {};		//セットメッセージ
		char aEndMessage[32] = {};		//終了メッセージ
		char aType[32] = {};			//種類判別メッセージ

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
				else if (strcmp(&aSetMessage[0], BLOCK_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditBlock = CMapBlock::Create();
					pEditBlock->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], NEEDLE_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%f", &SetMoveWight);
					fscanf(pFile, "%f", &SetMoveSpeed);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedle = CMapNeedle::Create(pos + SetPos);
					pEditNeedle->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedle->SetRotChange(true);
					}
					else
					{
						pEditNeedle->SetRotChange(false);
					}
					pEditNeedle->SetMoveWight(SetMoveWight);
					pEditNeedle->SetMoveSpeed(SetMoveSpeed);
				}
				else if (strcmp(&aSetMessage[0], NEEDLEUD_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedleUD = CMapNeedleUD::Create(false);
					pEditNeedleUD->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedleUD->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
						pEditNeedleUD->SetRotChange(true);
					}
				}
				else if (strcmp(&aSetMessage[0], NEEDLELR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%d", &SetChangeRot);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditNeedleLR = CMapNeedleLR::Create(false);
					pEditNeedleLR->SetPos(D3DXVECTOR3(pos + SetPos));
					if (SetChangeRot == 1)
					{
						pEditNeedleLR->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
						pEditNeedleLR->SetRotChange(true);
					}
				}
				else if (strcmp(&aSetMessage[0], DOOR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditDoor = CMapDoor::Create(D3DXVECTOR3(pos + SetPos));
					pEditDoor->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], SWITCH_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%f", &SetPos2.x);
					fscanf(pFile, "%f", &SetPos2.y);
					fscanf(pFile, "%f", &SetPos2.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditSwitch = CMapSwitch::Create();
					pEditSwitch->SetPos(D3DXVECTOR3(pos + SetPos));
					pEditSwitch->SetDoorPos(pos + SetPos2);
				}
				else if (strcmp(&aSetMessage[0], PITFLOOR_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditPitFloor = CMapPitFloor::Create();
					pEditPitFloor->SetPos(D3DXVECTOR3(pos + SetPos));
				}
				else if (strcmp(&aSetMessage[0], CANNON_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);

					fscanf(pFile, "%f", &SetRot.x);
					fscanf(pFile, "%f", &SetRot.y);
					fscanf(pFile, "%f", &SetRot.z);

					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditCannon = CMapCannon::Create();
					pEditCannon->SetPos(D3DXVECTOR3(pos + SetPos));
					pEditCannon->SetRot(D3DXVECTOR3(SetRot));
				}
				else if (strcmp(&aSetMessage[0], CHECKPOINT_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);

					fscanf(pFile, "%s", &aSetMessage[0]);

					pEditCheckPoint = CMapCheckPoint::Create();
					pEditCheckPoint->SetPos(D3DXVECTOR3(pos + SetPos));
				}
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}