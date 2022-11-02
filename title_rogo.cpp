//=============================================================================
//
// タイトルロゴ処理 [title_rogo.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "title_rogo.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CTitleRogo::m_apObject2D[14] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleRogo::CTitleRogo(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleRogo::~CTitleRogo()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleRogo::Init()
{
	//THERE IS RUN DOLL
	m_apObject2D[0] = CObject2D::Create("TITLE_D", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[1] = CObject2D::Create("TITLE_E_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[2] = CObject2D::Create("TITLE_E_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[3] = CObject2D::Create("TITLE_I", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[4] = CObject2D::Create("TITLE_L_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[5] = CObject2D::Create("TITLE_L_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[6] = CObject2D::Create("TITLE_N", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[7] = CObject2D::Create("TITLE_H", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[8] = CObject2D::Create("TITLE_O", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[9] = CObject2D::Create("TITLE_R_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[10] = CObject2D::Create("TITLE_R_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[11] = CObject2D::Create("TITLE_S", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[12] = CObject2D::Create("TITLE_U", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[13] = CObject2D::Create("TITLE_T", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// オブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitleRogo::Uninit()
{
	// オブジェクトの終了処理
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitleRogo::Update()
{
	for (int i = 0; i < 14; i++)
	{
		m_apObject2D[i]->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}

	// オブジェクトの更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitleRogo::Draw()
{
	// オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CTitleRogo * CTitleRogo::Create(void)
{
	//ポインタ宣言
	CTitleRogo *pTitleRogo = nullptr;

	//インスタンス生成
	pTitleRogo = new CTitleRogo;

	if (pTitleRogo != nullptr)
	{//ポインタが存在したら実行
		pTitleRogo->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pTitleRogo;
}
