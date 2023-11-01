//============================================
//
//	ボスの処理 [bosslevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BOSSLEVEL_H_
#define _BOSSLEVEL_H_

#include "object.h"

//前方宣言
class CModel;
class CMotion;
class CObject2D; 
class CLifeGauge;

//オブジェクトプレイヤークラス
class CBossLevel : public CObject
{
public:
	CBossLevel();
	~CBossLevel();

	//ボスのモーション
	typedef enum
	{
		ACTION_WAIT1 = 0,
		ACTION_DAMAGE,
		ACTION_BULLETATTACK,
		ACTION_JAMPATTACK,
		ACTION_MAX,

	}ACTION_TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_NODAMAGE,
		STATE_WAIT,
		STATE_SPAWN,
		STATE_DEATH,
		STATE_SET,
		STATE_MAX,
	}STATE;

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CBossLevel *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadLevelData(const char *pFilename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	STATE GetState(void) { return m_State; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetSize(float Size) { m_Size = Size; }
	float GetSize(void) { return m_Size; }
	float GetWight(void) { return m_Size; }
	void SetNULL(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool *bJumpMove, bool *bHit, bool bX);

private:
	bool CollisionObject(D3DXVECTOR3 *pos, bool bX);	//オブジェクトとの当たり判定
	void Move(void);									//移動処理
	void Rot(void);										//向き処理
	void HitDamage(void);								//移動処理
	void StateManager(void);							//状態管理
	void SetBullet(void);								//弾の生成
	void SetNeedle(void);								//とげの生成
	void AttackPattern(void);							//攻撃パターン
	void AtkMiniJump(void);								//小ジャンプ攻撃
	void AtkJump(void);									//ジャンプ攻撃
	void AtkBullet(void);								//射撃攻撃
	void AtkNeedle(void);								//とげ攻撃
	void AtkNoDamage(void);								//無敵攻撃

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_NeedlePos;//位置
	int m_nNeedleEffect;	//位置
	float m_Size;			//大きさ
	D3DXVECTOR3 m_posOld;	//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き
	bool m_bHit;			//当たっているかどうか
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	int m_MotionCount;		//モーションカウント
	int m_nLife;			//体力
	int m_AttackCount;		//攻撃のカウント
	int m_BulletCount;		//攻撃のカウント
	int m_NeedleCount;		//とげ生成のカウント
	int m_NeedleSet;		//とげ生成のかず
	bool m_bAttack;			//攻撃中か否か
	bool m_bJump;			//ジャンプ中か否か
	bool m_bMiniJump;		//ジャンプ中か否か
	bool m_bRight;			//右向きかどうか
	bool m_bBullet;			//射撃中かどうか
	bool m_bNeedle;			//とげ生成中かどうか
	bool m_bRoundATK;		//ラウンドごとの無敵攻撃
	int m_nNoDamageCount;	//無敵攻撃の時間
	float m_fNeedleSet;		//とげ生成位置の設定
	STATE m_State;			//ボスの状態
	int m_nStateCount;		//状態カウント
	int m_FallCount;		//落下カウント
	int m_HitCount;			//被弾カウント

	CLifeGauge *m_pLifeGauge;		//体力ゲージ
	CLifeGauge *m_pLifeFG;			//体力ゲージの前面ポリゴン
	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;

	CObject2D *m_pLife;
};

#endif