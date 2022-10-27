//=============================================================================
//
// モード処理 [mode.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// 前方定義
//=============================================================================
class CTitle;
class CGame;
class CResult;

//=============================================================================
// クラスの定義
//=============================================================================
class CMode : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CMode();
	~CMode() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override { return S_OK; };							// 初期化処理
	void Uninit() override {};											// 終了処理						
	void Update() override {};											// 更新処理
	void Draw() override {};											// 描画処理
	void VtxUpdate() override {};										// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override { D3DXVECTOR3 i = pos; };		// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override { D3DXVECTOR3 i = size; };	// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override { D3DXVECTOR3  i = move; };	// 移動量設定処理
	void SetCol(D3DXCOLOR col) override { D3DXCOLOR i = col; };			// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override { D3DXVECTOR3 i = rot; };		// 向き設定処理
	D3DXVECTOR3 GetPos(void) override { return D3DXVECTOR3(); }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return D3DXVECTOR3(); }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return D3DXCOLOR(); }				// 色取得処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CTitle *m_pTitle;
	CGame *m_pGame;
	CResult *m_pResult;
};

#endif