//=============================================================================
//
// ゴール処理
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
#include "particle.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CGoal::m_GoalFlag = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal(int nPriority)
{
	// メンバ変数のクリア
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
	// ギミックの終了処理
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

	// プレイヤーが接触したかのポインタ
	CPlayer* hitPlayer = GetHitPlayer();

	// プレイヤーのスピードをなくす
	hitPlayer->SetSpeed(0.0f);
	m_GoalCount--;
	if ((m_GoalCount % 20) == 0)
	{
		int max = 50;
		int minPosZ = -(rand() % 350);
		int maxPosZ = rand() % 350;

		for (int i = 0; i < max; i++)
		{
			m_pParticle = CParticle::Create(D3DXVECTOR3(pos.x, pos.y + 180.0f, (rand() % maxPosZ) - minPosZ),
				D3DXVECTOR3(sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))) * cosf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), cosf((rand() % max * ((360 / max) * (D3DX_PI / 180))))),
				D3DXCOLOR((rand() % 100) * 0.01f, (rand() % 100) * 0.01f, (rand() % 100) * 0.01f, 1.0f),
				"PARTICLE_FLARE",
				PRIORITY_LEVEL3);
		}
	}
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
	// ギミックの描画処理
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
