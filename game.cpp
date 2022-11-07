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
#include "load_stage.h"
#include "barrage_move_wall.h"
#include "alternate_move_wall.h"
#include "push_move_wall.h"
#include "pause.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer *CGame::m_pPlayer1P = nullptr;
CPlayer *CGame::m_pPlayer2P = nullptr;
CCamera *CGame::m_pCamera = nullptr;
CMeshfield *CGame::m_pMeshField = nullptr;
CLight *CGame::m_pLight = nullptr;
CTime *CGame::m_pTime = nullptr;
CObstacle *CGame::m_pObstacle1P = nullptr;
CObstacle *CGame::m_pObstacle2P = nullptr;
CPause *CGame::m_pPause = nullptr;
CGame::EMode CGame::m_mode = CGame::EMode::SOLO;

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
	// ライトの生成
	m_pLight = CLight::Create();

	// タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL4);

	// メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ギミックの生成(連打ギミック)
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// ギミックの生成(交互連打ギミック)
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// ギミックの生成(押すギミック)
	//CPushMoveWall::Create(D3DXVECTOR3(-700.0f,0.0f,2000.0f));

	//プレイヤーの生成
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	CLoadStage::LoadAll(m_pPlayer1P->GetPos());
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_ONE);

	if (m_mode == EMode::VS)
	{
		//CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));
		// ギミックの生成(押すギミック)
		CPushMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
		CPushMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));

		m_pPlayer2P = CPlayer::Create(CPlayer::EPLAYER_2P, D3DXVECTOR3(700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
		CLoadStage::LoadAll(m_pPlayer2P->GetPos());
		CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TWO);
	}

	// カメラの設定
	CApplication::GetCamera()->Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// ナンバーの削除
	CNumber::Unload();

	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);

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
void CGame::Update(void)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (pInputKeyboard->Trigger(DIK_P))
	{
		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create();
		}
		else
		{
			m_pPause->Uninit();
			m_pPause = nullptr;
		}
	}


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