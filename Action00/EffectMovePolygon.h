//============================================
//
//	エフェクト処理 [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EFFECTMOVEPOLYGON_H_
#define _EFFECTMOVEPOLYGON_H_

#include "main.h"
#include "objectBillboard.h"

//オブジェクトプレイヤークラス
class CEffectMovePolygon : public CObjectBillboard
{
public:

	CEffectMovePolygon(int nPriority = 4);
	~CEffectMovePolygon();

	static CEffectMovePolygon *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRadius(float Radius) { m_fSetRadius = Radius; }
	float GetRadius(void) { return m_fDel; }
	void SetDel(float Del) { m_fDel = Del; }
	float GetDel(void) { return m_fDel; }
	void SetColer(D3DXCOLOR Coler) { m_col = Coler; }
	D3DXCOLOR GetColer(void) { return m_col; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }
	int GetIdx(void) { return m_nIdxTexture; }

private:
	D3DXVECTOR3 m_CenterPos;				//中心の座標	
	D3DXVECTOR3 m_VtxPos[4];				//頂点の座標	
	int m_nIdxTexture;						//テクスチャの番号
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャへのポインタ
	D3DXVECTOR3 m_move;						//移動量	
	float m_fRadius;						//半径(大きさ)	
	float m_fSetRadius;						//最終的な半径(大きさ)	
	float m_fDel;							//半径を小さくしていく値
	D3DXCOLOR m_col;						//色
	int m_nLife;							//寿命
	float m_fStartRadius;					//開始時の大きさ
	bool m_bStart;							//開始フラグ
	bool m_bCenter;							//中間フラグ
	bool m_bSet;							//出現フラグ
};
#endif