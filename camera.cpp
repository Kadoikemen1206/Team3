//=============================================================================
//
// �J�������� [camera.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	//���_�E�����_�E�������ݒ肷��i�\���̂̏������j
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);							//���_
	m_posR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);								//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//������x�N�g�� ���Œ��OK!!
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����
	float fLength1 = (m_posV.x - m_posR.x);									//���_���璍���_��X���̋���
	float fLength2 = (m_posV.z - m_posR.z);									//���_���璍���_��Z���̋���
	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//���_���璍���_�܂ł̋���

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	//�J�����̈ړ�
	if (pInputKeyboard->GetPress(DIK_DOWN))
	{//��Ɉړ�
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_UP))
	{//���Ɉړ�
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_RIGHT))
	{//���Ɉړ�
		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_LEFT))
	{//�E�Ɉړ�
		m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posV.z -= cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//�����_�̐���
	if (pInputKeyboard->GetPress(DIK_C))
	{//���ɐ���
		m_rot.y += 0.05f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_Z))
	{//�E�ɐ���
		m_rot.y -= 0.05f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//���_�̐���
	if (pInputKeyboard->GetPress(DIK_E))
	{//���ɐ���
		m_rot.y += 0.05f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_Q))
	{//�E�ɐ���
		m_rot.y -= 0.05f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//�A�X�y�N�g��
		10.0f,											//�j�A�i�ǂ�����ǂ��܂ŃJ�����ŕ\�����邩�ݒ�j
		3000.0f);										//�t�@�[

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// ��������
//=============================================================================
CCamera * CCamera::Create(void)
{
	//�|�C���^�錾
	CCamera *pCamera = nullptr;

	//�C���X�^���X����
	pCamera = new CCamera;

	if (pCamera != nullptr)
	{//�|�C���^�����݂�������s
		pCamera->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pCamera;
}
