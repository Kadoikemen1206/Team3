//=============================================================================
//
// ギミックの基盤処理 [gimmick.h]
// Author : saito shian
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"

//=============================================================================
// 前方定義
//=============================================================================
class CPlayer;
class CIcon;

//=============================================================================
// クラスの定義
//=============================================================================
class CGimmick : public CObjectX
{
public:
	//-------------------------------------------------------------------------
	// ギミックのタイプ
	//-------------------------------------------------------------------------
	enum GIMMICKTYPE
	{
		GIMMICKTYPE_NONE = 0,
		GIMMICKTYPE_BARRAGEMOVEWALL,		// 連打で動く壁
		GIMMICKTYPE_ALTERNATEMOVEWALL,		// 交互に連打で動く壁
		GIMMICKTYPE_PUSHMOVEWALL,			// 押すギミック
		GIMMICKTYPE_GOAL,					// ゴール
		GIMMICKTYPE_MAX
	};
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CGimmick(int nPriority = PRIORITY_LEVEL3);
	~CGimmick() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理

	void SetGimmickType(GIMMICKTYPE type);								// ギミックの種類の設定
	void SetCompletion(bool flag) { m_Completion = flag; }				// 完了したかを設定
	void SetHitPlayer(CPlayer* inPlayer) { m_pHitPlayer = inPlayer; }	// プレイヤーがギミックに当たったかの設定処理

	bool Collision(CPlayer* inPlayer);									// プレイヤーが接触
	bool CollisionGimmick(CPlayer* inPlayer);							// プレイヤーがギミックに接触
	bool GetCompletion() { return m_Completion; }						// 完了したかを知らせる

	GIMMICKTYPE GetGimmickType(void) { return m_GimmickType; }			// ギミックの種類の取得
	CPlayer* GetHitPlayer() { return m_pHitPlayer; }					// プレイヤーがギミックに当たったかの取得処理

	virtual void ConstOperate() = 0;									// 一定の操作(連打、回転)

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_Pos;				// ギミックの位置
	GIMMICKTYPE m_GimmickType;		// ギミックの種類
	CPlayer* m_pHitPlayer;			// 当たったプレイヤー

	bool m_Completion;				// 完了したか否かフラグ 
};
#endif
