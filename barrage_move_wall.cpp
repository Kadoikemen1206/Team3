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
#include "barrage_move_wall.h"
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
CBarrageMoveWall::CBarrageMoveWall(int nPriority)
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
CBarrageMoveWall::~CBarrageMoveWall()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBarrageMoveWall::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//モデルのロード
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBarrageMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBarrageMoveWall::Update()
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

		// ギミック処理
		ConstOperate();

		CPlayer* hitPlayer = GetHitPlayer();

		hitPlayer->SetSpeed(0.0f);
		if (GetCompletion())
		{// 操作が完了した時に実行
		 // プレイヤーのスピードを元に戻す
			hitPlayer->SetSpeed(5.0f);
		}

		// プレイヤーの座標取得
		D3DXVECTOR3 PlayerPos1 = hitPlayer->GetPos();

		// ギミックの更新
		CGimmick::Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBarrageMoveWall::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CBarrageMoveWall::ConstOperate()
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

	if (pInputKeyboard->Trigger(DIK_SPACE))
	{// SPACEキーを押したらカウントを増やす
		m_nTriggerCount++;
		if (m_nTriggerCount >= 20)
		{// カウントが20回以上行ったら実行
		 // ギミック(壁)が上に移動
			// 操作が完了した
			SetCompletion(true);
		}
	}
}

//=============================================================================
// キーをカウントする関数
//=============================================================================
void CBarrageMoveWall::KeyCount()
{
	m_nTriggerCount++;
}

//=============================================================================
// 操作処理
//=============================================================================
CBarrageMoveWall* CBarrageMoveWall::Create(const D3DXVECTOR3& pos)
{
	CBarrageMoveWall *pObstacle = new CBarrageMoveWall();

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
