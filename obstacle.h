//=============================================================================
//
// 障害物処理 [obstacle.h]
// Author : saito shian
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "gimmick.h"

//=============================================================================
// 前方定義
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CObstacle : public CGimmick
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObstacle(int nPriority = PRIORITY_LEVEL3);
	~CObstacle() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理

	void ConstOperate(int barrage, int rotate) override;			// 一定の操作(連打、回転)
	D3DXVECTOR3 BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);	// 連打で動く壁の処理
	D3DXVECTOR3 AlternateMoveWal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);	// 交互連打で動く壁の処理
	bool PlayerGoal(D3DXVECTOR3 ObstaclePos , D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);				// プレイヤーがゴールした時の処理

	static CObstacle *Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype,SHAPETYPE shapetype, int nPriority);			// 生成処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	int m_nTriggerCount1;			// キーを押した回数
	int m_nTriggerCount2;			// キーを押した回数
	int m_ArrowRand;				// 矢印の種類ランダム

	bool m_ArrowRandFlag;			// 矢印の種類ランダムフラグ
	bool m_ArrowFlag;				// 矢印のフラグ
	bool m_nAlternateFlag;			// 交互にキーを押しているか
	bool PlayerGoalFlag;			// プレイヤーがゴールしたか
};
#endif
