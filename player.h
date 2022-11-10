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
class CIcon;
class CBillboard;
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
	// 列挙型
	//-------------------------------------------------------------------------
	enum EMotion
	{
		MOTION_NONE = 0,
		MOTION_MOVE,
		MOTION_SCREW,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_BURABURA,
		MOTION_PUSH,
		MOTION_MAX
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
	void HalfWayPoint(D3DXVECTOR3 &pos);				// 中間地点処理

	void Move();

	// Setter
	void SetType(EPLAYER type);								// タイプ設定処理
	void SetSpeed(float speed);								// プレイヤー移動スピード設定処理
	void SetMotionType(EMotion inMotion);					// プレイヤー移動スピード設定処理
	void SetIsMove(bool isMove) { m_isMove = isMove; }		// 移動を行う有無
	void SetKeyIndex(int index) { m_keyIndex = index; }

	// Getter
	EPLAYER GetPlayerType(void) { return m_nType; }		// プレイヤータイプ取得処理
	int GetKeyIndex() { return m_keyIndex; }

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

	bool m_HalfWayPointFlag;			// 中間地点まで到達したかフラグ

	bool m_isMove;						// 移動を行うか否か

	EMotion m_moutionType;
	int m_keyIndex;						// 入力デバイスの番号

	CParticle *m_pParticle;				// パーティクルのポインタ
	CIcon *m_pIcon;

	int m_nRopeCnt;
	CBillboard *m_pRope;
};
#endif