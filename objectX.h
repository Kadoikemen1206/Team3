//=============================================================================
//
// オブジェクトX処理 [objectX.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CObjectX : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObjectX(int nPriority = PRIORITY_LEVEL3);
	~CObjectX() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// 初期化処理
	void Uninit() override;										// 終了処理	
	void Update() override;										// 更新処理
	void Draw() override;										// 描画処理
	void VtxUpdate() override {};								// 頂点座標更新処理
	void SetPos(D3DXVECTOR3 pos) override;						// 座標設定処理
	void SetSize(D3DXVECTOR3 size) override;					// サイズ設定処理
	void SetMove(D3DXVECTOR3 move) override;					// 移動量設定処理
	void SetCol(D3DXCOLOR col) override;						// 色設定処理
	void SetRot(D3DXVECTOR3 rot) override;						// 向き設定処理
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// 座標取得処理
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// サイズ取得処理
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// 移動量取得処理
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// 向き取得処理
	D3DXCOLOR GetCol(void) override { return m_col; }			// 色取得処理

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);	// 生成処理
	void LoadModel(const char *aFileName);						// モデルの読み込み処理
	void Projection(void);										// 平行投影処理
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);	// 当たり判定
	//void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 PosOld);	// 当たり判定
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);							// 頂点最大値設定処理
	void SetMinVtx(D3DXVECTOR3 Minvtx);							// 頂点最小値設定処理
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }			// 頂点最大値取得処理
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }			// 頂点最小値取得処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_pos;					// 座標
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 座標
	D3DXVECTOR3 m_move;					// 角度
	D3DXVECTOR3 m_MinVtx;				// モデルの頂点最小値
	D3DXVECTOR3 m_MaxVtx;				// モデルの頂点最大値
	D3DXCOLOR m_col;					// 色
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	LPD3DXMESH m_pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD m_NumMat;						// マテリアル情報の数
};

#endif