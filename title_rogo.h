//=============================================================================
//
// タイトルロゴ処理 [title_rogo.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _TITLE_ROGO_H_ 
#define _TITLE_ROGO_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "mode.h"
#include "object2D.h"
#include "application.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CObject2D;

//=============================================================================
// クラスの定義
//=============================================================================
class CTitleRogo : public CObject2D
{
public:

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CTitleRogo(int nPriority = PRIORITY_LEVEL5);
	~CTitleRogo();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	static CTitleRogo *Create(void);	// 生成処理

private:

	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static	CObject2D *m_apObject2D[14];	// ポインタ
	bool	m_bTitleRogoSwitch;				// 縦の動きのフラグ
	int		m_nSinCount;					// Z軸の角度を加算する為のカウント変数
	float	m_fRotZ;						// Z軸の角度設定用の変数
};
#endif