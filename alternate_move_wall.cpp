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
#include "alternate_move_wall.h"
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
CAlternateMoveWall::CAlternateMoveWall(int nPriority) :
	m_Screw(nullptr),
	m_buttonPushCount(0)
{
	m_PosOld = {};
	m_nTriggerCount = 0;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// デストラクタ
//=============================================================================
CAlternateMoveWall::~CAlternateMoveWall()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAlternateMoveWall::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//モデルのロード
	LoadModel("POCKET_WATCH");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CAlternateMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CAlternateMoveWall::Update()
{
	if (GetCompletion())
	{
		/* ↓Gimmickクリアしている↓ */

		// ギミックの座標,移動量取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		move = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

		// 位置更新
		pos += move;

		// 移動量減衰
		pos.x += (0.0f - move.x) * 0.1f;
		pos.y += (0.0f - move.y) * 0.1f;
		pos.z += (0.0f - move.z) * 0.1f;

		SetPos(pos);	// 座標の設定
		SetMove(move);	// 移動量の設定
	}
	else
	{
		/* ↓Gimmickクリアしていない↓ */

		// 当たり判定のチェック
		Collision(CGame::GetPlayer1P());
		Collision(CGame::GetPlayer2P());

		if (GetHitPlayer() == nullptr)
		{
			return;
		}

		CPlayer* hitPlayer = GetHitPlayer();

		if (hitPlayer->GetPos().x != 0.0f)
		{
			D3DXVECTOR3 pos = hitPlayer->GetPos();
			pos.x = GetPos().x;
			hitPlayer->SetPos(pos);
		}
		hitPlayer->SetMotionType(CPlayer::MOTION_SCREW);

		// ギミック処理
		ConstOperate();

		m_buttonPushCount++;

		if (m_buttonPushCount >= 10)
		{
			hitPlayer->SetUpdateStop(true);
		}
		else
		{
			D3DXVECTOR3 rot = m_Screw->GetRot();
			rot.y += 0.04f;
			m_Screw->SetRot(rot);
		}

		hitPlayer->SetSpeed(0.0f);
		if (GetCompletion())
		{// 操作が完了した時に実行
		 // プレイヤーのスピードを元に戻す
			hitPlayer->SetSpeed(5.0f);
		}

		// ギミックの更新
		CGimmick::Update();
		m_Screw->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CAlternateMoveWall::Draw()
{
	CGimmick::Draw();
	m_Screw->Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CAlternateMoveWall::ConstOperate()
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

	/* ↓操作が完了していない↓ */

	if (pInputKeyboard->Trigger(DIK_Z) && !m_nAlternateFlag)
	{// Zキーを押したら実行
		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = true;
	}

	if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag)
	{// Cキーを押したら実行
		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = false;
	}

	if (m_nTriggerCount >= 40)
	{
		// 操作が完了した
		GetHitPlayer()->SetMotionType(CPlayer::MOTION_NONE);
		CGimmick::SetCompletion(true);
	}
}

//=============================================================================
// キーをカウントする関数
//=============================================================================
void CAlternateMoveWall::KeyCount()
{
	m_nTriggerCount++;
}

//=============================================================================
// 操作処理
//=============================================================================
CAlternateMoveWall* CAlternateMoveWall::Create(const D3DXVECTOR3& pos)
{
	CAlternateMoveWall *pObstacle = new CAlternateMoveWall();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_BARRAGEMOVEWALL);
		pObstacle->Init();
		pObstacle->SetPos(pos);
		pObstacle->m_Screw = CObjectX::Create(pos - D3DXVECTOR3(0.0f, 0.0f, 130.0f), CObject::PRIORITY_LEVEL3);
		pObstacle->m_Screw->LoadModel("SCREW WINDING");
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
