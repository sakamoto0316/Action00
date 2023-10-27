//============================================
//
//	マップの中の大砲 [MapCannon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CANNONBULLET_H_
#define _CANNONBULLET_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CCannonBullet : public CObjectXtex
{
public:

	CCannonBullet(int nPriority = 3);
	~CCannonBullet();

	static CCannonBullet *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionObject(D3DXVECTOR3 pos);	//オブジェクトとの当たり判定

	void SetMove(D3DXVECTOR3 Move) { m_move = Move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;				//当たり判定用の座標
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
};
#endif