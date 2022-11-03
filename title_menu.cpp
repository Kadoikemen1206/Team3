//=============================================================================
//
// タイトルメニュー処理 [title_menu.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "title_menu.h"
#include "title_rogo.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CTitleMenu::m_apObject2D[4] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleMenu::CTitleMenu(int nPriority) :
	m_nTextureMax(4)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleMenu::~CTitleMenu()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleMenu::Init()
{
	// タイトルメニュー [背景]
	m_apObject2D[0] = CObject2D::Create("TITLEMENU_BG", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [GAME]
	m_apObject2D[1] = CObject2D::Create("TITLEMENU_GAME", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [TUTORIAL]
	m_apObject2D[2] = CObject2D::Create("TITLEMENU_TUTORIAL", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [RANKING]
	m_apObject2D[3] = CObject2D::Create("TITLEMENU_RANKING", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// オブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitleMenu::Uninit()
{
	// オブジェクトの終了処理
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitleMenu::Update()
{
	// 座標取得
	D3DXVECTOR3 pos[4];
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		pos[nCnt] = m_apObject2D[nCnt]->GetPos();
	}

	// タイトルメニュー[壁紙]出現
	if (CTitleRogo::GetTitleMenuFlag())
	{
		if (pos[0].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[0]->SetMove(D3DXVECTOR3(30.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[0]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bRanking = true;
		}
	}

	// タイトルメニュー[RANKING]出現
	if (m_bRanking)
	{
		if (pos[3].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(25.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bTutorial = true;
		}
	}

	// タイトルメニュー[TUTORIAL]出現
	if (m_bTutorial)
	{
		if (pos[2].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(35.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bGame = true;
		}
	}

	// タイトルメニュー[GAME]出現
	if (m_bGame)
	{
		if (pos[1].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(25.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	// オブジェクトの更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitleMenu::Draw()
{
	// オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CTitleMenu * CTitleMenu::Create(void)
{
	//ポインタ宣言
	CTitleMenu *pTitleMenu = nullptr;

	//インスタンス生成
	pTitleMenu = new CTitleMenu;

	if (pTitleMenu != nullptr)
	{//ポインタが存在したら実行
		pTitleMenu->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pTitleMenu;
}
