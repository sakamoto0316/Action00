//============================================
//
//	マップ中のすり抜け床 [MapPitFloor.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPPITFLOOR_H_
#define _MAPPITFLOOR_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CMapPitFloor : public CObjectXtex
{
public:

	CMapPitFloor(int nPriority = 3);
	~CMapPitFloor();

	static CMapPitFloor *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;		//当たり判定用の座標
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
};
#endif