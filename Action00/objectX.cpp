//============================================
//
//	オブジェクトXファイル [objectX.cpp]
//	Author:sakamoto kai
//
//============================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "Xmodel.h"
#include "texture.h"

#define POLYDON_SIZE (200.0f)

//====================================================================
//コンストラクタ
//====================================================================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_dwNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MatColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bUseColor = false;
}

//====================================================================
//デストラクタ
//====================================================================
CObjectX::~CObjectX()
{

}

//====================================================================
//生成処理
//====================================================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObjectX = NULL;

	if (pObjectX == NULL)
	{
		//オブジェクト3Dの生成
		pObjectX = new CObjectX();
	}

	//オブジェクトの初期化処理
	if (FAILED(pObjectX->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pObjectX;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CObjectX::Init(void)
{
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CObjectX::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		//メモリを開放する
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//更新処理
//====================================================================
void CObjectX::Update(void)
{
	//SetVerTex();
}

//====================================================================
//描画処理
//====================================================================
void CObjectX::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice =CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xモデルの取得
	CXModel::XModel *pXmodel =CManager::GetInstance()->GetXModel()->GetXModel(GetIdxXModel());
	CTexture *pTexture =CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

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

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		if (m_bUseColor == true)
		{
			m_StateMat.MatD3D.Diffuse = m_MatColor;
			pDevice->SetMaterial(&m_StateMat.MatD3D);
		}
		else
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}

		//テクスチャの設定
		//pDevice->SetTexture(0, m_pTexture[nCntMat]);
		int Idex = GetIdxTexture(nCntMat);
		if (Idex != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(Idex));
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		//モデル(パーツ)の描画
		pXmodel->m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//モデル情報の割り当て
//====================================================================
void CObjectX::BindFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pdwNumMat)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice =CManager::GetInstance()->GetRenderer()->GetDevice();
	//D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	////情報の割り当て
	//m_pMesh = pMesh;
	//m_pBuffMat = pBuffMat;
	//m_dwNumMat = pdwNumMat;

	////Xモデルの取得
	//CXModel::XModel *pXmodel =CManager::GetInstance()->GetXModel()->GetXModel(GetIdxXModel());

	////テクスチャのメモリを確保
	//if (m_pTexture == NULL)
	//{
	//	//メモリを確保する
	//	m_pTexture = new LPDIRECT3DTEXTURE9[pXmodel->m_dwNumMat];
	//}

	////マテリアル情報に対するポインタを所得
	//pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		//テクスチャの読み込み
	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{
	//		m_pTexture[nCntMat] = NULL;
	//	}
	//}
}

//====================================================================
//頂点座標の設定
//====================================================================
void CObjectX::SetVerTex(void)
{

}

//====================================================================
//テクスチャ座標の設定
//====================================================================
void CObjectX::SetAnim(D3DXVECTOR2 Tex)
{

}

//====================================================================
//頂点カラーの設定
//====================================================================
void CObjectX::SetColor(D3DXCOLOR col)
{

}