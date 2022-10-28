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
	m_nSpeed(5.0f)
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
	BindTexture("FLOOR2");

	//objectxのposとrot
	m_pos = CBillboard::GetPos();

	//オブジェクトの初期化
	CBillboard::Init();
	CBillboard::SetMove(D3DXVECTOR3(rand() % 5, 1.5f, rand() % 5));
	CBillboard::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticle::Update()
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();
	CBillboard::Update();

	// 前回の位置を保存
	m_posOld = m_pos;

	m_pos = CBillboard::GetPos();

	CBillboard::SetPos(m_pos);
	CBillboard::SetCol(D3DXCOLOR(0.0f,1.0f,1.0f,0.6f));
}

//=============================================================================
// 生成処理
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}