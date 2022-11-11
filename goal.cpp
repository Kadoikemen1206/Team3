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
#include "goal.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "billboard.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CGoal::m_GoalFlag = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal(int nPriority)
{
	m_GoalCount = MAX_REVERBERATION_TIME;
	m_GoalFlag = false;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// デストラクタ
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGoal::Init()
{
	// ギミックの初期化
	CGimmick::Init();

	//モデルのロード
	LoadModel("CROWN");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGoal::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGoal::Update()
{
	// ギミックの座標,移動量取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 当たり判定のチェック
	m_GoalFlag = CollisionGimmick(CGame::GetPlayer1P());
	if (CGame::GetPlayer2P() != nullptr)
	{
		CollisionGimmick(CGame::GetPlayer2P());
	}

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	// ギミック処理
	ConstOperate();

	CPlayer* hitPlayer = GetHitPlayer();

	hitPlayer->SetSpeed(0.0f);
	m_GoalCount--;
	if (m_GoalCount <= 0)
	{
		// フェード生成
		CFade::SetFade(CApplication::MODE_RANKING);
		m_GoalCount = MAX_REVERBERATION_TIME;
	}

	// ギミックの更新
	CGimmick::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGoal::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CGoal::ConstOperate()
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
CGoal* CGoal::Create(const D3DXVECTOR3& pos)
{
	CGoal *pObstacle = new CGoal();

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
