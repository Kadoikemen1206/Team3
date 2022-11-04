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
	// プレイヤー情報の取得
	CPlayer * pPlayer1P = CGame::GetPlayer1P();
	CPlayer * pPlayer2P = CGame::GetPlayer2P();

	// ギミック情報の取得
	CObstacle * pObstacle1P = CGame::GetObstacle1P();
	CObstacle * pObstacle2P = CGame::GetObstacle2P();

	// ギミック1Pの座標,移動量取得
	D3DXVECTOR3 pos1P = pObstacle1P->GetPos();
	D3DXVECTOR3 move1P = pObstacle1P->GetMove();

	// ギミック2Pの座標,移動量取得
	D3DXVECTOR3 pos2P = pObstacle2P->GetPos();
	D3DXVECTOR3 move2P = pObstacle2P->GetMove();

	// プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos1 = CGame::GetPlayer1P()->GetPos();
	D3DXVECTOR3 PlayerPos2 = CGame::GetPlayer2P()->GetPos();

	// 連打で動く壁の処理関数呼び出し
	bool bFlag1P = pObstacle1P->BarrageMoveWall2(pObstacle1P, pos1P, PlayerPos1);
	bool bFlag2P = pObstacle2P->BarrageMoveWall2(pObstacle2P, pos2P, PlayerPos2);

	if (bFlag1P)
	{
		move1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (pObstacle1P->GetStopFlag())
		{
			move1P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
		}
	}
	else
	{
		pPlayer1P->SetSpeed(0.0f);
	}

	if (bFlag2P)
	{
		move2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (pObstacle2P->GetStopFlag())
		{
			move2P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
		}
	}
	else
	{
		pPlayer2P->SetSpeed(0.0f);
	}

	if (pObstacle1P->GetCompletion() == true)
	{// 操作が完了した時に実行
		// プレイヤーのスピードを元に戻す
		CGame::GetPlayer1P()->SetSpeed(5.0f);
	}
	if (pObstacle2P->GetCompletion() == true)
	{// 操作が完了した時に実行
	 // プレイヤーのスピードを元に戻す
		CGame::GetPlayer2P()->SetSpeed(5.0f);
	}

	// 位置更新
	pos1P += move1P;
	pos2P += move2P;

	// 移動量減衰
	pos1P.x += (0.0f - move1P.x) * 0.1f;
	pos1P.y += (0.0f - move1P.y) * 0.1f;
	pos1P.z += (0.0f - move1P.z) * 0.1f;

	pos2P.x += (0.0f - move2P.x) * 0.1f;
	pos2P.y += (0.0f - move2P.y) * 0.1f;
	pos2P.z += (0.0f - move2P.z) * 0.1f;

	// 座標の設定
	pObstacle1P->SetPos(pos1P);
	pObstacle2P->SetPos(pos2P);

	// 移動量の設定
	pObstacle1P->SetMove(move1P);
	pObstacle2P->SetMove(move2P);

	// ギミックの更新
	CGimmick::Update();

	////ギミックの更新
	//CGimmick::Update();
	//D3DXVECTOR3 ObstacleMove1P = CGame::GetObstacle1P()->GetMove();
	//D3DXVECTOR3 ObstacleMove2P = CGame::GetObstacle2P()->GetMove();
	//D3DXVECTOR3 ObstaclePos = CGimmick::GetPos();
	//D3DXVECTOR3 PlayerPos1 = CGame::GetPlayer1P()->GetPos();		//プレイヤー1POS情報の取得
	//D3DXVECTOR3 PlayerPos2 = CGame::GetPlayer2P()->GetPos();		//プレイヤー2POS情報の取得

	//// 連打で動く壁の処理関数呼び出し
	//ObstacleMove1P = CGame::GetObstacle1P()->BarrageMoveWall(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove1P, ObstacleMove2P);
	////ObstacleMove2P = CGame::GetObstacle2P()->BarrageMoveWall(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove2P);
	//// 交互連打で動く壁の処理関数呼び出し
	////ObstacleMove = AlternateMoveWal(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);
	//// プレイヤーがゴールした時の関数呼び出し
	////PlayerGoal(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);
	////プレイヤーが押したら動く壁の処理
	////ObstacleMove = PushMoveObject(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);
	//// キーボードの情報取得

	//if (CGimmick::GetCompletion1P() == true)
	//{// 操作が完了した時に実行
	//	// プレイヤーのスピードを元に戻す
	//	CGame::GetPlayer1P()->SetSpeed(5.0f);
	//}
	//if (CGimmick::GetCompletion2P() == true)
	//{// 操作が完了した時に実行
	// // プレイヤーのスピードを元に戻す
	//	CGame::GetPlayer2P()->SetSpeed(5.0f);
	//}

	////位置更新
	//ObstaclePos.x += ObstacleMove1P.x;
	//ObstaclePos.y += ObstacleMove1P.y;
	//ObstaclePos.z += ObstacleMove1P.z;

	////移動量減衰
	//ObstaclePos.x += (0.0f - ObstacleMove1P.x) * 0.1f;
	//ObstaclePos.y += (0.0f - ObstacleMove1P.y) * 0.1f;
	//ObstaclePos.z += (0.0f - ObstacleMove1P.z) * 0.1f;

	//CGame::GetObstacle1P()->SetMove(ObstacleMove1P);

	////位置更新
	//ObstaclePos.x += ObstacleMove2P.x;
	//ObstaclePos.y += ObstacleMove2P.y;
	//ObstaclePos.z += ObstacleMove2P.z;

	////移動量減衰
	//ObstaclePos.x += (0.0f - ObstacleMove2P.x) * 0.1f;
	//ObstaclePos.y += (0.0f - ObstacleMove2P.y) * 0.1f;
	//ObstaclePos.z += (0.0f - ObstacleMove2P.z) * 0.1f;

	//CGame::GetObstacle2P()->SetMove(ObstacleMove2P);
	//SetPos(ObstaclePos);
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

//=============================================================================
// 連打で動く壁の処理
//=============================================================================
D3DXVECTOR3 CObstacle::BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove, D3DXVECTOR3 ObstacleMove2P)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (CGimmick::GetCompletion1P() == false)
	{// 操作を完了していない時実行
		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
			&&ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 150.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 150.0f <= P1Pos.z)
		{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら
			//プレイヤー1を動かさないようにする
			CGame::GetPlayer1P()->SetSpeed(0.0f);
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
 					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f,0.0f);
					// 操作が完了した
					CGimmick::SetCompletion1P(true);
				}
			}
		}
	}
	if (CGimmick::GetCompletion2P() == false)
	{// 操作を完了していない時実行
		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
			&&ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 150.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 150.0f <= P2Pos.z)
		{// プレイヤータイプが2Pだったら && ギミックの範囲内にいたら
		 //プレイヤー2を動かさないようにする
			CGame::GetPlayer2P()->SetSpeed(0.0f);
		}
		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
		{// ギミックのタイプが連打で動く壁だった時実行
			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
				&&pInputKeyboard->Trigger(DIK_LSHIFT))
			{// プレイヤータイプが2Pだったら && SPACEキーを押したら
				//キーを押すごとにカウントが増えていく
				m_nTriggerCount2++;
				if (m_nTriggerCount2 >= 20)
				{// カウントが20回以上行ったら実行
				 // ギミック(壁)が上に移動
					ObstacleMove2P = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
					// 操作が完了した
					CGimmick::SetCompletion2P(true);
				}
			}
		}
	}

	return ObstacleMove2P;
}

//=============================================================================
// 交互連打で動く壁の処理
//=============================================================================
D3DXVECTOR3 CObstacle::AlternateMoveWal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
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
		if (CGimmick::GetGimmickType() == GIMMICKTYPE_ALTERNATEMOVEWALL)
		{// ギミックのタイプが交互に連打で動く壁だった時実行
			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P)
			{
				if (pInputKeyboard->Trigger(DIK_Z) && m_nAlternateFlag == false)
				{// Zキーを押したら実行
					m_nTriggerCount1++;
					m_nAlternateFlag = true;
				}
				if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag == true)
				{// Cキーを押したら実行
					m_nTriggerCount1++;
					m_nAlternateFlag = false;
				}
				if (m_nTriggerCount1 >= 10)
				{
					// ギミック(壁)が上に移動
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

					// 操作が完了した
					CGimmick::SetCompletion1P(true);
				}
			}
			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P)
			{
				if (pInputKeyboard->Trigger(DIK_N) && m_nAlternateFlag == false)
				{// Zキーを押したら実行
					m_nTriggerCount2++;
					m_nAlternateFlag = true;
				}
				if (pInputKeyboard->Trigger(DIK_M) && m_nAlternateFlag == true)
				{// Cキーを押したら実行
					m_nTriggerCount2++;
					m_nAlternateFlag = false;
				}
				if (m_nTriggerCount2 >= 10)
				{
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

//=============================================================================
// プレイヤーが押して動く壁の処理
//=============================================================================
D3DXVECTOR3 CObstacle::PushMoveObject(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	// 前回の位置を保存
	m_PosOld = ObstaclePos;

	if (CGimmick::GetGimmickType() == GIMMICKTYPE_PUSH)
	{
		// 重力設定
		ObstacleMove.y -= 0.0f;

		//if (CGimmick::GetCompletion1P() == false || CGimmick::GetCompletion1P() == false)
		//{// 操作を完了していない時実行
		//	if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
		//		&&ObstaclePos.x + 50.0f >= P1Pos.x && ObstaclePos.z + 75.0f >= P1Pos.z
		//		&&ObstaclePos.x - 50.0f <= P1Pos.x && ObstaclePos.z - 75.0f <= P1Pos.z)
		//	{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら

		//		m_AreaFlag1P = true;
		//		if (m_AreaFlag1P == true)
		//		{
		//			//プレイヤー1の移動を1.5fにする
		//			CGame::GetPlayer1P()->SetSpeed(1.5f);
		//			ObstacleMove.z = 1.5f;
		//		}
		//	}
		//	else
		//	{
		//		m_AreaFlag1P = false;

		//		if (m_AreaFlag1P == false)
		//		{
		//			//プレイヤー1の移動を1.5fにする
		//			CGame::GetPlayer1P()->SetSpeed(5.0f);
		//			ObstacleMove.z = 0.0f;
		//		}
		//	}

		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
			&&ObstaclePos.x + 50.0f >= P2Pos.x && ObstaclePos.z + 75.0f >= P2Pos.z
			&&ObstaclePos.x - 50.0f <= P2Pos.x && ObstaclePos.z - 75.0f <= P2Pos.z)
		{// プレイヤータイプが1Pだったら && ギミックの範囲内にいたら

			m_AreaFlag2P = true;
			if (m_AreaFlag2P == true)
			{
				//プレイヤー2の移動を1.5fにする
				CGame::GetPlayer2P()->SetSpeed(1.5f);
				ObstacleMove.z = 1.5f;
			}
		}
		else
		{
			m_AreaFlag2P = false;

			if (m_AreaFlag2P == false)
			{
				//プレイヤー2の移動を1.5fにする
				CGame::GetPlayer2P()->SetSpeed(5.0f);
				ObstacleMove.z = 0.0f;
			}
		}
		//}
	//}

	//// ポインタ宣言
	//CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	//// ギミックとモデルの当たり判定
	//while (pObject != nullptr)
	//{
	//	if (pObject == this)
	//	{
	//		pObject = pObject->GetNext();
	//		continue;
	//	}

	//	//変数宣言
	//	CObject::EObjType objType;

	//	//オブジェクトのタイプを取得
	//	objType = pObject->GetObjType();

	//	if (objType == OBJTYPE_MODEL)
	//	{
	//		CObjectX *pObjectX = (CObjectX*)pObject;
	//		m_bIsLanding = pObjectX->Collision(&ObstaclePos, &m_PosOld, &CObjectX::GetSize());
	//		m_bIsLandingUp = pObjectX->UpCollision(&ObstaclePos, &m_PosOld, &CObjectX::GetSize(), &ObstacleMove);
	//	}

	//	//ポインタを次に進める
	//	pObject = pObject->GetNext();
	//}

		
	}
	return ObstacleMove;
}

//=============================================================================
// プレイヤーがゴールした時の処理
//=============================================================================
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

//=============================================================================
// 交互連打で動く壁の処理
//=============================================================================
bool CObstacle::BarrageMoveWall2(CObstacle * pCObstacle, D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 PlayerPos)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	// 変数宣言
	bool bFlag = true;

	if (pCObstacle->GetCompletion() == false)
	{// 操作を完了していない時実行
		if (((ObstaclePos.x + 150.0f) >= PlayerPos.x) && ((ObstaclePos.z + 150.0f) >= PlayerPos.z)
			&&((ObstaclePos.x - 150.0f) <= PlayerPos.x) && ((ObstaclePos.z - 150.0f) <= PlayerPos.z))
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
	}

	// 値を返す
	return bFlag;
}
