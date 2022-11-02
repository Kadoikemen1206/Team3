//=============================================================================
// particle.h
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"
#include <vector>

class CParticle : public CBillboard
{
public:
	enum EBehaviorType
	{
		BEHAVIOR_NONE = 0,
		BEHAVIOR_FLY,
		BEHAVIOR_FIREWORKS,
		BEHAVIOR_SMOKE,
		BEHAVIOR_MAX,
		BEHAVIOR_INVALID
	};

	struct SData
	{
		D3DXVECTOR3 destPos;	//目的の位置
		int frame;
	};

	explicit CParticle(int nPriority = PRIORITY_LEVEL3);
	~CParticle() override;

	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理

	//セッター
	void SetPath(std::string url) { m_path = url; }
	void SetBehavior(EBehaviorType behavior) { m_behavior = behavior; }
	void SetDelay(int time) { m_nDelay = time; }
	void SetGravity(bool set) { m_bGravity = set; }
	void SetGravity(bool set, float value) { m_bGravity = set, m_fFallSpeed = value; }
	void SetFade(bool set) { m_bFade = set; }
	void SetFade(bool set, float value) { m_bFade = set, m_fFadeValue = value; }
	void SetRotation(bool set, float value) { m_bRotate = set, m_fRotateSpeed = value; }
	void SetScaling(bool set) { m_bScaling = set; }
	void SetScaling(bool set, float value) { m_bScaling = set, m_fScalingValue = value; }
	void SetLocus(bool set) { m_bLocus = set; }
	void SetBounce(bool set) { m_bBounce = set; }
	void SetPosSpecify(bool set) { m_bPosSpecify = set; }
	void SetTransitionColor(bool set, D3DXCOLOR col) { m_bTransition = set, m_destCol = col; }

	//ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CParticle *Create(const D3DXVECTOR3 pos, EBehaviorType type, int nPriority);    // パーティクルの方で大体設定しちゃうとき用
	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const std::string url, int nPriority);    // 生成処理

private:
	void DetailSetting();
	void Preset();

	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_beginPos;				// 開始時の位置
	D3DXVECTOR3 m_posOld;				// 前回の位置
	D3DXVECTOR3 m_destPos;				// 目的の位置
	D3DXVECTOR3 m_lowerPos;
	D3DXVECTOR3 m_moveTransition;
	D3DXCOLOR m_col;					// 色
	D3DXCOLOR m_destCol;				// 目的の色
	CParticle *m_pParticle;
	std::vector<SData> m_data;
	std::string m_path;
	SData m_effect;
	EBehaviorType m_behavior;
	int m_nTime;						// 時間
	int m_nDelay;						// 遅延
	int m_nDestroyTime;					// エフェクトを消す時間
	float m_fAngle;						// 角度 未使用
	float m_fRadius;					// 半径 未使用
	float m_fAttenuation;				// 減衰
	float m_fSpeed;						// スピード
	float m_fFadeValue;					// エフェクトがフェードする数値
	float m_fFallSpeed;					// 落下速度
	float m_fRotateSpeed;				// 回転速度
	float m_fScalingValue;				// 拡縮する数値
	float m_fTouchAttenuation = 1.0f;	// 地面に触れた時の減衰量
	bool m_bGravity;					// 下に落ちていくかどうか
	bool m_bFade;						// エフェクトのフェードを使用するかどうか
	bool m_bRotate;						// 回転をするかどうか
	bool m_bScaling;					// 拡縮を行うかどうか
	bool m_bLocus;						// パーティクルに軌跡をつけるかどうか
	bool m_bBounce;						// バウンドをさせるかどうか
	bool m_bTransition;					// 色の変化をつけるかどうか
	bool m_bPosSpecify;					// 位置の指定をするかどうか
	bool m_bPosOperate = false;			// 位置の操作用
};
#endif