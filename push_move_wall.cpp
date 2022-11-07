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
#include "push_move_wall.h"
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
CPushMoveWall::CPushMoveWall(int nPriority)
{
	m_PosOld = {};
	m_nTriggerCount = 0;
	m_Completion = false;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPushMoveWall::~CPushMoveWall()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPushMoveWall::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//モデルのロード
	LoadModel("BUGGY");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPushMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPushMoveWall::Update()
{
	if (GetCompletion() == false)
	{
		// ギミックの座標,移動量取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		/* ↓Gimmickクリアしていない↓ */

		// 当たり判定のチェック
		Collision(CGame::GetPlayer1P());
		Collision(CGame::GetPlayer2P());

		if (GetHitPlayer() == nullptr)
		{
			return;
		}

		// ギミック処理
		ConstOperate();

		if (GetHitPlayer())
		{
			CPlayer* hitPlayer = GetHitPlayer();

			hitPlayer->SetSpeed(2.5f);
			move = D3DXVECTOR3(0.0f, 0.0f, 2.5f);
			if(pos.z)
		}

		// ギミックの更新
		CGimmick::Update();

		// 位置更新
		pos += move;

		// 移動量減衰
		pos.x += (0.0f - move.x) * 0.1f;
		pos.y += (0.0f - move.y) * 0.1f;
		pos.z += (0.0f - move.z) * 0.1f;

		SetPos(pos);	// 座標の設定
		SetMove(move);	// 移動量の設定
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPushMoveWall::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 操作処理
//=============================================================================
void CPushMoveWall::ConstOperate()
{
	if (GetHitPlayer())
	{
		return;
	}

	/* ↓プレイヤーと接触した↓ */

	if (GetCompletion())
	{
		return;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CPushMoveWall* CPushMoveWall::Create(const D3DXVECTOR3& pos)
{
	CPushMoveWall *pObstacle = new CPushMoveWall();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_PUSHMOVEWALL);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
