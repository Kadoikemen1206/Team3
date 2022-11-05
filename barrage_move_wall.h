//=============================================================================
//
// 連打すると動く壁ギミック
// Author : saito shian
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _BARRAGE_MOVE_WALL_H_
#define _BARRAGE_MOVE_WALL_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "gimmick.h"
#include "player.h"

//=============================================================================
// 前方定義
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CBarrageMoveWall : public CGimmick
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CBarrageMoveWall(int nPriority = PRIORITY_LEVEL3);
	~CBarrageMoveWall() override;

	static CBarrageMoveWall *Create(const D3DXVECTOR3& pos);		// 生成処理

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理

	void ConstOperate() override;	// 一定の操作(連打、回転)
	void KeyCount();				// キーをカウントする関数

	bool GetCompletion(void) { return m_Completion; }
	void SetCompletion(bool bflag) { m_Completion = bflag; }

	bool GetStopFlag(void) { return m_StopObstacle; }
	void SetStopFlag(bool bflag) { m_StopObstacle = bflag; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_PosOld;			// 前回の位置
	int m_nTriggerCount1;			// キーを押した回数
	int m_nTriggerCount2;			// キーを押した回数
	int m_ArrowRand;				// 矢印の種類ランダム

	bool m_ArrowRandFlag;			// 矢印の種類ランダムフラグ
	bool m_AreaFlag1P;				// 1Pがエリア内にいるかフラグ
	bool m_AreaFlag2P;				// 2Pがエリア内にいるかフラグ
	bool m_nAlternateFlag;			// 交互にキーを押しているか
	bool PlayerGoalFlag;			// プレイヤーがゴールしたか
	bool m_bIsLanding;				// モデルとの当たり判定フラグ(左右,奥,手前)
	bool m_bIsLandingUp;			// モデルとの当たり判定フラグ(上側)

	bool m_Completion;				// Playerが完了したか否かフラグ
	bool m_StopObstacle;			// Obstacleストップするかのフラグ
};
#endif
