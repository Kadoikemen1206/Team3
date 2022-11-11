//=============================================================================
//
//カウントダウン処理 [countdown.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COUNTDOWN_TEXTURE	(4)				// 使用するテクスチャの枚数
#define COUNTDOWN_WIDTH		(700.0f)		// カウントダウンの幅
#define COUNTDOWN_HEIGHT	(700.0f)		// カウントダウンの高さ

//=============================================================================
// 列挙型
//=============================================================================
enum ECountDown
{
	COUNTDOWN_3,
	COUNTDOWN_2,
	COUNTDOWN_1,
	COUNTDOWN_START,
	COUNTDOWN_MAX
};

//=============================================================================
// クラスの定義
//=============================================================================
class CCountDown : public CObject2D
{
public:
	//--------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------
	CCountDown(int nPriority = PRIORITY_LEVEL5);
	~CCountDown() override;

	//--------------------------------
	// メンバー関数
	//--------------------------------
	HRESULT Init(void) override;					// 初期化処理
	void Uninit(void) override;						// 終了処理
	void Update(void) override;						// 更新処理
	void Draw(void) override;						// 描画処理
	static CCountDown *Create(D3DXVECTOR3 pos);		// アイテムの生成関数
	static HRESULT Load(void);						// テクスチャの読み込み関数
	static void UnLoad(void);						// テクスチャの破棄関数
	static bool GetEndFlag(void) { return m_bCountDownEnd; }

private:
	//--------------------------------
	// メンバー変数
	//--------------------------------
	static LPDIRECT3DTEXTURE9 m_pTexture[COUNTDOWN_TEXTURE];		// テクスチャのポインタ
	int m_nCounter;
	static bool m_bCountDownEnd;

	CObject2D *m_pObject;
};

#endif