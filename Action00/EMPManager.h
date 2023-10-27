//============================================
//
//	エフェクト処理 [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EMPMANGER_H_
#define _EMPMANGER_H_

#include "main.h"
#include "objectBillboard.h"

//オブジェクトプレイヤークラス
class CEMPManager : public CObject
{
public:

	CEMPManager(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType, int nPriority = 4);
	~CEMPManager();

	static CEMPManager *Create(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMoveParticle(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType);

private:
	int m_nType;					//種類
	int m_nPSetWave;				//出現ウェーブ
	int m_nPSetCount;				//出現カウント
	int m_nPSetCountMax;			//出現カウントの最大値
	D3DXVECTOR3 m_Ppos;				//位置
	float m_nPRadius;				//大きさ
	float m_nPDel;					//消滅速度
};
#endif