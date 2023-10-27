//============================================
//
//	タイムの処理 [time.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define NUM_TIME (2)		//スコアの桁数

//前方宣言
class CObject;
class CNumber;

//多重背景クラス
class CTime : public CObject
{
public:
	CTime();
	~CTime();

	static CTime *Create();
	static void SetTime(int Time) { m_nTime = Time; }
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	static void ReSetCount(void) { m_nCount = 0; }

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CNumber *m_apObject[NUM_TIME];
	static D3DXVECTOR3 m_pos;
	static int m_nCount;
	static int m_nTime;
	static int m_nNumber[NUM_TIME];
};

#endif