//=============================================================================
//
// �}�l�[�W������ [application.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
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

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInputKeyboard = nullptr;
CObject *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CMeshfield *CApplication::m_pMeshField = nullptr;
CTime *CApplication::m_pTime = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;
CObjectX *CApplication::m_apObject3D[4] = {};

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
	m_pInputKeyboard = new CInput;
	//�C���v�b�g�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{ //���������������s�����ꍇ
		return -1;
	}

	// �e�N�X�`���̐���
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// �J����
	m_pCamera = new CCamera;	// ����
	m_pCamera->Init();			// ������

	//���C�g�̐���
	m_pLight = CLight::Create();

	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL5);

	//�|���S���̐���
	//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//���f���̐���
	m_apObject3D[0] = CObjectX::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	m_apObject3D[1] = CObjectX::Create(D3DXVECTOR3(-100.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	m_apObject3D[2] = CObjectX::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);

	//�v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CApplication::Uninit(void)
{
	//�I�u�W�F�N�g�̑S�J��
	CObject::UninitAll();

	//�i���o�[�̍폜
	CNumber::Unload();

	// �e�N�X�`���̍폜
	m_pTexture->UnloadAll();
	
	//�����_�����O�̉���E�폜
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�C���v�b�g�̉���E�폜
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
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
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//�����_�����O�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//�J�����̍X�V����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//�L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_C))
	{
		m_apObject3D[3] = CObjectX::Create(D3DXVECTOR3(-200.0f, 100.0f, 0.0f), CObject::PRIORITY_LEVEL1);
	}

	if (pInputKeyboard->GetTrigger(DIK_V) && m_apObject3D[0] != nullptr)
	{
		m_apObject3D[0]->Uninit();
		m_apObject3D[0] = nullptr;
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
CInput * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}