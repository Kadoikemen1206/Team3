//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "motion_model3D.h"

//=============================================================================
// 前方定義
//=============================================================================
class CShadow;
class CParticle;

//=============================================================================
// クラスの定義
//=============================================================================
class CPlayer : public CMotionModel3D
{
public:
	static const float SPEED_POWER;
	static const float JUMP_POWER;
	static const float GRAVITY_POWER;

public:
	//-------------------------------------------------------------------------
	// 列挙型
	//-------------------------------------------------------------------------
	enum EPLAYER
	{
		EPLAYER_NONE = 0,
		EPLAYER_1P,
		EPLAYER_2P,
		EPLAYER_MAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CPlayer(int nPriority = PRIORITY_LEVEL3);
	~CPlayer() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;							// 初期化処理
	void Update() override;								// 更新処理
	void Respawn(D3DXVECTOR3 &pos);						// リスポーン処理

	// Setter
	void SetType(EPLAYER type);							// タイプ設定処理
	void SetSpeed(float speed);							// プレイヤー移動スピード設定処理

	// Getter
	EPLAYER GetPlayerType(void) { return m_nType; }		// プレイヤータイプ取得処理

	static CPlayer *Create(EPLAYER type, const D3DXVECTOR3 pos, int nPriority);	// 生成処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_move;					// プレイヤーの移動量
	D3DXVECTOR3 m_rotDest;				// 目的の角度
	D3DXVECTOR3 m_posOld;				// 前回の位置
	EPLAYER m_nType;					// 1Pと2Pのタイプ分け
	int m_nSmokeCnt;					// スモークの状態
	float m_nSpeed;						// スピード
	bool m_bJumpFlag;					// ジャンプしたかどうかのフラグ
	bool m_bIsLanding;					// モデルとの当たり判定フラグ(左右,奥,手前)
	bool m_bIsLandingUp;				// モデルとの当たり判定フラグ(上側)

	int m_moutionType;

	CParticle *m_pParticle;				// パーティクルのポインタ
};
#endif