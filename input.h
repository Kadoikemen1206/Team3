//=============================================================================
//
// ���͏��� [input.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define NUM_KEY_MAX	(256)		//�L�[�̍ő�l

//=============================================================================
//�L�[�̎��
//=============================================================================
typedef enum
{
	JOYKEY_UP = 0,			//�\���L�[�i��j
	JOYKEY_DOWN,			//�\���L�[�i���j
	JOYKEY_LEFT,			//�\���L�[�i���j
	JOYKEY_RIGHT,			//�\���L�[�i�E�j
	JOYKEY_START,			//START�{�^��
	JOYKEY_BACK,			//BACK�{�^��
	JOYKEY_PUSHLSTICK,		//���X�e�B�b�N��������
	JOYKEY_PUSHRSTICK,		//�E�X�e�B�b�N��������
	JOYKEY_LBUTTON5,		//���{�^����
	JOYKEY_RBUTTON5,		//�E�{�^����
	JOYKEY_10,				//�s��
	JOYKEY_11,				//�s��
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�{�^��
	JOYKEY_LEFT_STICK,		//L�X�e�B�b�N
	JOYKEY_RIGHT_STICK,		//R�X�e�B�b�N
	JOYKEY_MAX
}JOYKEY;

class CInput
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CInput();
	virtual ~CInput();

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

protected:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 m_pDevice;
	LPDIRECTINPUT8 m_pInput;
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

#endif