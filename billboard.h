#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"
#include <string>

class CBillboard : public CObject
{
public:
	enum EAlphaBlend
	{
		BLEND_NONE = 0,
		BLEND_ADDITIVE,
		BLEND_SUBSTRUCT,
		BLEND_MAX
	};

	enum EFlip
	{
		FLIP_NONE = 0,
		FLIP_HORIZON,
		FLIP_VERTICAL,
		FLIP_MAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CBillboard(int nPriority = PRIORITY_LEVEL3);
	~CBillboard() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// 初期化処理
	void Uninit() override;										// 終了処理
	void Update() override;										// 更新処理
	void Draw() override;										// 描画処理
	void VtxUpdate() override;									// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override;						// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override { m_size = size; }	// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override { m_move = move; }	// 移動量設定処理
	void SetCol(D3DXCOLOR col) override { m_col = col; }		// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override { m_rot = rot; }		// 向き設定処理
	void BindTexture(std::string inPath);						// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	void SetUV(float x_1, float x_2, float y_1, float y_2);		// テクスチャ座標更新処理
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);
	void SetFlip(EFlip flip);
	void SetRotate(bool set) { m_bIsRotate = set; }
	void SetBlend(EAlphaBlend blend) { m_blend = blend; }
	void SetStopAnim(const int X, const int Y);

	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }			// 色取得処理

	static CBillboard *Create(D3DXVECTOR3 pos, int nPriority);	// 生成処理
	void LoadTexture(const char *aFileName);					// テクスチャの読み込み

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動力
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_size;						// サイズ
	D3DXCOLOR m_col;						// 色
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;
	int m_DivisionX;						// X分割数
	int m_DivisionY;						// Y分割数
	int m_DivisionMAX;						// 最大分割数
	int m_AnimationSpeed;					// アニメーションする速度
	int m_AnimationSpdCnt;
	int m_Timer;							// タイマー
	int m_CntTime;							// 
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 角度
	bool m_bIsRotate;
	bool m_bAnimation;
	bool m_bLoop;
	EObjType m_type;						// オブジェクトのタイプ
	EAlphaBlend m_blend;
	EFlip m_flip;
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
};

#endif