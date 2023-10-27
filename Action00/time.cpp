//============================================
//
//	タイムの処理 [time.cpp]
//	Author:sakamoto kai
//
//============================================
#include "time.h"
#include "number.h"
#include "game.h"
#include "playerlevel.h"

//マクロ定義
#define SPACE_TIME (60.0f)		//タイム同士の隙間

//静的メンバ変数宣言
CNumber *CTime::m_apObject[NUM_TIME] = {};
D3DXVECTOR3 CTime::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CTime::m_nTime = 0;
int CTime::m_nCount = 0;
int CTime::m_nNumber[NUM_TIME] = { 0 };

//====================================================================
//コンストラクタ
//====================================================================
CTime::CTime()
{

}

//====================================================================
//デストラクタ
//====================================================================
CTime::~CTime()
{

}

//====================================================================
//生成処理
//====================================================================
CTime *CTime::Create()
{
	CTime *pMultiBG = NULL;

	if (pMultiBG == NULL)
	{
		//オブジェクト2Dの生成
		pMultiBG = new CTime();
	}

	//オブジェクトの初期化処理
	if (FAILED(pMultiBG->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pMultiBG;
}

//====================================================================
//タイムの初期化
//====================================================================
HRESULT CTime::Init(void)
{
	SetType(CObject::TYPE_MULTIBG);

	SetPos(D3DXVECTOR3(580.0f, 60.0f, 0.0f));

	SetTime(10);

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = CNumber::Create();
			m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * SPACE_TIME), m_pos.y, m_pos.z));
		}
	}
	return S_OK;
}

//====================================================================
//タイムの終了
//====================================================================
void CTime::Uninit(void)
{
	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
			m_apObject[nCntObject] = NULL;
		}
	}

	SetDeathFlag(true);
}

//====================================================================
//タイムの更新
//====================================================================
void CTime::Update(void)
{
	if (m_nTime > 0)
	{
		m_nCount++;
	}
	else
	{
		CGame::GetPlayerLevel()->HitDamage();
	}

	if (m_nCount >= 60)
	{
		m_nCount = 0;
		m_nTime--;
	}

	m_nNumber[0] = m_nTime % 100 / 10;
	m_nNumber[1] = m_nTime % 10 / 1;

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		m_apObject[nCntObject]->SetNumber(m_nNumber[nCntObject]);
	}
}

//====================================================================
//タイムの描画
//====================================================================
void CTime::Draw(void)
{

}