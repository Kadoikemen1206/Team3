//=============================================================================
//
// �J�������� [camera.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CCamera::CAMERATYPE CCamera::m_nCameraType = CAMERATYPE_NONE;

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
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nCameraType == CAMERATYPE_ONE)
	{
		// ���_�E�����_�E�������ݒ肷��i�\���̂̏������j
		m_posV[0] = D3DXVECTOR3(0.0f, 200.0f, -400.0f);						// ���_
		m_posR[0] = D3DXVECTOR3(0.0f, 0.0f, .0f);							// �����_
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// ������x�N�g�� ���Œ��OK!!
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ����
		float fLength1 = (m_posV[0].x - m_posR[0].x);						// ���_���璍���_��X���̋���
		float fLength2 = (m_posV[0].z - m_posR[0].z);						// ���_���璍���_��Z���̋���
		m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));	// ���_���璍���_�܂ł̋���
	}

	if (m_nCameraType == CAMERATYPE_TWO)
	{
		//************************
		// �v���C���[�̃J����
		//************************
		// ���_�A�����_�A�������ݒ肷��
		m_posV[0] = D3DXVECTOR3(0.0f, 200, -400.0f);
		m_posR[0] = D3DXVECTOR3(0.0f, 20.0f, -1.0f);
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//<-�Œ�ŗǂ�

		//************************
		// �Q�v���C���[�̃J����
		//************************
		// ���_�A�����_�A�������ݒ肷��
		m_posV[1] = D3DXVECTOR3(0.0f, 200, -400.0f);
		m_posR[1] = D3DXVECTOR3(0.0f, 20.0f, -1.0f);
		m_vecU[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// <-�Œ�ŗǂ�

		for (int nCnt = 0; nCnt < MAX_CAMERA; nCnt++)
		{
			// �O�����̒藝(sqrtf�̓��[�g�̖���)
			m_fDistance = sqrtf(((m_posR[nCnt].x - m_posV[nCnt].x) * (m_posR[nCnt].x - m_posV[nCnt].x)) + ((m_posR[nCnt].z - m_posV[nCnt].z) * (m_posR[nCnt].z - m_posV[nCnt].z)));
		}

		//************************
		// �v���C���[
		//************************
		// �r���[�|�[�g�\���̕ۑ�
		m_Viewport[0].X = 0;			// �r���[�|�[�g�̊J�n�ʒu(x���W)
		m_Viewport[0].Y = 0;			// �r���[�|�[�g�̊J�n�ʒu(y���W)
		m_Viewport[0].Width = 639;		// �r���[�|�[�g�̕�
		m_Viewport[0].Height = 720;		// �r���[�|�[�g�̍���
		m_Viewport[0].MinZ = 0.0f;
		m_Viewport[0].MaxZ = 1.0f;

		//************************
		// 2�v���C���[
		//************************
		// �r���[�|�[�g�\���̕ۑ�
		m_Viewport[1].X = 641;			// �r���[�|�[�g�̊J�n�ʒu(x���W)
		m_Viewport[1].Y = 0;			// �r���[�|�[�g�̊J�n�ʒu(y���W)
		m_Viewport[1].Width = 640;		// �r���[�|�[�g�̕�
		m_Viewport[1].Height = 720;		// �r���[�|�[�g�̍���
		m_Viewport[1].MinZ = 0.0f;
		m_Viewport[1].MaxZ = 1.0f;
	}

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
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer1P()->GetPos();		//�v���C���[POS���̎擾

	D3DXVECTOR3 PlayerPos1P = CGame::GetPlayer1P()->GetPos();		//�v���C���[POS���̎擾
	D3DXVECTOR3 PlayerPos2P = CGame::GetPlayer2P()->GetPos();		//�v���C���[POS���̎擾

	////************************
	//// �J�����̒Ǐ]����
	////************************
	//if (m_nCameraType == CAMERATYPE_ONE)
	//{ // �\�����[�h�̏ꍇ���s
	//	D3DXVECTOR3 PlayerPos = CGame::GetPlayer1P()->GetPos();        //�v���C���[POS���̎擾

	//	 //*******************************
	//	 // �J�����̒Ǐ]����
	//	 //*******************************
	//	 //�ړI�̒����_�̐ݒ�
	//	m_posRDest.z = PlayerPos.z;
	//	//�ړI�̎��_�̐ݒ�
	//	m_posVDest.z = PlayerPos.z - cosf(m_rot.y) * 250.0f;

	//	//���_�̌�������
	//	for (int nCnt = 0; nCnt < m_nCameraType; nCnt++)
	//	{
	//		m_posR[nCnt].z += (m_posRDest.z - m_posR[nCnt].z) * 0.1f;
	//		m_posV[nCnt].z += (m_posVDest.z - m_posV[nCnt].z) * 0.1f;
	//	}
	//}

	if (m_nCameraType == CAMERATYPE_TWO)
	{ // VS���[�h�̏ꍇ���s
		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P)
		{ //1P�̏ꍇ���s
			//�ړI�̒����_�̐ݒ�							  
			m_posRDest.z = PlayerPos1P.z;
			//�ړI�̎��_�̐ݒ�																				
			m_posVDest.z = PlayerPos1P.z - cosf(m_rot.y) * 250.0f;
			m_posR[0].z += (m_posRDest.z - m_posR[0].z) * 0.1f;
			m_posV[0].z += (m_posVDest.z - m_posV[0].z) * 0.1f;
		}
		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P)
		{ //2P�̏ꍇ���s
			//�ړI�̒����_�̐ݒ�							  
			m_posRDest.z = PlayerPos2P.z;
			//�ړI�̎��_�̐ݒ�																				
			m_posVDest.z = PlayerPos2P.z - cosf(m_rot.y) * 250.0f;
			m_posR[1].z += (m_posRDest.z - m_posR[1].z) * 0.1f;
			m_posV[1].z += (m_posVDest.z - m_posV[1].z) * 0.1f;
		}
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(int nCntCamera, CAMERATYPE type)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �^�C�v�ݒ�
	SetCameraType(type);

	////**************************************************
	////	�\�����[�h
	////**************************************************
	////if (type == CAMERATYPE_ONE)
	////{
	////	�r���[�}�g���b�N�X�̏����� 
	////	D3DXMatrixIdentity(&m_mtxView[0]);

	////	�r���[�}�g���b�N�X�̍쐬
	////	D3DXMatrixLookAtLH(&m_mtxView[0],
	////		&m_posV[0],
	////		&m_posR[0],
	////		&m_vecU[0]);

	////	�r���[�}�g���b�N�X�̐ݒ�
	////	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[0]);

	////	�v���W�F�N�V�����}�g���b�N�X�̏�����
	////	D3DXMatrixIdentity(&m_mtxProjection[0]);

	////	�v���W�F�N�V�����}�g���b�N�X�̍쐬
	////	D3DXMatrixPerspectiveFovLH(&m_mtxProjection[0],
	////		D3DXToRadian(45.0f),						//����p
	////		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��
	////		10.0f,										//�j�A�i�ǂ�����ǂ��܂ŃJ�����ŕ\�����邩�ݒ�j
	////		3000.0f);									//�t�@�[

	////	�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	////	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[0]);
	////}

	//**************************************************
	//	vs���[�h
	//**************************************************
	if (type == CAMERATYPE_TWO)
	{
		//�r���[�|�[�g�̐ݒ�
		pDevice->SetViewport(&m_Viewport[nCntCamera]);

		//�r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxView[nCntCamera]);

		//�r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView[nCntCamera],
			&m_posV[nCntCamera],
			&m_posR[nCntCamera],
			&m_vecU[nCntCamera]);

		//�r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[nCntCamera]);

		//�v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxProjection[nCntCamera]);

		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection[nCntCamera],
			D3DXToRadian(45.0f),																//����p
			(float)m_Viewport[nCntCamera].Width / (float)m_Viewport[nCntCamera].Height,			//�A�X�y�N�g��
			10.0f,																				//�ǂ�����(�j�A)�ǂ��܂�(�t�@�[)���J������
			3000.0f);																			//�\�����邩�ݒ�

		//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[nCntCamera]);
	}
}
// �J�����̎�ނ̐ݒ�
void CCamera::SetCameraType(CAMERATYPE type)
{
	m_nCameraType = type;
}

