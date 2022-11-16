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
#include "sound.h"
#include "billboard.h"
#include "icon.h"

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
	LoadModel("BOOK04");
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	D3DXVECTOR3 pos = GetPos();
	pos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	SetPos(pos);

	//モデルのロード
	m_Door = CObjectX::Create(GetPos() - D3DXVECTOR3(200.0f, 0.0f, 0.0f),PRIORITY_LEVEL3);
	m_Door->Init();
	m_Door->LoadModel("BOOK04");
	//m_Door->SetPos(GetPos() - D3DXVECTOR3(50.0f, 0.0f, 100.0f));
	pos = GetPos();
	pos -= D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_Door->SetPos(pos);
	m_Door->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));

	m_pIcon[0] = nullptr;
	m_pIcon[1] = nullptr;

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
		D3DXVECTOR3 rot = GetRot();
		D3DXVECTOR3 move = GetMove();

		if (rot.y <= D3DX_PI * 0.5f)
		{
			move = D3DXVECTOR3(0.0f, -0.01f, 0.0f);
			rot = m_Door->GetRot();
			rot += move;
			m_Door->SetRot(rot);
			
			move = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
			// 位置更新
			rot = GetRot();
			rot += move;
			SetRot(rot);
		}
	}
	else
	{
		/* ↓Gimmickクリアしていない↓ */

		// 当たり判定のチェック
		Collision(CGame::GetPlayer1P());
		if (CGame::GetPlayer2P() != nullptr)
		{
			Collision(CGame::GetPlayer2P());
		}

		if (GetHitPlayer() == nullptr)
		{
			return;
		}

		// ギミック処理
		ConstOperate();

		CPlayer* hitPlayer = GetHitPlayer();

		hitPlayer->SetSpeed(0.0f);
		hitPlayer->SetMotionType(CPlayer::MOTION_PUSH);

		if (GetCompletion())
		{// 操作が完了した時に実行
		 // プレイヤーのスピードを元に戻す
			hitPlayer->SetMotionType(CPlayer::MOTION_NONE);
			hitPlayer->SetSpeed(5.0f);
		}

		auto pos = hitPlayer->GetPos();

		if (m_pIcon[0] != nullptr)
		{
			m_pIcon[0]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		}
		if (m_pIcon[1] != nullptr)
		{
			m_pIcon[1]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		}

		// ギミックの更新
		CGimmick::Update();
		m_Door->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBarrageMoveWall::Draw()
{
	CGimmick::Draw();
	m_Door->Draw();
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

	if (m_pIcon[0] == nullptr)
	{
		m_pIcon[0] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), "SPEECH_BUBBLE", PRIORITY_LEVEL3);
		m_pIcon[0]->SetScaling(true, true);
		m_pIcon[0]->SetAnimation(1, 1, 12, 1, true);
	}

	if (GetHitPlayer()->GetKeyIndex() == -1)
	{
		if (m_pIcon[1] == nullptr)
		{
			m_pIcon[1] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), "BUTTON_ENTER", PRIORITY_LEVEL3);
			m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
		}
	}
	else
	{
		if (m_pIcon[1] == nullptr)
		{
			m_pIcon[1] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), "BUTTON_B", PRIORITY_LEVEL3);
			m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
		}
	}

	/* ↓操作が完了していない↓ */

	if (pInputKeyboard->Trigger(KEY_DECISION))
	{// SPACEキーを押したらカウントを増やす
		m_nTriggerCount++;
		if (m_nTriggerCount >= 20)
		{// カウントが20回以上行ったら実行
		 // ギミック(壁)が上に移動
			m_pIcon[0]->Uninit();
			m_pIcon[1]->Uninit();
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
		pObstacle->SetPos(pos);
		pObstacle->Init();
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
