//============================================
//
//	マップの中のスイッチ [MapSwitch.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAPSWITCH_H_
#define _MAPSWITCH_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言
class CMapDoor;

//オブジェクトプレイヤークラス
class CMapSwitch : public CObjectXtex
{
public:

	CMapSwitch(int nPriority = 3);
	~CMapSwitch();

	static CMapSwitch *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool b_Jamp);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);

	CMapSwitch *GetSwitch(void) { return m_pSwitch; }
	CMapDoor *GetDoor(void) { return m_pDoor; }
	void SetDoorSwitch(D3DXVECTOR3 Pos) { m_SwitchPos = Pos; }
	void SetDoorPos(D3DXVECTOR3 Pos) { m_DoorPos = Pos; }

private:
	void OnCountDown(void);					//オンからオフになるまでのカウント

	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static D3DXVECTOR3 m_CollisionPos;		//当たり判定用の座標
	static bool m_bCollision;				//当たり判定用の座標
	int m_nIdxTexture;						//テクスチャの番号

	CMapSwitch *m_pSwitch;					//連動するスイッチ
	D3DXVECTOR3 m_SwitchPos;				//スイッチの座標
	CMapDoor *m_pDoor;						//連動するドア
	D3DXVECTOR3 m_DoorPos;					//ドアの座標	
	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//向き	
	bool SwitchOn;							//スイッチが起動しているかどうか
	int OnTime;								//スイッチの起動時間
	bool bSetDoor;							//ドアを配置したかどうか
};
#endif