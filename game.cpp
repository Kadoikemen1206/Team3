//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "object.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "model.h"
#include "time.h"
#include "number.h"
#include "obstacle.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer *CGame::m_pPlayer1P = nullptr;
CPlayer *CGame::m_pPlayer2P = nullptr;
CCamera *CGame::m_pCamera = nullptr;
CMeshfield *CGame::m_pMeshField = nullptr;
CLight *CGame::m_pLight = nullptr;
CTime *CGame::m_pTime = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//ライトの生成
	m_pLight = CLight::Create();

	// タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL5);

	//メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//モデルの生成
	CObjectX::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);
	CObjectX::Create(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		//モデルの生成(壁)
		CModel::Create(D3DXVECTOR3(-150.0f, 0.0f, 200.0f + (380.0f * nCnt)), CObject::PRIORITY_LEVEL1);
	}

	//プレイヤーの生成
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-50.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_pPlayer2P = CPlayer::Create(CPlayer::EPLAYER_2P, D3DXVECTOR3(50.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// 障害物を作成
	CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_BARRAGEMOVEWALL, CGimmick::SHAPETYPE_AQUARE, CObject::PRIORITY_LEVEL3);

	// ギミックの生成
	CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_GOAL, CGimmick::SHAPETYPE_NONE, CObject::PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//ナンバーの削除
	CNumber::Unload();

	//ライトの解放・削除
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//インスタンスの解放処理
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInputKeyboard->Trigger(DIK_RETURN))
		{
			// 遷移
			CFade::SetFade(CApplication::MODE_TITLE);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create()
{
	//ポインタ宣言
	CGame *pGame = nullptr;

	//インスタンス生成
	pGame = new CGame;

	if (pGame != nullptr)
	{//ポインタが存在したら実行
		pGame->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pGame;
}