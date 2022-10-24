//=============================================================================
//
// 入力処理 [input.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define NUM_KEY_MAX	(256)		//キーの最大値

//=============================================================================
//キーの種類
//=============================================================================
typedef enum
{
	JOYKEY_UP = 0,			//十字キー（上）
	JOYKEY_DOWN,			//十字キー（下）
	JOYKEY_LEFT,			//十字キー（左）
	JOYKEY_RIGHT,			//十字キー（右）
	JOYKEY_START,			//STARTボタン
	JOYKEY_BACK,			//BACKボタン
	JOYKEY_PUSHLSTICK,		//左スティック押し込み
	JOYKEY_PUSHRSTICK,		//右スティック押し込み
	JOYKEY_LBUTTON5,		//左ボタン上
	JOYKEY_RBUTTON5,		//右ボタン上
	JOYKEY_10,				//不明
	JOYKEY_11,				//不明
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yボタン
	JOYKEY_LEFT_STICK,		//Lスティック
	JOYKEY_RIGHT_STICK,		//Rスティック
	JOYKEY_MAX
}JOYKEY;

class CInput
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CInput();
	virtual ~CInput();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

protected:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 m_pDevice;
	LPDIRECTINPUT8 m_pInput;
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

#endif