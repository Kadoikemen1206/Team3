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
#include "sound.h"
#include "meshfield.h"
#include "light.h"
#include "title_logo.h"
#include "title_menu.h"
#include "load_stage.h"

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
	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TITLE);
	CApplication::GetCamera()->Init();

	//BGMの設定
	CApplication::GetSound()->Play(CSound::LABEL_BGM_TITLE);

	// ライトの生成
	m_pLight = CLight::Create();

	// メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ステージのロード
	CLoadStage::LoadAll();

	// タイトルロゴの生成
	CTitleLogo::Create();

	// タイトルメニューの生成
	CTitleMenu::Create();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);

	//BGMを止める設定
	CApplication::GetSound()->Stop();

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
	// カメラの情報取得
	CCamera *pCamera = CApplication::GetCamera();

	// カメラの視点と注視点取得
	D3DXVECTOR3 posV = pCamera->GetPosV();
	D3DXVECTOR3 posR = pCamera->GetPosR();

	// 視点と注視点を後ろにずらしていく処理
	posV += D3DXVECTOR3(0.0f, 0.0f, 2.0f);
	posR += D3DXVECTOR3(0.0f, 0.0f, 2.0f);

	// 視点と注視点を設定
	pCamera->SetPosV(posV);
	pCamera->SetPosR(posR);

	if (posR.z >= 5200.0f)
	{
		CFade::SetFade(CApplication::GetMode());
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
	{// ポインタが虚無だったら実行5
		assert(false);
	}

	// ポインタを返す
	return pTitle;
}
