//=============================================================================
//
// �}�l�[�W������ [application.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshfield.h"
#include "time.h"
#include "number.h"
#include "texture.h"
#include "model.h"
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "fade.h"
#include "objectX_group.h"
#include "obstacle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInput = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CObjectXGroup *CApplication::m_pObjectXGroup = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CApplication::CApplication()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplication::~CApplication()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����̏�����
	srand((unsigned int)time(0));

	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;
	//�����_�����O�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{ //���������������s�����ꍇ
		return -1;
	}

	//�C���v�b�g�N���X�̐���
	m_pInput = new CInput;
	//�C���v�b�g�̏���������
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{ //���������������s�����ꍇ
		return -1;
	}

	// �J�����̏�����
	m_pCamera = new CCamera;
	//m_pCamera->SetCameraType(CCamera::CAMERATYPE_ONE);	// �\��
	m_pCamera->SetCameraType(CCamera::CAMERATYPE_TWO);		// VS
	m_pCamera->Init();

	// �e�N�X�`���̐���
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// ���f���̐���
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	//���[�h����
	CFade::Create(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CApplication::Uninit(void)
{
	//�I�u�W�F�N�g�̑S�J��
	CObject::UninitAll();

	// �e�N�X�`���̍폜
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// X���f���̍폜
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}

	//�����_�����O�̉���E�폜
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�C���v�b�g�̉���E�폜
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//�J�����̉���E�폜
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CApplication::Update(void)
{
	//�C���v�b�g�̍X�V����
	if (m_pInput != nullptr)
	{
		m_pInput->Update();
	}

	//�J�����̍X�V����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//�����_�����O�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CApplication::Draw(void)
{
	//�����_�����O�̕`�揈��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �����_�����O�̃|�C���^��Ԃ�����
//=============================================================================
CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// �C���v�b�g�̃|�C���^��Ԃ�����
//=============================================================================
CInput * CApplication::GetInput()
{
	return m_pInput;
}

//=============================================================================
// ���[�h�Z�b�g����
//=============================================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	CObject::ModeRelease();

	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case MODE_GAME:
		m_pMode = CGame::Create();
		break;
	case MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
		break;
	}
}

//=============================================================================
// ���[�h���擾���鏈��
//=============================================================================
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}