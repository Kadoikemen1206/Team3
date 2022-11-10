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
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTriggerCount = 0;
	m_Completion = false;
	m_bIsLanding = false;
	m_bIsLandingUp = false;

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
	LoadModel("SMALL BOTTLE");

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
	// ギミックの更新
	CGimmick::Update();

	// ギミックの座標,移動量取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 重力設定
	move.y -= 2.5f;

	// 前回の位置を保存
	m_PosOld = pos;

	// ポインタ宣言
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	// 位置更新
	pos += move;

	// ギミック(モデル)とモデルの当たり判定
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		/* ↓Gimmickクリアしていない↓ */
		CObject::EObjType objType;

		// 当たり判定のチェック
		objType = pObject->GetObjType();

		if (objType == OBJTYPE_MODEL)
		{
			CObjectX *pObjectX = (CObjectX*)pObject;
			m_bIsLanding = pObjectX->Collision(&pos, &m_PosOld, &GetSize());
			m_bIsLandingUp = pObjectX->UpCollision(&pos, &m_PosOld, &GetSize(), &move);
		}

		// ギミック処理
		pObject = pObject->GetNext();
	}

	// 当たり判定のチェック
	bool bCollision1P = CollisionGimmick(CGame::GetPlayer1P());
	bool bCollision2P = CollisionGimmick(CGame::GetPlayer2P());

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	// ギミック処理
	ConstOperate();

	// プレイヤーが接触したかのポインタ
	CPlayer* hitPlayer = GetHitPlayer();

	// ギミックとプレイヤーが接触した時
	if (bCollision1P || bCollision2P)
	{
		// 位置更新
		hitPlayer->SetSpeed(1.5f);
		move = D3DXVECTOR3(0.0f, 0.0f, 1.5f);
	}
	// ギミックとプレイヤーが離れた時
	else
	{
		// プレイヤーのスピードを5.0f、ギミックのスピードを0.0fに戻す
		hitPlayer->SetSpeed(5.0f);
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ギミックが下に落ちた時
	if (pos.y <= -100.0f)
	{
		// 移動量減衰
		hitPlayer->SetSpeed(5.0f);
		// ギミック削除
		Uninit();
		return;
	}

	// 移動量減衰
	pos.x += (0.0f - move.x) * 0.1f;
	pos.y += (0.0f - move.y) * 0.1f;
	pos.z += (0.0f - move.z) * 0.1f;

	SetPos(pos);	// 座標の設定
	SetMove(move);	// 移動量の設定
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
