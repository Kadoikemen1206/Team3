//=============================================================================
// particle.h
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	explicit CParticle(int nPriority = PRIORITY_LEVEL3);
	~CParticle() override;

	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理
	void DetailSetting();

	//セッター
	void SetDelay(int time) { m_nDelay = time; }
	void SetGravity(bool set) { m_bGravity = set; }
	void SetGravity(bool set, float value) { m_bGravity = set, m_fFallSpeed = value; }
	void SetFade(bool set) { m_bFade = set; }
	void SetRotation(bool set, float value) { m_bRotate = set, m_fRotateSpeed = value; }
	void SetScaling(bool set) { m_bScaling = set; }
	void SetTransitionColor(bool set, D3DXCOLOR col) { m_bTransition = set, m_destCol = col; }

	//ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, int nPriority);    // 生成処理

private:
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_beginPos;		// 開始時の位置
	D3DXVECTOR3 m_posOld;		// 前回の位置
	D3DXCOLOR m_col;			// 色
	D3DXCOLOR m_destCol;		// 目的の色
	int m_nTime;				// 時間
	int m_nDelay;				// 遅延
	int m_nDestroyTime;			// エフェクトを消す時間
	float m_fSpeed;				// スピード
	float m_fFadeValue;			// エフェクトがフェードする数値
	float m_fFallSpeed;			// 落下速度
	float m_fRotateSpeed;		// 回転速度
	float m_fScalingValue;		// 拡縮する数値
	bool m_bGravity;			// 下に落ちていくかどうか
	bool m_bFade;				// エフェクトのフェードを使用するかどうか
	bool m_bRotate;				// 回転をするかどうか
	bool m_bScaling;			// 拡縮を行うかどうか
	bool m_bTransition;			// 色の変化をつけるかどうか
};
#endif