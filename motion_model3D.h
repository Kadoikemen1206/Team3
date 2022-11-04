//=============================================================================
//
// 3Dモーションキャラクタークラス(motion_model3D.h)
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行う
//
//=============================================================================
#ifndef _MOTION_MODEL3D_H_			// このマクロ定義がされてなかったら
#define _MOTION_MODEL3D_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotion;

//=============================================================================
// 3Dプレイヤークラス
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行うクラス
//=============================================================================
class CMotionModel3D : public CObject
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CMotionModel3D *Create();			// 3Dプレイヤーの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotionModel3D();
	~CMotionModel3D();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;											// 初期化
	void Uninit() override;												// 終了
	void Update() override;												// 更新
	void VtxUpdate() override {};
	void Draw() override;												// 描画

	// Setter
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; };				// 位置
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }			// 過去位置
	void SetRot(D3DXVECTOR3 rot) override { m_rot = rot; };				// 向き
	void SetSize(D3DXVECTOR3 size) override { m_size = size; }			// 大きさ
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ワールドマトリックスのセッター
	void SetMotion(const char *pName);									// モーション情報の設定
	void SetMove(D3DXVECTOR3 inMove) override { m_move = inMove; }
	void SetCol(D3DXCOLOR) override {};

	// Getter
	D3DXVECTOR3 GetPos() override { return m_pos; }						// 位置
	D3DXVECTOR3 GetPosOld() { return m_posOld; }						// 過去位置
	D3DXVECTOR3 GetRot()  override { return m_rot; }					// 向き
	D3DXVECTOR3 GetSize()  override { return m_size; }					// 大きさ
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }						// ワールドマトリックスのゲッター
	CMotion *GetMotion() { return m_pMotion; }							// モーション情報の取得
	D3DXVECTOR3 GetMove() override { return m_move; }
	D3DXCOLOR GetCol() override { return D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f); }

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMotion			*m_pMotion;				// モーションインスタンス
	D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3		m_pos;					// 位置
	D3DXVECTOR3		m_move;					// 
	D3DXVECTOR3		m_posOld;				// 過去位置
	D3DXVECTOR3		m_rot;					// 向き
	D3DXVECTOR3		m_size;					// 大きさ
};

#endif