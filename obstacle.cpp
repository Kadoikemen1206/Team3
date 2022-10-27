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

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CObstacle::CObstacle(int nPriority)
{
	m_nTriggerCount = 0;
	m_nAlternateFlag = false;
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
	LoadModel("Data\\MODEL\\aquare.x");

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
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();		//プレイヤーPOS情報の取得
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	if (ObstaclePos.x + 150.0f >= PlayerPos.x && ObstaclePos.z + 150.0f >= PlayerPos.z
		&&ObstaclePos.x - 150.0f <= PlayerPos.x && ObstaclePos.z - 150.0f <= PlayerPos.z
		&&CGimmick::GetCompletion() == false)
	{// ギミックの範囲&&操作を完了していない時実行

		// プレイヤーを動かさないようにする
		CGame::GetPlayer()->SetSpeed(0.0f);

		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
		{// ギミックのタイプが連打で動く壁だった時実行
			if (pInputKeyboard->Trigger(DIK_SPACE))
			{// SPACEキーを押したら実行

				//キーを押すごとにカウントが増えていく
				m_nTriggerCount++;
				if (m_nTriggerCount >= 20)
				{// カウントが20回以上行ったら実行

					 // ギミック(壁)が上に移動
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

					// 操作が完了した
					CGimmick::SetCompletion(true);
				}
			}
		}
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
	}
	if (CGimmick::GetCompletion() == true)
	{// 操作が完了した時に実行

		// プレイヤーのスピードを元に戻す
		CGame::GetPlayer()->SetSpeed(5.0f);
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
