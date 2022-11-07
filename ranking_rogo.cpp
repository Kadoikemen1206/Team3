//=============================================================================
//
// ランキングロゴ処理 [ranking_rogo.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "precompile.h"
#include "ranking_rogo.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CRankingRogo::m_apObject2D[7] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRankingRogo::CRankingRogo(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRankingRogo::~CRankingRogo()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRankingRogo::Init()
{
	// ランキング[透過壁紙]
	m_apObject2D[0] = CObject2D::Create("RANKING_BG", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[1位]
	m_apObject2D[1] = CObject2D::Create("RANKING_1", D3DXVECTOR3(300.0f, 200.0f, 0.0f), D3DXVECTOR3(150.0f, 90.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[2位]
	m_apObject2D[2] = CObject2D::Create("RANKING_2", D3DXVECTOR3(300.0f, 310.0f, 0.0f), D3DXVECTOR3(150.0f, 90.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[3位]
	m_apObject2D[3] = CObject2D::Create("RANKING_3", D3DXVECTOR3(300.0f, 420.0f, 0.0f), D3DXVECTOR3(150.0f, 90.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[4位]
	m_apObject2D[4] = CObject2D::Create("RANKING_4", D3DXVECTOR3(300.0f, 530.0f, 0.0f), D3DXVECTOR3(150.0f, 90.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[5位]
	m_apObject2D[5] = CObject2D::Create("RANKING_5", D3DXVECTOR3(300.0f, 640.0f, 0.0f), D3DXVECTOR3(150.0f, 90.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ランキング[ロゴ]
	m_apObject2D[6] = CObject2D::Create("RANKING_0", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF + 10.0f, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// オブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRankingRogo::Uninit()
{
	// オブジェクトの終了処理
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRankingRogo::Update()
{
	// オブジェクトの更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRankingRogo::Draw()
{
	// オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CRankingRogo * CRankingRogo::Create(void)
{
	//ポインタ宣言
	CRankingRogo *pRankingRogo = nullptr;

	//インスタンス生成
	pRankingRogo = new CRankingRogo;

	if (pRankingRogo != nullptr)
	{//ポインタが存在したら実行
		pRankingRogo->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pRankingRogo;
}
