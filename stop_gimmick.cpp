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
#include "stop_gimmick.h"
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
CStopGimmick::CStopGimmick(int nPriority)
{
	m_StopCount = 100;
	m_StopFlag = false;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// デストラクタ
//=============================================================================
CStopGimmick::~CStopGimmick()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStopGimmick::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	//モデルのロード
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStopGimmick::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStopGimmick::Update()
{
	// ギミックの座標,移動量取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 当たり判定のチェック
	CollisionGimmick(CGame::GetPlayer1P());
	if (CGame::GetPlayer2P() != nullptr)
	{
		CollisionGimmick(CGame::GetPlayer2P());
	}

	if (CGame::GetPlayer2P() == nullptr)
	{
		CGame::GetPlayer2P()->Death();
		return;
	}

	// ギミック処理
	ConstOperate();

	CPlayer* hitPlayer = GetHitPlayer();

	if (CollisionGimmick(CGame::GetPlayer1P()) == true)
	{
		hitPlayer->SetSpeed(0.0f);
		m_StopCount--;
		if (m_StopCount <= 0)
		{
			hitPlayer->SetSpeed(5.0f);
			m_StopCount = 100;
		}
	}
	else
	{
		hitPlayer->SetSpeed(5.0f);
		m_StopCount = 100;
	}

	// 位置更新
	pos += move;

	// 移動量減衰
	pos.x += (0.0f - move.x) * 0.1f;
	pos.y += (0.0f - move.y) * 0.1f;
	pos.z += (0.0f - move.z) * 0.1f;

	SetPos(pos);	// 座標の設定
	SetMove(move);	// 移動量の設定

					// ギミックの更新
	CGimmick::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CStopGimmick::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CStopGimmick::ConstOperate()
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
CStopGimmick* CStopGimmick::Create(const D3DXVECTOR3& pos)
{
	CStopGimmick *pObstacle = new CStopGimmick();

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
