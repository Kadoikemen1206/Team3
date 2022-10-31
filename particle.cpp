#include <assert.h>
#include "application.h"
#include "input.h"
#include "main.h"
#include "particle.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle::CParticle(int nPriority) :
	m_nTime(0),
	m_nDelay(60),
	m_nDestroyTime(300),
	m_fAngle(0.0f),
	m_fRadius(0.0f),
	m_fAttenuation(0.05f),
	m_fSpeed(5.0f),
	m_bGravity(true),			// 重力
	m_bFade(true),				// アルファ値増減
	m_bRotate(true),			// ビルボードの回転
	m_bScaling(true),			// 拡縮
	m_bLocus(true),				// パーティクルに軌跡をつける（激重です）
	m_bTransition(true),		// 色の変化
	m_bPosSpecify(false)		// 位置の指定
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
	//テクスチャの読み込み
	BindTexture("PARTICLE_FLARE");

	m_beginPos = CBillboard::GetPos();

	//テスト用
	m_fRadius = 75.0f;
	m_fFadeValue = -0.005f;
	m_fFallSpeed = 0.05f;
	m_fRotateSpeed = 0.1f;
	m_fScalingValue = 0.05f;
	m_destPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destCol = D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);
	m_fAttenuation = 0.08f;

	//位置の指定テスト
	m_effect.destPos = m_beginPos + D3DXVECTOR3(0.0f,50.0f, 0.0f);
	m_effect.frame = 100;
	m_data.push_back(m_effect);

	m_effect.destPos = m_beginPos + D3DXVECTOR3(0.0f, 150.0f, 0.0f);
	m_effect.frame = 250;
	m_data.push_back(m_effect);

	//オブジェクトの初期化
	CBillboard::Init();
	CBillboard::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticle::Update()
{
	CBillboard::Update();

	// 前回の位置を保存
	m_posOld = m_pos;

	m_pos = CBillboard::GetPos();
	m_col = CBillboard::GetCol();

	if (m_bPosSpecify)
	{// 位置の指定をする場合
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data.at(i).frame != m_nTime)
			{
				continue;
			}

			m_destPos = m_data.at(i).destPos;
			m_bPosOperate = true;
		}

		if (m_bPosOperate)
		{
			m_pos += (m_destPos - m_pos) * m_fAttenuation;
		}
	}

	DetailSetting();

	CBillboard::SetPos(m_pos);
	m_nTime++;

	// ======================
	// 正規化
	// ======================
	if (m_fRadius > D3DX_PI)
	{
		m_fRadius -= D3DX_PI * 2;
	}
	else if (m_fRadius < -D3DX_PI)
	{
		m_fRadius += D3DX_PI * 2;
	}

	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2;
	}
	else if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2;
	}

	if (m_nTime >= m_nDestroyTime || m_col.a <= 0.0f)
	{
		CBillboard::Uninit();
		return;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetMove(move);
		pParticle->SetCol(col);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//詳細設定
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
		m_col.r += (m_destCol.r - m_col.r) / m_nDestroyTime;
		m_col.g += (m_destCol.g - m_col.g) / m_nDestroyTime;
		m_col.b += (m_destCol.b - m_col.b) / m_nDestroyTime;
	}

	if (m_bLocus && (m_nTime % 2) == 0)
	{// パーティクルに軌跡をつける場合
		m_pParticle = CParticle::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_col, PRIORITY_LEVEL3);
		m_pParticle->SetFade(true, -0.1f);
		m_pParticle->SetGravity(false);
		m_pParticle->SetLocus(false);
		m_pParticle->SetPosSpecify(false);
	}

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}