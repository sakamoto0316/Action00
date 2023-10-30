//============================================
//
//	エディット [Edit.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"
#include "object.h"

#define SET_BLOCK_WIGHT (20)
#define SET_BLOCK_HEIGHT (25)
#define DATA_NAME ("data\\TXT\\ShortMap")	//スタートメッセージがあるかどうかの確認

//前方宣言
class CMapBlock;
class CMapNeedle;
class CMapNeedleUD;
class CMapNeedleLR;
class CMapDoor;
class CMapSwitch;
class CMapPitFloor;
class CMapCannon;
class CMapCheckPoint;

//マップクラス
class CEdit
{
public:
	CEdit();
	~CEdit();

	static CEdit *Create();
	void Uninit(void);
	void Update(void);

	void LoadData(char *Name, D3DXVECTOR3 pos);

	D3DXVECTOR3 GetEditPos(void) { return m_EditPos; }
protected:

private:
	void DeleteObject(D3DXVECTOR3 pos);
	void DebugObject(void);
	void SaveData(void);

	static CMapBlock *m_EditBlock;
	static CMapNeedle *m_EditNeedle;
	static CMapNeedleUD *m_EditNeedleUD;
	static CMapNeedleLR *m_EditNeedleLR;
	static CMapDoor *m_EditDoor;
	static CMapSwitch *m_EditSwitch;
	static CMapPitFloor *m_EditPitFloor;
	static CMapCannon *m_EditCannon;
	static CMapCheckPoint *m_EditCheckPoint;
	int ObjectType;
	int m_HeightNumber;			//縦の番号
	D3DXVECTOR3 m_EditPos;		//座標
	D3DXVECTOR3 m_EditPos2;		//座標
	bool m_RotChange;			//座標と向きの切り替え
	int m_RotSelecet;			//向きの切り替え
	float m_fNeedleMoveWight;	//とげの移動範囲
	float m_fNeedleMoveSpeed;	//とげの移動速度
	int m_nSideCount;				//左右移動の長押しカウント
};
#endif