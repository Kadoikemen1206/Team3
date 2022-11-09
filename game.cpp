//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
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
#include "button_move_player.h"
#include "stop_gimmick.h"
#include "goal.h"
#include "random_door.h"

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
	//乱数
	srand((unsigned int)time(NULL));	//起動時に一回だけ行うため初期化に書く

	// ライトの生成
	m_pLight = CLight::Create();

	// タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 3,CObject::PRIORITY_LEVEL4);

	// メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ギミックの生成(連打ギミック)
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 1500.0f));
	// ギミックの生成(交互連打ギミック)
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 3000.0f));
	// ギミックの生成(押すギミック)
	//CPushMoveWall::Create(D3DXVECTOR3(-700.0f,0.0f,2000.0f));
	// ギミックの生成(ボタンをしたら少しずつ進むギミック)
	//CButtonMovePlayer::Create(D3DXVECTOR3(-700.0f, -200.0f, 2000.0f));
	// ギミックの生成(当たったら止まるギミック)
	//CStopGimmick::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// ゴールの生成
	CGoal::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));

	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	CRandomDoor::Create(D3DXVECTOR3(-800.0f + 75.0f * nCnt, 0.0f, 2000.0f));
	//}

	//プレイヤーの生成
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	CLoadStage::LoadAll(m_pPlayer1P->GetPos());
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_ONE);
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 20.0f, 2000.0f));
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 45.0f, 2800.0f));
	//CButtonMovePlayer::Create(D3DXVECTOR3(-700.0f, -200.0f, 3600.0f));
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 4000.0f));
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 4300.0f));

	if (m_mode == EMode::VS)
	{
		//CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));
		// ギミックの生成(押すギミック)
		CButtonMovePlayer::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));
		CAlternateMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2800.0f));
		CButtonMovePlayer::Create(D3DXVECTOR3(700.0f, 0.0f, 3600.0f));
		CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 4000.0f));
		CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 4300.0f));

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

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (m_pPause == nullptr)
		{
			if (pInputKeyboard->Trigger(DIK_P))
			{
				m_pPause = CPause::Create();
			}
		}
		else
		{
			if (m_pPause->GetEndFlag())
			{
				static int count = 0;
				count++;

				if (count <= 20)
				{
					count = 0;
					m_pPause = nullptr;
				}
			}
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