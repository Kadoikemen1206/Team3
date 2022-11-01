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
		GIMMICKTYPE_SHAPE,					// 図形当てギミック
		GIMMICKTYPE_GOAL,					// ゴール
		GIMMICKTYPE_MAX
	};
	//-------------------------------------------------------------------------
	// 図形のタイプ
	//-------------------------------------------------------------------------
	enum SHAPETYPE
	{
		SHAPETYPE_NONE = 0,
		SHAPETYPE_CIRCLE,				// 円形
		SHAPETYPE_AQUARE,				// 四角形
		SHAPETYPE_TRIANGLE,				// 三角形
		SHAPETYPE_MAX
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

	GIMMICKTYPE GetGimmickType(void) { return m_GimmickType; }	// ギミックの種類の取得
	void SetGimmickType(GIMMICKTYPE type);						// ギミックの種類の設定

	SHAPETYPE GetShapeType(void) { return m_ShapeType; }	// 図形の種類の取得
	void SetShapeType(SHAPETYPE type);						// 図形の種類の設定

	D3DXVECTOR3 GetArea() { return m_Area; }					// ギミックのエリア取得処理

	virtual void ConstOperate(int barrage,int rotate) = 0;		// 一定の操作(連打、回転)

	static bool GetCompletion1P();			// 完了したかを知らせる
	static bool GetCompletion2P();			// 完了したかを知らせる
	static void SetCompletion1P(bool flag);	// 1Pが完了したかを設定
	static void SetCompletion2P(bool flag);	// 2Pが完了したかを設定

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_Pos;				// ギミックの位置
	GIMMICKTYPE m_GimmickType;		// ギミックの種類
	SHAPETYPE m_ShapeType;			// 図形の種類
	static bool m_Completion1P;		// 1Pが完了したか否かフラグ
	static bool m_Completion2P;		// 2Pが完了したか否かフラグ
	static D3DXVECTOR3 m_Area;		// ギミックの範囲
};
#endif
