//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <assert.h>
#include "application.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "objectX.h"
#include "player.h"
#include "shadow.h"
#include "renderer.h"
#include "meshfield.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : 
	m_nSpeed(5.0f)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init()
{
	//objectx��pos��rot
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 size = CObjectX::GetSize();
	D3DXVECTOR3 rot = CObjectX::GetRot();

	//�I�u�W�F�N�g�̏�����
	CObjectX::Init();

	//���f���̃��[�h
	LoadModel("Data\\MODEL\\AstroBot.x");

	//�ړI�̊p�x�̏�����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		

	//�e�̐���
	CShadow::Create(pos, size, CObject::PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update()
{
	//�L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	//�J�����̏��擾
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();

	//objectx��pos��rot
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 rot = CObjectX::GetRot();

	//�e��pos
	D3DXVECTOR3 ShadowPos = m_shadow->GetPos();

	if (pInputKeyboard->GetPress(DIK_W))
	{//��Ɉړ�
		if (pInputKeyboard->GetPress(DIK_A))
		{
			pos.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
		}
		else if (pInputKeyboard->GetPress(DIK_D))
		{
			pos.x += sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
		}
		else
		{
			pos.x += sinf(pCameraRot.y) * m_nSpeed;
			pos.z += cosf(pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_S))
	{//���Ɉړ�
		if (pInputKeyboard->GetPress(DIK_A))
		{
			pos.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->GetPress(DIK_D))
		{
			pos.x += sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
		}
		else
		{
			pos.x -= sinf(pCameraRot.y) * m_nSpeed;
			pos.z -= cosf(pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + 0.0f;
		}

	}
	else if (pInputKeyboard->GetPress(DIK_A))
	{//���Ɉړ�
		pos.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		pos.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
	}
	else if (pInputKeyboard->GetPress(DIK_D))
	{//�E�Ɉړ�
		pos.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		pos.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
	}

	//�p�x�̐��K��(�ړI�̊p�x)
	if (m_rotDest.y - rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//����������
	rot.y += (m_rotDest.y - rot.y) * 0.08f;

	//�p�x�̐��K��(���݂̊p�x)
	if (rot.y > D3DX_PI)
	{
		rot.y = rot.y - D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = rot.y + D3DX_PI * 2;
	}

	//���b�V���t�B�[���h�̃|�C���^���擾
	CMeshfield *pMeshField = CApplication::GetMeshfield();
	pMeshField->Collision(&pos);

	//�v���C���[��pos��rot�̐ݒ�
	CObjectX::SetPos(pos);
	CObjectX::SetRot(rot);

	//�e��pos�̐ݒ�
	m_shadow->SetPos(D3DXVECTOR3(pos.x, pos.y + 2.0f, pos.z));

	//CObjectX�̍X�V����
	CObjectX::Update();

	//CDebugProc::Print("���f���̌��݂̊p�x:%f\n���f���̖ړI�̊p�x:%f", rot.y, m_rotDest.y);
}

//=============================================================================
// ��������
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CPlayer *pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetPos(pos);

		pPlayer->m_shadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.5f, pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), CObject::PRIORITY_LEVEL3);
	}
	else
	{
		assert(false);
	}

	return pPlayer;
}