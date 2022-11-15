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
#include "obstacle.h"
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
CObstacle::CObstacle(int nPriority)
{
	m_PosOld = {};
	m_nTriggerCount1 = 0;
	m_nTriggerCount2 = 0;
	m_ArrowRand = 0;
	m_AreaFlag1P = false;
	m_AreaFlag2P = false;
	m_ArrowRandFlag = false;
	m_nAlternateFlag = false;
	PlayerGoalFlag = false;
	m_bIsLanding = false;
	m_bIsLandingUp = false;
	m_Completion = false;
	m_StopObstacle = false;

	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_GIMMICK);
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
	// ギミックの初期化
	CGimmick::Init();

	//乱数
	srand((unsigned int)time(NULL));	//起動時に一回だけ行うため初期化に書く

	m_PosOld = CObjectX::GetPos();

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
	//// プレイヤー情報の取得
	//CPlayer * pPlayer1P = CGame::GetPlayer1P();
	//CPlayer * pPlayer2P = CGame::GetPlayer2P();

	//// ギミック情報の取得
	//CObstacle * pObstacle1P = CGame::GetObstacle1P();
	//CObstacle * pObstacle2P = CGame::GetObstacle2P();

	//// ギミック1Pの座標,移動量取得
	//D3DXVECTOR3 pos1P = pObstacle1P->GetPos();
	//D3DXVECTOR3 move1P = pObstacle1P->GetMove();

	//// ギミック2Pの座標,移動量取得
	//D3DXVECTOR3 pos2P = pObstacle2P->GetPos();
	//D3DXVECTOR3 move2P = pObstacle2P->GetMove();

	//// プレイヤーの座標取得
	//D3DXVECTOR3 PlayerPos1 = CGame::GetPlayer1P()->GetPos();
	//D3DXVECTOR3 PlayerPos2 = CGame::GetPlayer2P()->GetPos();

	//// 連打で動く壁の処理関数呼び出し
	//bool bFlag1P = pObstacle1P->BarrageMoveWall(pObstacle1P, pos1P, PlayerPos1);
	//bool bFlag2P = pObstacle2P->BarrageMoveWall(pObstacle2P, pos2P, PlayerPos2);

	//// 押したら動く壁の処理関数呼び出し
	///*bFlag1P = pObstacle1P->PushMoveObject(pObstacle1P, pos1P, PlayerPos1);
	//bFlag2P = pObstacle2P->PushMoveObject(pObstacle2P, pos2P, PlayerPos2);*/

	//if (bFlag1P)
	//{
	//	move1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	if (pObstacle1P->GetStopFlag())
	//	{
	//		move1P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	//	}
	//}
	//else
	//{
	//	pPlayer1P->SetSpeed(0.0f);
	//}

	//if (bFlag2P)
	//{
	//	move2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	if (pObstacle2P->GetStopFlag())
	//	{
	//		move2P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	//	}
	//}
	//else
	//{
	//	pPlayer2P->SetSpeed(0.0f);
	//}

	//if (pObstacle1P->GetCompletion() == true)
	//{// 操作が完了した時に実行
	//	// プレイヤーのスピードを元に戻す
	//	CGame::GetPlayer1P()->SetSpeed(5.0f);
	//}
	//if (pObstacle2P->GetCompletion() == true)
	//{// 操作が完了した時に実行
	// // プレイヤーのスピードを元に戻す
	//	CGame::GetPlayer2P()->SetSpeed(5.0f);
	//}

	//// 位置更新
	//pos1P += move1P;
	//pos2P += move2P;

	//// 移動量減衰
	//pos1P.x += (0.0f - move1P.x) * 0.1f;
	//pos1P.y += (0.0f - move1P.y) * 0.1f;
	//pos1P.z += (0.0f - move1P.z) * 0.1f;

	//pos2P.x += (0.0f - move2P.x) * 0.1f;
	//pos2P.y += (0.0f - move2P.y) * 0.1f;
	//pos2P.z += (0.0f - move2P.z) * 0.1f;

	//// 座標の設定
	//pObstacle1P->SetPos(pos1P);
	//pObstacle2P->SetPos(pos2P);

	//// 移動量の設定
	//pObstacle1P->SetMove(move1P);
	//pObstacle2P->SetMove(move2P);

	//// ギミックの更新
	//CGimmick::Update();
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
void CObstacle::ConstOperate()
{
}

//=============================================================================
// キーをカウントする関数
//=============================================================================
void CObstacle::KeyCount()
{
	m_nTriggerCount1++;
}

//=============================================================================
// 操作処理
//=============================================================================
CObstacle * CObstacle::Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype,int nPriority)
{
	CObstacle *pObstacle = new CObstacle(nPriority);
	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(gimmicktype);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}

////=============================================================================
//// 連打で動く壁の処理
////=============================================================================
//D3DXVECTOR3 CObstacle::BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove, D3DXVECTOR3 ObstacleMove2P)
//{
//	// キーボードの情報取得
//	CInput *pInputKeyboard = CApplication::GetInput();
//
//	if (CGimmick::GetCompletion() == false)
//	{// 操作を完了していない時実行
//		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
//			&&ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 150.0f >= P1Pos.z
//			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 150.0f <= P1Pos.z)
//		{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら
//			//プレイヤー1を動かさないようにする
//			CGame::GetPlayer1P()->SetSpeed(0.0f);
//		}
//		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
//		{// ギミックのタイプが連打で動く壁だった時実行
//			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
//				&&pInputKeyboard->Trigger(DIK_SPACE))
//			{// プレイヤータイプが1Pだったら && SPACEキーを押したら
//				//キーを押すごとにカウントが増えていく
//				m_nTriggerCount1++;
//				if (m_nTriggerCount1 >= 20)
//				{// カウントが20回以上行ったら実行
//					 // ギミック(壁)が上に移動
// 					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f,0.0f);
//					// 操作が完了した
//					CGimmick::SetCompletion(true);
//				}
//			}
//		}
//	}
//
//	if (CGimmick::GetCompletion() == false)
//	{// 操作を完了していない時実行
//		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
//			&&ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 150.0f >= P2Pos.z
//			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 150.0f <= P2Pos.z)
//		{// プレイヤータイプが2Pだったら && ギミックの範囲内にいたら
//		 //プレイヤー2を動かさないようにする
//			CGame::GetPlayer2P()->SetSpeed(0.0f);
//		}
//		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
//		{// ギミックのタイプが連打で動く壁だった時実行
//			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
//				&&pInputKeyboard->Trigger(DIK_LSHIFT))
//			{// プレイヤータイプが2Pだったら && SPACEキーを押したら
//				//キーを押すごとにカウントが増えていく
//				m_nTriggerCount2++;
//				if (m_nTriggerCount2 >= 20)
//				{// カウントが20回以上行ったら実行
//				 // ギミック(壁)が上に移動
//					ObstacleMove2P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
//					// 操作が完了した
//					CGimmick::SetCompletion(true);
//				}
//			}
//		}
//	}
//
//	return ObstacleMove2P;
//}


//=============================================================================
// 連打で動く壁の処理
//=============================================================================
bool CObstacle::BarrageMoveWall(CObstacle * pCObstacle, D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 PlayerPos)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	// 変数宣言
	bool bFlag = true;

	if (pCObstacle->GetCompletion())
	{
		// 操作が完了している
		return bFlag;
	}

	/* ↓操作が完了していない↓ */

	if (((ObstaclePos.x + 150.0f) >= PlayerPos.x) && ((ObstaclePos.z + 150.0f) >= PlayerPos.z)
		&& ((ObstaclePos.x - 150.0f) <= PlayerPos.x) && ((ObstaclePos.z - 150.0f) <= PlayerPos.z))
	{// プレイヤーを動かさないようにするフラグを有効にする
		bFlag = false;
	}

	if (pCObstacle->GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
	{// ギミックのタイプが連打で動く壁だった時実行
		if (!bFlag)
		{
			if (pInputKeyboard->Trigger(DIK_SPACE))
			{// SPACEキーを押したらカウントを増やす
				m_nTriggerCount1++;
				if (m_nTriggerCount1 >= 20)
				{// カウントが20回以上行ったら実行
				 // ギミック(壁)が上に移動
					bFlag = true;
					// 操作が完了した
					pCObstacle->SetCompletion(true);
					pCObstacle->SetStopFlag(true);
				}
			}
		}
	}

	// 値を返す
	return bFlag;
}

////=============================================================================
//// 交互連打で動く壁の処理
////=============================================================================
//D3DXVECTOR3 CObstacle::AlternateMoveWal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
//{
//	// キーボードの情報取得
//	CInput *pInputKeyboard = CApplication::GetInput();
//
//	if (CGimmick::GetCompletion() == false || CGimmick::GetCompletion() == false)
//	{// 操作を完了していない時実行
//		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
//			&&ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 150.0f >= P1Pos.z
//			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 150.0f <= P1Pos.z)
//		{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら
//		 //プレイヤー1を動かさないようにする
//			CGame::GetPlayer1P()->SetSpeed(0.0f);
//		}
//		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
//			&&ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 150.0f >= P2Pos.z
//			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 150.0f <= P2Pos.z)
//		{// プレイヤータイプが2Pだったら && ギミックの範囲内にいたら
//		 //プレイヤー2を動かさないようにする
//			CGame::GetPlayer2P()->SetSpeed(0.0f);
//		}
//		if (CGimmick::GetGimmickType() == GIMMICKTYPE_ALTERNATEMOVEWALL)
//		{// ギミックのタイプが交互に連打で動く壁だった時実行
//			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P)
//			{
//				if (pInputKeyboard->Trigger(DIK_Z) && m_nAlternateFlag == false)
//				{// Zキーを押したら実行
//					m_nTriggerCount1++;
//					m_nAlternateFlag = true;
//				}
//				if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag == true)
//				{// Cキーを押したら実行
//					m_nTriggerCount1++;
//					m_nAlternateFlag = false;
//				}
//				if (m_nTriggerCount1 >= 10)
//				{
//					// ギミック(壁)が上に移動
//					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
//
//					// 操作が完了した
//					CGimmick::SetCompletion(true);
//				}
//			}
//			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P)
//			{
//				if (pInputKeyboard->Trigger(DIK_N) && m_nAlternateFlag == false)
//				{// Zキーを押したら実行
//					m_nTriggerCount2++;
//					m_nAlternateFlag = true;
//				}
//				if (pInputKeyboard->Trigger(DIK_M) && m_nAlternateFlag == true)
//				{// Cキーを押したら実行
//					m_nTriggerCount2++;
//					m_nAlternateFlag = false;
//				}
//				if (m_nTriggerCount2 >= 10)
//				{
//					// ギミック(壁)が上に移動
//					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
//
//					// 操作が完了した
//					CGimmick::SetCompletion(true);
//				}
//			}
//		}
//	}
//	return ObstacleMove;
//}

////=============================================================================
//// プレイヤーが押して動く壁の処理
////=============================================================================
//bool CObstacle::PushMoveObject(CObstacle * pCObstacle, D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 PlayerPos)
//{
//	// 変数宣言
//	bool bFlag = true;
//
//	if (pCObstacle->GetCompletion())
//	{
//		// 操作が完了している
//		return bFlag;
//	}
//
//	if (pCObstacle->GetGimmickType() == GIMMICKTYPE_PUSHMOVEWALL)
//	{
//		if (((ObstaclePos.x + 50.0f) >= PlayerPos.x) && ((ObstaclePos.z + 75.0f) >= PlayerPos.z)
//			&& ((ObstaclePos.x - 50.0f) <= PlayerPos.x) && ((ObstaclePos.z - 75.0f) <= PlayerPos.z))
//		{// ギミックの範囲内にいたら
//			bFlag = false;
//		}
//	}
//	return bFlag;
//}

//=============================================================================
// プレイヤーがゴールした時の処理
//=============================================================================
bool CObstacle::PlayerGoal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	if (CGimmick::GetGimmickType() == GIMMICKTYPE_GOAL)
	{
		if (ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 50.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 50.0f <= P1Pos.z
			&&CGimmick::GetCompletion() == false && PlayerGoalFlag == false
			|| ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 50.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 50.0f <= P2Pos.z
			&&CGimmick::GetCompletion() == false && PlayerGoalFlag == false)
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
