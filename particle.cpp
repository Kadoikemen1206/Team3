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
	m_nDestroyTime(200),
	m_fSpeed(5.0f),
	m_bGravity(true),
	m_bFade(false),
	m_bRotate(true),
	m_bScaling(true),
	m_bTransition(true)
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
	BindTexture("PARTICLE_STAR");

	m_beginPos = CBillboard::GetPos();

	//テスト用
	m_fFadeValue = -0.01f;
	m_fFallSpeed = 0.05f;
	m_fRotateSpeed = 0.1f;
	m_fScalingValue = 0.3f;
	m_destCol = D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);

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

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}