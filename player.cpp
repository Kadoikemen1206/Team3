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
#include "obstacle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DXVECTOR3 CPlayer::m_pos = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : m_nSpeed(5.0f)
{
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_PLAYER);
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
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	// �J�����̏��擾
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();

	// ���W�擾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	// �����擾
	D3DXVECTOR3 rot = CObjectX::GetRot();

	// �O��̈ʒu��ۑ�
	m_posOld = pos;

	if (pInputKeyboard->Press(DIK_W))
	{// ��Ɉړ�
		if (pInputKeyboard->Press(DIK_A))
		{
			pos.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
		}
		else if (pInputKeyboard->Press(DIK_D))
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

	else if (pInputKeyboard->Press(DIK_S))
	{// ���Ɉړ�
		if (pInputKeyboard->Press(DIK_A))
		{
			pos.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->Press(DIK_D))
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
	else if (pInputKeyboard->Press(DIK_A))
	{// ���Ɉړ�
		pos.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		pos.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
	}
	else if (pInputKeyboard->Press(DIK_D))
	{// �E�Ɉړ�
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

	// ����������
	rot.y += (m_rotDest.y - rot.y) * 0.08f;

	// �p�x�̐��K��(���݂̊p�x)
	if (rot.y > D3DX_PI)
	{
		rot.y = rot.y - D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = rot.y + D3DX_PI * 2;
	}

	//�|�C���^�錾
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//�ϐ��錾
		CObject::EObjType objType;

		//�I�u�W�F�N�g�̃^�C�v���擾
		objType = pObject->GetObjType();

		if (objType == OBJTYPE_MODEL)
		{//�v���C���[�ƃ��f���̓����蔻��
			CObjectX *pObjectX = (CObjectX*)pObject;
			pObjectX->Collision(&pos, &m_posOld, &CObjectX::GetSize());
		}

		pObject = pObject->GetNext();
	}

	// ���b�V���t�B�[���h�̃|�C���^���擾
	CMeshfield *pMeshField = CApplication::GetMeshfield();
	//pMeshField->Collision(&pos);

	// �v���C���[��pos��rot�̐ݒ�
	CObjectX::SetPos(pos);
	CObjectX::SetRot(rot);

	// CObjectX�̍X�V����
	CObjectX::Update();

	m_pos = pos;

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

//=============================================================================
// �X�s�[�h�̐ݒ�
//=============================================================================
void CPlayer::SetSpeed(float speed)
{
	m_nSpeed = speed;
}