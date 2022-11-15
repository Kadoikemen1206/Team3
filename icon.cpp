//=============================================================================
//
// ビルボードでアイコンの表示 [icon.cpp]
// Author : Tanaka Kouta
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "icon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CIcon::CIcon(int nPriority) : 
	m_bDestroy(false),
	m_bScaling(false),
	m_bLimit(false),
	m_bFade(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CIcon::~CIcon()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CIcon::Init(void)
{
	CBillboard::SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_beginScale = CBillboard::GetSize();

	//テクスチャの読み込み
	BindTexture(m_path);

	CBillboard::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CIcon::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CIcon::Update(void)
{
	CBillboard::Update();

	if (m_bScaling)
	{	//拡縮
		D3DXVECTOR3 scale = CBillboard::GetSize();

		scale.x += 0.5f;
		scale.y += 0.5f;

		if (m_bLimit)
		{
			if (scale.x >= m_beginScale.x + 15.0f && scale.y >= m_beginScale.y + 15.0f)
			{
				scale.x -= 10.5f;
				scale.y -= 10.5f;
			}
		}

		CBillboard::SetSize(scale);
	}

	if (m_bFade)
	{	//フェード
		auto col = CBillboard::GetCol();

		col.a -= 0.05f;

		CBillboard::SetCol(col);

		if (col.a <= 0.0f)
		{
			CBillboard::Uninit();
			return;
		}
	}

	if (m_bDestroy)
	{	//アイコンを消すかどうか
		CBillboard::Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CIcon::Draw(void)
{
	CBillboard::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CIcon *CIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, std::string url, int nPriority)
{
	//ポインタ宣言
	CIcon *pIcon = nullptr;

	pIcon = new CIcon(nPriority);

	if (pIcon != nullptr)
	{
		pIcon->SetPos(pos);
		pIcon->SetSize(size);
		pIcon->SetPath(url);
		pIcon->Init();
	}

	return pIcon;
}