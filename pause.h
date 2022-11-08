//=============================================================================
//
// ポーズ処理 [ pause.h ]
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CObject2D;
class CPauseSelect;

//=============================================================================
// クラスの定義
//=============================================================================
class CPause : public CObject
{
public:
	enum ESelect
	{
		QUIT,
		RETRY,
		EXIT
	};
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CPause();
	~CPause() override;

	// 生成処理
	static CPause *Create();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void BeginUpdate();				// 
	void SelectUpdate();			// 
	void EndUpdate();				// 
	void Draw(void) override;		// 描画処理

	bool GetEndFlag() { return m_isEndFlag; }

private:
	CObject2D* m_pBg;

	CPauseSelect* m_quit;
	CPauseSelect* m_retry;
	CPauseSelect* m_exit;

	ESelect m_select;
	int m_beginCount;		// 始まっているカウント
	int m_endCount;			// 終了までのカウント
	bool m_isEndFlag;		// 終了するフラグ
	bool m_isBeginFlag;		// 始まってる最中のフラグ
};

#endif