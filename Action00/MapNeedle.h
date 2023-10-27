//============================================
//
//	とげ [MapNeedle.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPNEEDLE_H_
#define _MAPNEEDLE_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CMapNeedle : public CObjectXtex
{
public:

	CMapNeedle(D3DXVECTOR3 StartPos,int nPriority = 0);
	~CMapNeedle();

	static CMapNeedle *Create(D3DXVECTOR3 StartPos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);
	void SetRotChange(bool bChange) { m_bRotChange = bChange; }
	bool GetRotChange(void) { return m_bRotChange; }
	void SetMoveSpeed(float fSpeed) { m_MoveSpeed = fSpeed; }
	float GetMoveSpeed(void) { return m_MoveSpeed; }
	void SetMoveWight(float fWight) { m_fMoveWight = fWight; }
	float GetMoveWight(void) { return m_fMoveWight; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;				//当たり判定用の座標
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_StartPos;					//開始時の位置	
	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
	float m_fMoveWight;						//到着点までの距離	
	bool m_bRotChange;						//上下左右の向き情報	
	float m_MoveSpeed;						//とげの移動スピード	
};
#endif