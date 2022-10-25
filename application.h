//=============================================================================
//
// マネージャ処理 [application.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラスの前方定義
//=============================================================================
class CInput;
class CCamera;
class CLight;
class CObjectX;
class CMeshfield;
class CTime;
class CTexture;

//=============================================================================
// クラスの定義
//=============================================================================
class CApplication
{
public:

	//=============================================================================
	// 列挙型
	//=============================================================================
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_TUTORIAL,
		MODE_MAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CApplication();
	~CApplication();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer();
	static CInput *GetInputKeyboard();
	static CCamera *GetCamera() { return m_pCamera; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }
	static CTexture *GetTexture() { return m_pTexture; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static CRenderer *m_pRenderer;
	static CInput *m_pInputKeyboard;
	static MODE m_mode;
	static CObject *m_pMode;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CMeshfield *m_pMeshField;
	static CTime *m_pTime;
	static CTexture *m_pTexture;

	static CObjectX *m_apObject3D[4];
};

#endif