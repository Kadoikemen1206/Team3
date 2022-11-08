//=============================================================================
//
// タイム処理 [time.h]
// Author : kubota yuuki
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"

//=============================================================================
//  前方定義
//=============================================================================
class CNumber;

//=============================================================================
// クラスの定義
//=============================================================================
class CTime : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CTime(int nPriority = PRIORITY_LEVEL5);
	~CTime()override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// 初期化処理
	void Uninit() override;										// 終了処理
	void Update() override;										// 更新処理
	void Draw() override;										// 描画処理
	
	void VtxUpdate() override {};										// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override;								// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override { m_size = size; };			// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override { D3DXVECTOR3 i = move; };	// 移動量設定処理
	void SetCol(D3DXCOLOR col) override { D3DXCOLOR i = col; };			// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override { D3DXVECTOR3 i = rot; };		// 向き設定処理
	void SetDigit(int nDigit) { m_nDigit = nDigit; }					// 桁数設定処理

	D3DXVECTOR3 GetPos(void) override { return m_pos; }				// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }			// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }	// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }		// 向き取得処理
	D3DXCOLOR GetCol(void) override { return D3DXCOLOR(); }			// 色取得処理

	static CTime *Create(D3DXVECTOR3 pos,D3DXVECTOR3 size, int nScore, int nPriority);
	void SetTime(int nScore);
	void AddTime(int nValue);
	int GetTime();


private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static CNumber *m_apNumBer[5];
	D3DXVECTOR3 m_pos;							// 座標
	D3DXVECTOR3 m_size;							// サイズ
	int  m_nDigit;								// 使用する桁数
	int m_nTime;								// スタート時刻
	int  m_apnTime;								// 情報格納変数
};

#endif