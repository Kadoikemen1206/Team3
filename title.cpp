//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "title.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "meshfield.h"
#include "light.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// カメラのタイプ取得
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TITLE);
	CApplication::GetCamera()->Init();

	// ライトの生成
	m_pLight = CLight::Create();

	// メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-350.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);		// カメラ

	// ライトの解放・削除
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// インスタンスの解放処理
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	// キーボードの情報取得
	CInput *pInput = CApplication::GetInput();

	// カメラの情報取得
	CCamera *pCamera = CApplication::GetCamera();

	// カメラの視点と注視点取得
	D3DXVECTOR3 posV = pCamera->GetPosV();
	D3DXVECTOR3 posR = pCamera->GetPosR();

	// 視点と注視点を後ろにずらしていく処理
	posV -= D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	posR -= D3DXVECTOR3(0.0f, 0.0f, 3.0f);

	// 視点と注視点を設定
	pCamera->SetPosV(posV);
	pCamera->SetPosR(posR);

	// 画面遷移処理
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInput->Trigger(DIK_RETURN))
		{
			// フェード生成
			CFade::SetFade(CApplication::MODE_GAME);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTitle * CTitle::Create()
{
	// ポインタ宣言
	CTitle *pTitle = nullptr;

	// インスタンス生成
	pTitle = new CTitle;

	if (pTitle != nullptr)
	{// ポインタが存在したら実行
		pTitle->Init();
	}
	else
	{// ポインタが虚無だったら実行
		assert(false);
	}

	// ポインタを返す
	return pTitle;
}
