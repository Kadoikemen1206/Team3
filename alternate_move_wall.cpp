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
#include "particle.h"
#include "icon.h"

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

		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

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

		hitPlayer->SetIsMove(false);
		if (GetCompletion())
		{// 操作が完了した時に実行
		 // プレイヤーのスピードを元に戻す
			hitPlayer->SetIsMove(true);
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

	if (m_pIcon[0] == nullptr)
	{
		m_pIcon[0] = CIcon::Create(m_Screw->GetPos() + D3DXVECTOR3(0.0f, 130.0f, 0.0f), D3DXVECTOR3(40.0f, 30.0f, 0.0f), "SPEECH_BUBBLE", PRIORITY_LEVEL3);
		m_pIcon[0]->SetScaling(true);
		m_pIcon[0]->SetAnimation(1, 1, 12, 1, true);
	}

	if (m_pIcon[1] == nullptr)
	{
		m_pIcon[1] = CIcon::Create(m_Screw->GetPos() + D3DXVECTOR3(0.0f, 130.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), "BUTTON_Y", PRIORITY_LEVEL3);
		m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
	}

	if (pInputKeyboard->Trigger(KEY_LEFT_ACTION) && !m_nAlternateFlag)
	{// Zキーを押したら実行

		D3DXVECTOR3 pos = GetPos();
		pos.y += 2.5f;
		SetPos(pos);

		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = true;

		for (int i = 0; i < 2; i++)
		{
			// 移動量
			D3DXVECTOR3 move;
			move.x = sinf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));
			move.y = sinf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180))) * cosf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));
			move.z = cosf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));

			// 色
			D3DXCOLOR color((rand() % 100) * 0.01f, (rand() % 100) * 0.01f, (rand() % 100) * 0.01f, 1.0f);

			CParticle* particle = CParticle::Create(GetPos(),move, color,"PARTICLE_FLARE",PRIORITY_LEVEL3);
			particle->SetLower(GetPos());
		}
	}

	if (pInputKeyboard->Trigger(KEY_RIGHT_ACTION) && m_nAlternateFlag)
	{// Cキーを押したら実行

		D3DXVECTOR3 pos = GetPos();
		pos.y += 2.5f;
		SetPos(pos);

		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = false;

		for (int i = 0; i < 2; i++)
		{
			D3DXVECTOR3 move;
			move.x = sinf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));
			move.y = sinf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180))) * cosf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));
			move.z = cosf(rand() % 50 * ((360 / 50) * (D3DX_PI / 180)));

			D3DXCOLOR color((rand() % 100) * 0.01f, (rand() % 100) * 0.01f, (rand() % 100) * 0.01f, 1.0f);

			CParticle* particle = CParticle::Create(GetPos(), move, color, "PARTICLE_FLARE", PRIORITY_LEVEL3);
			particle->SetLower(GetPos());
		}
	}

	// 指定回数のボタンを押した場合
	if (m_nTriggerCount >= 40)
	{
		// 操作が完了した
		GetHitPlayer()->SetMotionType(CPlayer::MOTION_NONE);
		m_pIcon[0]->Uninit();
		m_pIcon[1]->Uninit();
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
