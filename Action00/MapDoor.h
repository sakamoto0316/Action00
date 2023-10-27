//============================================
//
//	マップの中のドア [MapDoor.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPDOOR_H_
#define _MAPDOOR_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CMapDoor : public CObjectXtex
{
public:

	CMapDoor(D3DXVECTOR3 Pos, int nPriority = 3);
	~CMapDoor();

	static CMapDoor *Create(D3DXVECTOR3 Pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool GetOpen(void) { return m_bOpen; }
	void SetOpen(bool Set) { m_bOpen = Set; }
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; }
	void SetStartPos(D3DXVECTOR3 Pos) { m_StartPos = Pos; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);
	bool CollisionObject(D3DXVECTOR3 pos);	//オブジェクトとの当たり判定

private:
	void DoorOpen(void);
	void DoorClose(void);

	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;				//当たり判定用の座標
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_StartPos;					//出現時の位置	
	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
	bool m_bOpen;							//ドアが開いているかどうか
};
#endif