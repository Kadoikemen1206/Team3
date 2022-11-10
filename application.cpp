//=============================================================================
//
// マネージャ処理 [application.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "tutorial.h"
#include "fade.h"
#include "objectX_group.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInput = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CObjectXGroup *CApplication::m_pObjectXGroup = nullptr;
CSound *CApplication::m_pSound = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//=============================================================================
// コンストラクタ
//=============================================================================
CApplication::CApplication()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CApplication::~CApplication()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//乱数の初期化
	srand((unsigned int)time(0));

	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	//レンダリングの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ //初期化処理が失敗した場合
		return -1;
	}

	//インプットクラスの生成
	m_pInput = new CInput;
	//インプットの初期化処理
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{ //初期化処理が失敗した場合
		return -1;
	}

	// カメラの初期化
	m_pCamera = new CCamera;

	// テクスチャの生成
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// モデルの生成
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//モード生成
	CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CApplication::Uninit(void)
{
	//オブジェクトの全開放
	CObject::UninitAll();

	// テクスチャの削除
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// サウンドの削除
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// Xモデルの削除
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}

	//レンダリングの解放・削除
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//インプットの解放・削除
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//カメラの解放・削除
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CApplication::Update(void)
{
	//インプットの更新処理
	if (m_pInput != nullptr)
	{
		m_pInput->Update();
	}

	//カメラの更新処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//レンダリングの更新処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CApplication::Draw(void)
{
	//レンダリングの描画処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// レンダリングのポインタを返す処理
//=============================================================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// インプットのポインタを返す処理
//=============================================================================
CInput * CApplication::GetInput()
{
	return m_pInput;
}

//=============================================================================
// モードセット処理
//=============================================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	CObject::ModeRelease();

	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case MODE_GAME_SOLO:
		CGame::SetMode(CGame::EMode::SOLO);
		m_pMode = CGame::Create();
		break;
	case MODE_GAME_VS:
		CGame::SetMode(CGame::EMode::VS);
		m_pMode = CGame::Create();
		break;
	case MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
		break;
	case MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;
	}
}

//=============================================================================
// モードを取得する処理
//=============================================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}