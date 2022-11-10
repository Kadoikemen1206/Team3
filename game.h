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
class CObstacle;
class CPause;

//=============================================================================
// クラスの定義
//=============================================================================
class CGame : public CMode
{
public:
	enum class EMode
	{
		SOLO,
		VS
	};

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

	static void SetMode(EMode inMode) { m_mode = inMode; }
	static EMode GetMode() { return m_mode; }

	static CPlayer *GetPlayer1P() { return m_pPlayer1P; }
	static CPlayer *GetPlayer2P() { return m_pPlayer2P; }
	static CCamera *GetCamera() { return m_pCamera; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }

private:

	void SetGimmik(float x);

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	CObject2D *m_pObject2D;					// オブジェクト2Dのポインタ
	static EMode m_mode;					// モード
	static CPlayer *m_pPlayer1P;			// 1Pプレイヤーのポインタ
	static CPlayer *m_pPlayer2P;			// 2Pプレイヤーのポインタ
	static CCamera *m_pCamera;				// カメラのポインタ
	static CLight *m_pLight;				// ライトのポインタ
	static CMeshfield *m_pMeshField;		// メッシュフィールドのポインタ	
	static CTime *m_pTime;					// タイムのポインタ

	CFade *m_pFade;							// フェードのポインタ

	static CPause* m_pPause;				// ポーズ

	float m_RandDoor;						// ランダムドアの位置の変数

	bool m_isCountDownNow;				// カウントダウン中か否か
	int m_countDown;
};

#endif