//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : TANAKA KOTA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "application.h"
#include "input.h"
#include "main.h"
#include "particle.h"
#include "renderer.h"
#include "meshfield.h"
#include "objectX.h"
#include "model.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle::CParticle(int nPriority) :
	m_nTime(0),									// 時間
	m_nDelay(50),								// 遅延
	m_nDestroyTime(200),						// 消滅までの時間
	m_fRotateSpeed(0.1f),						// 回転速度
	m_bGravity(false),							// 重力
	m_bFade(false),								// アルファ値増減
	m_bRotate(true),							// ビルボードの回転
	m_bScaling(false),							// 拡縮
	m_bLocus(false),							// パーティクルに軌跡をつける（激重です）
	m_bBounce(false),							// バウンドさせる
	m_bTransition(false),						// 色の変化
	m_destCol(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)),	// 目的の色
	m_behavior(BEHAVIOR_FIREWORKS)				// 挙動
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticle::Init()
{
	if (m_behavior != BEHAVIOR_INVALID || m_behavior != BEHAVIOR_NONE)
	{
		Preset();
	}

	//テクスチャの読み込み
	BindTexture(m_path);

	m_beginPos = CBillboard::GetPos();

	//オブジェクトの初期化
	CBillboard::Init();
	CBillboard::SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticle::Update()
{
	CBillboard::Update();

	m_pos = CBillboard::GetPos();
	m_col = CBillboard::GetCol();

	m_pos += m_moveTransition;

	//詳細設定
	DetailSetting();

	CBillboard::SetPos(m_pos);

	m_nTime++;

	if (m_nTime >= m_nDestroyTime || m_col.a <= 0.0f)
	{
		CBillboard::Uninit();
		return;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, EBehaviorType type, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetBehavior(type);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//=============================================================================
// 生成処理
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const std::string url, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetMove(move);
		pParticle->SetCol(col);
		pParticle->SetPath(url);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//=============================================================================
//詳細設定
//=============================================================================
void CParticle::DetailSetting()
{
	D3DXVECTOR3 move = CBillboard::GetMove();
	D3DXVECTOR3 scale = CBillboard::GetSize();

	if (m_bGravity)
	{// 重力を使用する場合
		if (m_nTime >= m_nDelay)
		{
			move.y -= m_fFallSpeed;
		}
	}

	if (m_bBounce)
	{// バウンドを使用する場合
		if (m_pos.y <= m_lowerPos.y)
		{
			move.y += 1.0f * m_fTouchAttenuation;
			m_fTouchAttenuation -= 0.02f;
		}
	}

	if (m_bFade)
	{// エフェクトのフェードを使用する場合
		m_col.a += m_fFadeValue;
	}

	if (m_bRotate)
	{// ビルボードの回転をする場合
		D3DXVECTOR3 rot = CBillboard::GetRot();
		D3DXVECTOR3 vec = m_pos - m_beginPos;

		if (vec.x <= 0)
		{// 現在の位置が開始地点から左にある場合
			rot.z += m_fRotateSpeed;
		}
		else
		{// 右にある場合
			rot.z -= m_fRotateSpeed;
		}

		CBillboard::SetRotate(true);
		CBillboard::SetRot(rot);
	}

	if (m_bScaling)
	{// 拡大・縮小を行う場合
		scale.x += m_fScalingValue;
		scale.y += m_fScalingValue;
	}

	if (m_bTransition)
	{// 色の変化をつける場合
		m_col.r += (m_destCol.r - m_col.r) / (m_nDestroyTime * 0.8f);
		m_col.g += (m_destCol.g - m_col.g) / (m_nDestroyTime * 0.8f);
		m_col.b += (m_destCol.b - m_col.b) / (m_nDestroyTime * 0.8f);
	}

	if (m_bLocus && (m_nTime % 3) == 0 && m_col.a >= 0.2f)
	{// パーティクルに軌跡をつける場合
		m_pParticle = CParticle::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_col, "PARTICLE_FLARE", PRIORITY_LEVEL3);
		m_pParticle->SetSize(D3DXVECTOR3(20.0f,20.0f,0.0f));
		m_pParticle->SetScaling(true, -0.2f);
		m_pParticle->SetFade(true, -0.09f);
		m_pParticle->SetGravity(false);
		m_pParticle->SetLocus(false);
	}

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}

//=============================================================================
//挙動の設定
//=============================================================================
void CParticle::Preset()
{
	switch (m_behavior)
	{
	case BEHAVIOR_FLY:			//飛んで落ちる挙動
		m_path = "PARTICLE_FLARE";
		SetCol(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bLocus = false;
		m_bBounce = true;
		m_bTransition = true;
		m_fFadeValue = -0.005f;
		m_fFallSpeed = 0.1f;
		m_fScalingValue = 0.05f;
		break;

	case BEHAVIOR_FIREWORKS:	//たくさん出すと花火みたいな挙動
		m_path = "PARTICLE_FLARE";
		SetDestCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bTransition = true;
		m_bLocus = true;
		m_nDelay = 100;
		m_fFallSpeed = 0.001f;
		m_fFadeValue = -0.006f;
		m_fScalingValue = 0.1f;
		break;

	case BEHAVIOR_SMOKE:		//歩く時の煙
		m_path = "PARTICLE_SMOKE";
		SetMove(D3DXVECTOR3((rand() % 100) * 0.01f, (rand() % 100) * 0.005f, (rand() % 100) * 0.01f));
		SetCol(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bFade = true;
		m_bScaling = true;
		m_bRotate = true;
		m_fFadeValue = -0.03f;
		m_fScalingValue = 0.1f;
		break;

	default:
		break;
	}
}