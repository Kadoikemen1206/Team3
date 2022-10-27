//=============================================================================
//
// ゲーム処理 [game.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object2D.h"
#include "mode.h"

//=============================================================================
// 前方定義
//=============================================================================
class CPlayer;
class CCamera;
class CMeshfield;
class CTime;
class CFade;

//=============================================================================
// クラスの定義
//=============================================================================
class CGame : public CMode
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CGame();
	~CGame() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// 初期化処理
	void Uninit(void) override;		// 終了処理
	void Update(void) override;		// 更新処理
	void Draw(void) override;		// 描画処理
	static CGame *Create();			// 生成処理

	static CPlayer *GetPlayer1P() { return m_pPlayer1P; }
	static CPlayer *GetPlayer2P() { return m_pPlayer2P; }
	static CCamera *GetCamera() { return m_pCamera; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	static CPlayer *m_pPlayer1P;			// 1Pプレイヤーのポインタ
	static CPlayer *m_pPlayer2P;			// 2Pプレイヤーのポインタ
	static CCamera *m_pCamera;				// カメラのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ	
	static CTime *m_pTime;					// タイムのポインタ
	CFade *m_pFade;							// フェードのポインタ
};

#endif