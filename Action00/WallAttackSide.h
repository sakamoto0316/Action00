//============================================
//
//	横方向への壁生成攻撃 [WallAttackSide.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _WALLATTACKSIDE_H_
#define _WALLATTACKSIDE_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CWallAttackSide : public CObjectXtex
{
public:

	CWallAttackSide(bool bRight, int nPriority = 3);
	~CWallAttackSide();

	static CWallAttackSide *Create(bool bRight);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }

private:
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//オブジェクトとの当たり判定

	D3DXCOLOR m_BlockColor;
	float m_ColorA;
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;				//当たり判定用の座標

	D3DXVECTOR3 m_posOld;					//過去の位置	
	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
	float m_fUpPos;							//上昇量	
	bool m_bRight;							//右向きかどうか	
	bool m_bFall;							//落下するかどうか
	bool m_bBreak;							//破壊するかどうか
	int m_nLife;							//寿命
};
#endif