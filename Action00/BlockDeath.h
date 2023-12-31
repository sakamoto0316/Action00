//============================================
//
//	死亡時のブロック演出 [BlockDeath.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BLOCKDEATH_H_
#define _BLOCKDEATH_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CBlockDeath : public CObjectXtex
{
public:

	CBlockDeath(int nPriority = 3);
	~CBlockDeath();

	static CBlockDeath *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
};
#endif