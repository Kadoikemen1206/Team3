//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "title.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "meshfield.h"
#include "light.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �J�����̃^�C�v�擾
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TITLE);
	CApplication::GetCamera()->Init();

	// ���C�g�̐���
	m_pLight = CLight::Create();

	// ���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-350.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);		// �J����

	// ���C�g�̉���E�폜
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �C���X�^���X�̉������
	CObject::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInput *pInput = CApplication::GetInput();

	// �J�����̏��擾
	CCamera *pCamera = CApplication::GetCamera();

	// �J�����̎��_�ƒ����_�擾
	D3DXVECTOR3 posV = pCamera->GetPosV();
	D3DXVECTOR3 posR = pCamera->GetPosR();

	// ���_�ƒ����_�����ɂ��炵�Ă�������
	posV -= D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	posR -= D3DXVECTOR3(0.0f, 0.0f, 3.0f);

	// ���_�ƒ����_��ݒ�
	pCamera->SetPosV(posV);
	pCamera->SetPosR(posR);

	// ��ʑJ�ڏ���
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInput->Trigger(DIK_RETURN))
		{
			// �t�F�[�h����
			CFade::SetFade(CApplication::MODE_GAME);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CTitle * CTitle::Create()
{
	// �|�C���^�錾
	CTitle *pTitle = nullptr;

	// �C���X�^���X����
	pTitle = new CTitle;

	if (pTitle != nullptr)
	{// �|�C���^�����݂�������s
		pTitle->Init();
	}
	else
	{// �|�C���^����������������s
		assert(false);
	}

	// �|�C���^��Ԃ�
	return pTitle;
}
