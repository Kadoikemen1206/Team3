//=============================================================================
//
// ビルボードでアイコンの表示 [icon.h]
// Author : Tanaka Kouta
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CIcon : public CBillboard
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CIcon(int nPriority = PRIORITY_LEVEL3);
	~CIcon() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理

	//セッター
	void SetPath(std::string path) { m_path = path; }
	void SetDestroy(bool set) { m_bDestroy = set; }
	void SetScaling(bool set) { m_bScaling = set; }
	void SetFade(bool set) { m_bFade = set; }
	void SetScaling(bool set, bool limit) { m_bScaling = set, m_bLimit = limit; }

	static CIcon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, std::string url, int nPriority);    // 生成

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_beginScale;		//最初の大きさ
	std::string m_path;				//テクスチャのパス
	bool m_bScaling;				//拡大をするかどうか
	bool m_bFade;					//フェードをさせるかどうか
	bool m_bLimit;					//一定数拡大させたら縮小するかどうか
	bool m_bDestroy;				//アイコンを消すかどうか
	bool m_bAnim;					//アニメーションをするかどうか
};

#endif