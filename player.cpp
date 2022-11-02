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
#include "game.h"
#include "particle.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : 
	m_nSpeed(5.0f),					//�ړ��X�s�[�h
	m_rotDest(0.0f, 0.0f, 0.0f),	// �ړI�̊p�x
	m_bJumpFlag(false)				// �W�����v�������ǂ����̃t���O
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
	//�I�u�W�F�N�g�̏�����
	CObjectX::Init();

	//���f���̃��[�h
	LoadModel("PLAYER");

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update()
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInput();

	// �J�����̏��擾
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();

	// ���W�擾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	// �����擾
	D3DXVECTOR3 rot = CObjectX::GetRot();

	// �O��̈ʒu��ۑ�
	D3DXVECTOR3 move = CObjectX::GetMove();

	// �d�͐ݒ�
	move.y -= 1.0f;

	// �O��̈ʒu��ۑ�
	m_posOld = pos;

	// 1P�̏ꍇ���L�̈ړ����������s
	if (m_nType == EPLAYER_1P)
	{
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

		if (pInputKeyboard->Trigger(DIK_J))
		{// �W�����v
			m_bJumpFlag = true;
			move.y += 18.0f;
		}
	}
	
	// 2P�̏ꍇ���L�̈ړ����������s
	if (m_nType == EPLAYER_2P)
	{
		if (pInputKeyboard->Press(DIK_UP))
		{// ��Ɉړ�
			if (pInputKeyboard->Press(DIK_LEFT))
			{
				pos.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
			}
			else if (pInputKeyboard->Press(DIK_RIGHT))
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

		else if (pInputKeyboard->Press(DIK_DOWN))
		{// ���Ɉړ�
			if (pInputKeyboard->Press(DIK_LEFT))
			{
				pos.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
			}
			else if (pInputKeyboard->Press(DIK_RIGHT))
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
		else if (pInputKeyboard->Press(DIK_LEFT))
		{// ���Ɉړ�
			pos.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
		}
		else if (pInputKeyboard->Press(DIK_RIGHT))
		{// �E�Ɉړ�
			pos.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
		}
	}

	//�e�X�g�p
	if (pInputKeyboard->Press(DIK_PERIOD))
		m_pParticle = CParticle::Create(pos,
			D3DXVECTOR3(sinf((rand() % 25 * ((360 / 25) * (D3DX_PI / 180)))), 1.0f, cosf((rand() % 25 * ((360 / 25) * (D3DX_PI / 180))))),
			D3DXCOLOR(rand() % 100 * 0.01f, rand() % 100 * 0.01f, rand() % 100 * 0.01f, 1.0f),
			PRIORITY_LEVEL3);

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

	// �|�C���^�錾
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	// �ړ��ʉ��Z
	pos += move;

	// �v���C���[�ƃ��f���̓����蔻��
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
		{
			CObjectX *pObjectX = (CObjectX*)pObject;
			m_bIsLanding = pObjectX->Collision(&pos, &m_posOld, &CObjectX::GetSize());
			m_bIsLandingUp = pObjectX->UpCollision(&pos, &m_posOld, &CObjectX::GetSize(), &move);
		}

		//�|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
	}

	// ���b�V���t�B�[���h�̃|�C���^���擾
	//pMeshField->Collision(&pos);
	CMeshfield *pMeshField = CGame::GetMeshfield();

	float i = pMeshField->GetAnswer();

	// �v���C���[��pos��rot�̐ݒ�
	if (pos.y < pMeshField->GetAnswer())
	{
		m_bJumpFlag = false;
	}

	// ���b�V���t�B�[���h�Ƃ̓����蔻��
	if (m_bJumpFlag == false)
	{
		pMeshField->Collision(&pos);
	}

	// y�����ړ����ĂȂ������ꍇ
	if (pos.y == m_posOld.y)
	{
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �v���C���[��pos��rot��move�̐ݒ�
	CObjectX::SetPos(pos);
	CObjectX::SetRot(rot);
	CObjectX::SetMove(move);

	// CObjectX�̍X�V����
	CObjectX::Update();
}

//=============================================================================
// ��������
//=============================================================================
CPlayer * CPlayer::Create(EPLAYER type, const D3DXVECTOR3 pos, int nPriority)
{
	CPlayer *pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetType(type);
		pPlayer->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pPlayer;
}

//=============================================================================
// �^�C�v�ݒ菈��
//=============================================================================
void CPlayer::SetType(EPLAYER type)
{
	m_nType = type;
}
//=============================================================================
// �X�s�[�h�̐ݒ�
//=============================================================================
void CPlayer::SetSpeed(float speed)
{
	m_nSpeed = speed;
}