//=============================================================================
//
// �^�C�g�����S���� [title_rogo.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "title_rogo.h"
#include "object2D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleRogo::CTitleRogo(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleRogo::~CTitleRogo()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleRogo::Init()
{
	//THERE IS RUN DOLL
	CObject2D::Create("TITLE_D", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_E_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_E_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_I", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_L_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_L_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_N", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_H", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_O", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_R_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_R_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_S", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_U", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	CObject2D::Create("TITLE_T", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �I�u�W�F�N�g�̏���������
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitleRogo::Uninit()
{
	// �I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitleRogo::Update()
{
	// �I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitleRogo::Draw()
{
	// �I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CTitleRogo * CTitleRogo::Create(void)
{
	//�|�C���^�錾
	CTitleRogo *pTitleRogo = nullptr;

	//�C���X�^���X����
	pTitleRogo = new CTitleRogo;

	if (pTitleRogo != nullptr)
	{//�|�C���^�����݂�������s
		pTitleRogo->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	return pTitleRogo;
}
