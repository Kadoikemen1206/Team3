//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=============================================================================
// クラスの定義
//=============================================================================
class CObject
{
public:
	//-------------------------------------------------------------------------
	// 列挙型
	//-------------------------------------------------------------------------
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_BG,			//背景
		OBJTYPE_EFFECT,		//エフェクト
		OBJTYPE_NUMBER,		//番号
		OBJTYPE_SCORE,		//スコア
		OBJTYPE_MODE,		//モード
		OBJTYPE_TITLEROGO,	//タイトルロゴ
		OBJTYPE_COUNTDOWN,	//カウントダウン
		OBJTYPE_MODEL,		//モデル
		OBJTYPE_MAX,
		OBJTYPE_INVALID
	};

	enum EPRIORITY
	{
		PRIORITY_LEVEL0 = 0,
		PRIORITY_LEVEL1,
		PRIORITY_LEVEL2,
		PRIORITY_LEVEL3,
		PRIORITY_LEVEL4,
		PRIORITY_LEVEL5,
		PRIORITY_LEVELMAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	virtual HRESULT Init() = 0;							// 初期化処理
	virtual void Uninit() = 0;							// 終了処理						
	virtual void Update() = 0;							// 更新処理
	virtual void Draw() = 0;							// 描画処理
	virtual void VtxUpdate() = 0;						// 頂点座標更新処理
	virtual void SetPos(D3DXVECTOR3 pos) = 0;			// 座標設定処理
	virtual void SetSize(D3DXVECTOR3 size) = 0;			// サイズ設定処理
	virtual void SetMove(D3DXVECTOR3 move) = 0;			// 移動量設定処理
	virtual void SetCol(D3DXCOLOR col) = 0;				// 色設定処理
	virtual void SetRot(D3DXVECTOR3 rot) = 0;			// 向き設定処理
	virtual void SetType(const EObjType type);			// タイプ設定処理
	virtual EObjType GetObjType(void);					// オブジェクトのタイプ取得処理
	virtual D3DXVECTOR3 GetPos(void) = 0;				// 座標取得処理
	virtual D3DXVECTOR3 GetSize(void) = 0;				// サイズ取得処理
	virtual D3DXVECTOR3 GetMove(void) = 0;				// 移動量取得処理
	virtual D3DXVECTOR3 GetRot(void) = 0;				// 向き取得処理
	virtual D3DXCOLOR GetCol(void) = 0;					// 色取得処理
	virtual int GetID(void) { return m_nID; }			// 接続先の番号のゲッター


	static  void UninitAll(void);						// 全てのインスタンスの終了処理
	static  void UpdateAll(void);						// 全てのインスタンスの更新処理
	static  void DrawAll(void);							// 全てのインスタンスの描画処理
	static  void ModeRelease();							// モード以外だったら破棄処理
	void	Death(void);								// オブジェクト破棄処理

	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static CObject* GetCurrent(int nPriority) { return m_pCurrent[nPriority]; }
	CObject* GetNext() { return m_pNext; }

protected:
	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	void Release();										// インスタンスの解放処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static int m_nNumAll;										// オブジェクトの総数
	int m_nID;													// 接続先の番号	
	int m_nPriority;											// プライオリティの保存
	EObjType m_objType;											// オブジェクトの種類

	static CObject *m_pTop[PRIORITY_LEVELMAX];					// 先頭のオブジェクトへのポインタ
	static CObject *m_pCurrent[PRIORITY_LEVELMAX];				// 現在(一番後ろ)のオブジェクトへのポインタ
	CObject *m_pPrev;											// 前のオブジェクトへのポインタ
	CObject *m_pNext;											// 次のオブジェクトへのポインタ
	bool m_bDeath;												// 死フラグ
};

#endif