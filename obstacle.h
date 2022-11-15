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
#include "player.h"

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

	void ConstOperate() override;		// 一定の操作(連打、回転)

	static CObstacle *Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype,int nPriority);			// 生成処理

	bool GetCompletion(void) { return m_Completion; }					// ギミックをクリアしたかを取得する処理
	void SetCompletion(bool bflag) { m_Completion = bflag; }			// ギミックをクリアしたかの設定処理

	bool GetStopFlag(void) { return m_StopObstacle; }					// 障害物を止めるかの取得処理
	void SetStopFlag(bool bflag) { m_StopObstacle = bflag; }			// 障害物を止めるかの設定処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	bool m_Completion;				// Playerが完了したか否かフラグ
	bool m_StopObstacle;			// Obstacleストップするかのフラグ
};
#endif
