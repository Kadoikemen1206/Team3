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
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshfield.h"
#include "time.h"
#include "number.h"
#include "texture.h"
#include "model.h"
#include "obstacle.h"
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "fade.h"
#include "objectX_group.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInput = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CMeshfield *CApplication::m_pMeshField = nullptr;
CTime *CApplication::m_pTime = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CObjectXGroup *CApplication::m_pObjectXGroup = nullptr;
CApplication::MODE CApplication::m_mode = MODE_GAME;

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
	m_pCamera = new CCamera;
	m_pCamera->SetCameraType(CCamera::CAMERATYPE_ONE);
	m_pCamera->SetCameraType(CCamera::CAMERATYPE_TWO);
	m_pCamera->Init();

	// テクスチャの生成
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// モデルの生成
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	//モード生成
	CFade::Create(m_mode);

	CObstacle::Create(D3DXVECTOR3(0.0f,0.0f,500.0f), CGimmick::GIMMICKTYPE_SHAPE,CGimmick::SHAPETYPE_AQUARE, CObject::PRIORITY_LEVEL3);

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
	m_pTexture->UnloadAll();
	
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
	case MODE_GAME:
		m_pMode = CGame::Create();
		break;
	case MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
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