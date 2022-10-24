//=============================================================================
//
// 入力処理 [input.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "input.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput() : m_pDevice(nullptr)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInput::Uninit()
{
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//キーボードへのアクセス権を破棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CInput::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力処理

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//キーボードのトリガー情報を保存
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];		//キーボードのリリース情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];																//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//=============================================================================
//キーボードのプレス情報を取得
//=============================================================================
bool CInput::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//キーボードのトリガー情報を取得
//=============================================================================
bool CInput::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//キーボードのリリース情報を取得
//=============================================================================
bool CInput::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}