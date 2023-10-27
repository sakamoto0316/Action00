//============================================
//
//	タイトル画面 [title.cpp]
//	Author:sakamoto kai
//
//============================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "player3D.h"
#include "break_block3D.h"
#include "BlockUI.h"
#include "ranking.h"
#include "TitleUI.h"
#include "particle.h"
#include "sound.h"

//静的メンバ変数宣言
CObject2D *CTitle::m_pTitle = NULL;
int CTitle::m_nSelect = 1;
int CTitle::m_CreateCount = 0;
//====================================================================
//コンストラクタ
//====================================================================
CTitle::CTitle()
{
	m_nSelect = 1;
	m_CreateCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CTitle::~CTitle()
{

}

//====================================================================
//初期化処理
//====================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	m_pTitle = CObject2D::Create();
	m_pTitle->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pTitle->SetWight(1280.0f);
	m_pTitle->SetHeight(720.0f);
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_pTitle->SetIdx(pTexture->Regist("data\\TEXTURE\\Title.png"));

	//for (int nCnt = 0; nCnt < 10; nCnt++)
	//{
	//	m_pBlock3D = CBreak_Block3D::Create();
	//	m_pBlock3D->bUseSet();
	//	m_pBlock3D->SetPos(D3DXVECTOR3(-240.0f + nCnt * 40.0f, 0.0f, 0.0f));
	//	m_pBlock3D->SetWNumber(5);
	//}

	////BGMの再生
	//m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CTitle::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//====================================================================
//更新処理
//====================================================================
void CTitle::Update(void)
{
	//選択処理
	Select();

	m_CreateCount++;
}

//====================================================================
//描画処理
//====================================================================
void CTitle::Draw(void)
{

}

//====================================================================
//選択処理
//====================================================================
void CTitle::Select(void)
{
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		CFade::SetFade(CScene::MODE_GAME);
	}
}

//====================================================================
//選択項目のカラー変更処理
//====================================================================
void CTitle::SetSelectColor(int nCnt)
{
	m_nSelect = nCnt;
}