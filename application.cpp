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
#include "time.h"
#include "number.h"
#include "texture.h"
#include "model.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInputKeyboard = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CMeshfield *CApplication::m_pMeshField = nullptr;
CTime *CApplication::m_pTime = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
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
	m_pInputKeyboard = new CInput;
	//インプットの初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{ //初期化処理が失敗した場合
		return -1;
	}

	// テクスチャの生成
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();
	//カメラの初期化
	m_pCamera->SetCameraType(CCamera::CAMERATYPE_ONE);
	m_pCamera->SetCameraType(CCamera::CAMERATYPE_TWO);
	m_pCamera->Init();
	//ライトの生成
	m_pLight = CLight::Create();

	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL5);

	//ポリゴンの生成
	//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-500.0f, 0.0f, 14500.0f), CObject::PRIORITY_LEVEL2);

	//モデルの生成
	CObjectX::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);
	CObjectX::Create(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		//モデルの生成(壁)
		CModel::Create(D3DXVECTOR3(-150.0f, 0.0f , 200.0f + (380.0f * nCnt)), CObject::PRIORITY_LEVEL1);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CApplication::Uninit(void)
{
	//オブジェクトの全開放
	CObject::UninitAll();

	//ナンバーの削除
	CNumber::Unload();

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
CInput * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}