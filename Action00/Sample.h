//============================================
//
//	ゲーム画面 [game.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include "main.h"
#include "manager.h"

//前方宣言
class CObject2D;

//シーンクラス
class CSample : public CScene
{
public:
	CSample();
	~CSample();

	void Sample(void);

private:
	CObject2D *m_pSample2D;
};

#endif