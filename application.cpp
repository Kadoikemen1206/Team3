//=============================================================================
//
// マネージャ処理 [application.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
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

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInputKeyboard = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CMeshfield *CApplication::m_pMeshField = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;
CObjectX *CApplication::m_apObject3D[4] = {};

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

	//インプットクラスの生成
	m_pInputKeyboard = new CInput;

	//レンダリングの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ //初期化処理が失敗した場合
		return -1;
	}

	//インプットの初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{ //初期化処理が失敗した場合
		return -1;
	}

	//カメラの生成
	m_pCamera = CCamera::Create();

	//ライトの生成
	m_pLight = CLight::Create();

	//ポリゴンの生成
	//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//モデルの生成
	m_apObject3D[0] = CObjectX::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	m_apObject3D[1] = CObjectX::Create(D3DXVECTOR3(-100.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	m_apObject3D[2] = CObjectX::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CApplication::Uninit(void)
{
	//オブジェクトの全開放
	CObject::UninitAll();

	//レンダリングの解放・削除
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//インプットの解放・削除
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
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
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//レンダリングの更新処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//カメラの更新処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_C))
	{
		m_apObject3D[3] = CObjectX::Create(D3DXVECTOR3(-200.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	}

	if (pInputKeyboard->GetTrigger(DIK_V) && m_apObject3D[0] != nullptr)
	{
		m_apObject3D[0]->Uninit();
		m_apObject3D[0] = nullptr;
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
		m_pCamera->SetCamera();
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
CInput * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}