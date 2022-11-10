//=============================================================================
//
// タイトルメニュー処理 [title_menu.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "pause_menu.h"
#include "pause_logo.h"
#include "application.h"
#include "input.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CPauseMenu::m_apObject2D[6] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CPauseMenu::CPauseMenu(int nPriority) :
	m_nTextureMax(6),
	m_bGame(false),
	m_bTutorial(false),
	m_bRanking(false),
	m_bSelect(false),
	m_bGameMenu(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseMenu::~CPauseMenu()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPauseMenu::Init()
{
	// タイトルメニュー [背景]
	m_apObject2D[0] = CObject2D::Create("TITLEMENU_BG", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF - 30.0f, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1300.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [GAME]
	m_apObject2D[1] = CObject2D::Create("TITLEMENU_GAME", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [TUTORIAL]
	m_apObject2D[2] = CObject2D::Create("TITLEMENU_TUTORIAL", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [RANKING]
	m_apObject2D[3] = CObject2D::Create("TITLEMENU_RANKING", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// タイトルメニュー [SOLO]
	m_apObject2D[4] = CObject2D::Create("TITLEMENU_SOLO", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_apObject2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// タイトルメニュー [VS]
	m_apObject2D[5] = CObject2D::Create("TITLEMENU_VS", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_apObject2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// オブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPauseMenu::Uninit()
{
	// オブジェクトの終了処理
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPauseMenu::Update()
{
	// 座標取得
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		m_pos[nCnt] = m_apObject2D[nCnt]->GetPos();
	}

	// メニュー欄出現処理
	PutoutMenu();

	// メニュー欄選択処理
	SelectMenu();

	// オブジェクトの更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPauseMenu::Draw()
{
	// オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// メニュー欄出現処理
//=============================================================================
void CPauseMenu::PutoutMenu(void)
{
	// タイトルメニュー[壁紙]出現
	//if (CPauseMenu::GetTitleMenuFlag())
	{
		if (m_pos[0].x < SCREEN_WIDTH_HALF)
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
		if (m_pos[3].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
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
		if (m_pos[2].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
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
		if (m_pos[1].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bSelect = true;
		}
	}
}

//=============================================================================
// メニュー欄選択処理
//=============================================================================
void CPauseMenu::SelectMenu(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPauseMenu * CPauseMenu::Create(void)
{
	//ポインタ宣言
	CPauseMenu *pMenu = nullptr;

	//インスタンス生成
	pMenu = new CPauseMenu;

	if (pMenu != nullptr)
	{//ポインタが存在したら実行
		pMenu->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pMenu;
}
