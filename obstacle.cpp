//=============================================================================
//
// 障害物処理 [obstacle.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "obstacle.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CObstacle::CObstacle(int nPriority)
{
	m_nTriggerCount1 = 0;
	m_nTriggerCount2 = 0;
	m_nAlternateFlag = false;
	PlayerGoalFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObstacle::Init()
{
	CGimmick::Init();

	//モデルのロード
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObstacle::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObstacle::Update()
{
	//ギミックの更新
	CGimmick::Update();
	D3DXVECTOR3 ObstacleMove = GetMove();
	D3DXVECTOR3 ObstaclePos = CGimmick::GetPos();
	D3DXVECTOR3 PlayerPos1 = CGame::GetPlayer1P()->GetPos();		//プレイヤー1POS情報の取得
	D3DXVECTOR3 PlayerPos2 = CGame::GetPlayer2P()->GetPos();		//プレイヤー2POS情報の取得

	// 連打で動く壁の処理関数呼び出し
	ObstacleMove = BarrageMoveWall(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);

	//************************************************
	// 交互連打で動く壁
	//************************************************
	//if (CGimmick::GetGimmickType() == GIMMICKTYPE_ALTERNATEMOVEWALL)
	//{// ギミックのタイプが交互に連打で動く壁だった時実行
	//	if (pInputKeyboard->Trigger(DIK_Z) && m_nAlternateFlag == false)
	//	{// Zキーを押したら実行
	//		m_nTriggerCount++;
	//		m_nAlternateFlag = true;
	//	}
	//	if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag == true)
	//	{// Cキーを押したら実行
	//		m_nTriggerCount++;
	//		m_nAlternateFlag = false;
	//	}
	//	if (m_nTriggerCount >= 10)
	//	{
	//		// ギミック(壁)が上に移動
	//		ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	//
	//		// 操作が完了した
	//		CGimmick::SetCompletion(true);
	//	}
	//}
	//if (CGimmick::GetGimmickType() == GIMMICKTYPE_SHAPE)
	//{// ギミックのタイプが図形当てギミックだった時実行
	//	if (CGimmick::GetShapeType() == SHAPETYPE_AQUARE)
	//	{
	//		if (pInputKeyboard->Trigger(DIK_A))
	//		{// Aキーを押したら実行
	//			CGimmick::Uninit();
	//			return;
	//		}
	//	}
	//}

	// プレイヤーがゴールした時の関数呼び出し
	//PlayerGoal(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);

	if (CGimmick::GetCompletion1P() == true)
	{// 操作が完了した時に実行
		// プレイヤーのスピードを元に戻す
		CGame::GetPlayer1P()->SetSpeed(5.0f);
	}
	if (CGimmick::GetCompletion2P() == true)
	{// 操作が完了した時に実行
	 // プレイヤーのスピードを元に戻す
		CGame::GetPlayer2P()->SetSpeed(5.0f);
	}

	//位置更新
	ObstaclePos.x += ObstacleMove.x;
	ObstaclePos.y += ObstacleMove.y;
	ObstaclePos.z += ObstacleMove.z;

	//移動量減衰
	ObstaclePos.x += (0.0f - ObstacleMove.x) * 0.1f;
	ObstaclePos.y += (0.0f - ObstacleMove.y) * 0.1f;
	ObstaclePos.z += (0.0f - ObstacleMove.z) * 0.1f;

	SetMove(ObstacleMove);
	SetPos(ObstaclePos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CObstacle::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
void CObstacle::ConstOperate(int barrage, int rotate)
{
}

//=============================================================================
// 操作処理
//=============================================================================
CObstacle * CObstacle::Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype, SHAPETYPE shapetype, int nPriority)
{
	CObstacle *pObstacle = new CObstacle(nPriority);

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(gimmicktype);
		pObstacle->SetShapeType(shapetype);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}

//************************************************
// 連打で動く壁の処理
//************************************************
D3DXVECTOR3 CObstacle::BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (CGimmick::GetCompletion1P() == false || CGimmick::GetCompletion2P() == false)
	{// 操作を完了していない時実行
		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
			&&ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 150.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 150.0f <= P1Pos.z)
		{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら
			//プレイヤー1を動かさないようにする
			CGame::GetPlayer1P()->SetSpeed(0.0f);
		}
		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
			&&ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 150.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 150.0f <= P2Pos.z)
		{// プレイヤータイプが2Pだったら && ギミックの範囲内にいたら
			//プレイヤー2を動かさないようにする
			CGame::GetPlayer2P()->SetSpeed(0.0f);
		}
		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
		{// ギミックのタイプが連打で動く壁だった時実行
			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
				&&pInputKeyboard->Trigger(DIK_SPACE))
			{// プレイヤータイプが1Pだったら && SPACEキーを押したら
				//キーを押すごとにカウントが増えていく
				m_nTriggerCount1++;
				if (m_nTriggerCount1 >= 20)
				{// カウントが20回以上行ったら実行
					 // ギミック(壁)が上に移動
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
					// 操作が完了した
					CGimmick::SetCompletion1P(true);
				}
			}
			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
				&&pInputKeyboard->Trigger(DIK_LSHIFT))
			{// プレイヤータイプが2Pだったら && SPACEキーを押したら
				//キーを押すごとにカウントが増えていく
				m_nTriggerCount2++;
				if (m_nTriggerCount2 >= 20)
				{// カウントが20回以上行ったら実行
				 // ギミック(壁)が上に移動
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
					// 操作が完了した
					CGimmick::SetCompletion2P(true);
				}
			}
		}
	}
	return ObstacleMove;
}

//************************************************
// プレイヤーがゴールした時の処理
//************************************************
bool CObstacle::PlayerGoal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	if (CGimmick::GetGimmickType() == GIMMICKTYPE_GOAL)
	{
		if (ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 50.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 50.0f <= P1Pos.z
			&&CGimmick::GetCompletion1P() == false && PlayerGoalFlag == false
			|| ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 50.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 50.0f <= P2Pos.z
			&&CGimmick::GetCompletion2P() == false && PlayerGoalFlag == false)
		{// ギミックの範囲 && 操作を完了していない時実行
		 //ゲームクリア
			PlayerGoalFlag = true;
			if (PlayerGoalFlag == true)
			{
				// 遷移
				CFade::SetFade(CApplication::MODE_TITLE);
			}
		}
	}

	return false;
}
