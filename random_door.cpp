//=============================================================================
//
// 障害物処理 [obstacle.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
#include "random_door.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "billboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CRandomDoor::CRandomDoor(int nPriority)
{
	m_DoorNumber = 1;
	m_RandNumber = 0;
	m_RandFlag = false;
	m_RandNumberFlag = false;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// デストラクタ
//=============================================================================
CRandomDoor::~CRandomDoor()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRandomDoor::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	//乱数
	srand((unsigned int)time(NULL));	//起動時に一回だけ行うため初期化に書く

	//モデルのロード
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRandomDoor::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRandomDoor::Update()
{
	// ギミックの座標,移動量取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 PlayerPos1P = CGame::GetPlayer1P()->GetPos();		//プレイヤーPOS情報の取得
	//yD3DXVECTOR3 PlayerPos2P = CGame::GetPlayer2P()->GetPos();		//プレイヤーPOS情報の取得

	// 当たり判定のチェック
	CollisionGimmick(CGame::GetPlayer1P());
	CollisionGimmick(CGame::GetPlayer2P());

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	// ギミック処理
	ConstOperate();

	CPlayer* hitPlayer = GetHitPlayer();

	if (CollisionGimmick(CGame::GetPlayer1P()) == true)
	{
		if (m_RandNumberFlag == false)
		{// まだ番号が決まっていないときに実行
			m_RandNumber = rand() % 9 + 1;
			// 番号が決まった
			m_RandNumberFlag = true;
		}
		if (m_RandNumber == 1 || m_RandNumber == 2 && m_RandNumberFlag == true)
		{
			if (m_RandNumber == m_DoorNumber)
			{
				m_RandFlag = true;
			}
		}
		else
		{
			m_RandFlag = false;
		}

		if (m_RandFlag == true)
		{
			PlayerPos1P = D3DXVECTOR3(-700.0f,0.0f,2100.0f);
		}
		else
		{
			PlayerPos1P = D3DXVECTOR3(-700.0f, 0.0f, 1800.0f);
		}
	}

	CGame::GetPlayer1P()->SetPos(PlayerPos1P);
	// ギミックの更新
	CGimmick::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRandomDoor::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CRandomDoor::ConstOperate()
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	/* ↓プレイヤーと接触してない↓ */

	if (GetCompletion())
	{
		return;
	}
}

//=============================================================================
// 操作処理
//=============================================================================
CRandomDoor* CRandomDoor::Create(const D3DXVECTOR3& pos)
{
	CRandomDoor *pObstacle = new CRandomDoor();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_BARRAGEMOVEWALL);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
