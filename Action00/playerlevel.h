//============================================
//
//	プレイヤーの処理 [playerlevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PLAYERLEVEL_H_
#define _PLAYERLEVEL_H_

#include "object.h"

//前方宣言
class CModel;
class CMotion;

//オブジェクトプレイヤークラス
class CPlayerLevel : public CObject
{
public:
	CPlayerLevel();
	~CPlayerLevel();

	//プレイヤーのモーション
	typedef enum
	{
		ACTION_WAIT = 0,
		ACTION_MOVE,
		ACTION_WALLATTACK,
		ACTION_JAMP,
		ACTION_MAX,

	}ACTION_TYPE;

	//プレイヤーのモーション
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DEATH,
		STATE_WAIT,
		STATE_NODAMAGE,
		STATE_MAX,
		
	}STATE;

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CPlayerLevel *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadLevelData(const char *pFilename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetWight(float Wight) { m_fWight = Wight; }
	float GetWight(void) { return m_fWight; }
	void SetHeight(float Height) { m_fHeight = Height; }
	float GetHeight(void) { return m_fHeight; }
	void SetReSpownPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetReSpownPos(void) { return m_ReSpownPos; }
	STATE GetState(void) { return m_State; }
	void HitDamage(void);								//攻撃を受けた時の処理

private:
	void EventManager(void);							//ゲーム内イベントの管理
	void StateManager(void);							//状態管理
	void Move(void);									//移動処理
	void Rot(void);										//移動方向処理
	void ActionState(void);								//モーションと状態の管理
	void WallAttack(void);								//壁を発生させて攻撃
	void WallJamp(void);								//壁を発生させてジャンプ
	void WallMoveManager(void);							//移動中の岩エフェクトの管理
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//オブジェクトとの当たり判定
	void CollisionBoss(void);							//ボスとの当たり判定
	void DeleteMap(void);								//マップの削除
	
	ACTION_TYPE m_Action;
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_posOld;		//過去の位置
	D3DXVECTOR3 m_ReSpownPos;	//復活地点
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//向き
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	bool m_bWallJump;			//壁生成ジャンプ
	bool m_bRight;				//右向きか
	bool m_bAirAttack;			//空中で攻撃をしたかどうか
	int m_nJump;				//ジャンプ可能な回数
	int m_nActionCount;			//状態のカウント
	int m_nAttackCount;			//攻撃のカウント
	int m_nWallMoveCount;		//移動のカウント
	int m_nActionNotCount;		//行動不能のカウント
	float m_fWight;				//幅
	float m_fHeight;			//高さ
	STATE m_State;				//状態
	int m_nStateCount;			//状態管理用カウント
	bool m_bHit;				//攻撃をくらったかどうか
	bool m_GameEnd;				//ゲームが終わったかどうか

	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;
};

#endif