//=============================================================================
//
// ��Q������ [obstacle.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include "push_move_wall.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "billboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPushMoveWall::CPushMoveWall(int nPriority)
{
	m_PosOld = {};
	m_nTriggerCount = 0;
	m_Completion = false;

	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPushMoveWall::~CPushMoveWall()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPushMoveWall::Init()
{
	// �M�~�b�N�̏�����
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//���f���̃��[�h
	LoadModel("BUGGY");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPushMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPushMoveWall::Update()
{
	if (GetCompletion() == false)
	{
		// �M�~�b�N�̍��W,�ړ��ʎ擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		/* ��Gimmick�N���A���Ă��Ȃ��� */

		// �����蔻��̃`�F�b�N
		Collision(CGame::GetPlayer1P());
		Collision(CGame::GetPlayer2P());

		if (GetHitPlayer() == nullptr)
		{
			return;
		}

		// �M�~�b�N����
		ConstOperate();

		if (GetHitPlayer())
		{
			CPlayer* hitPlayer = GetHitPlayer();

			hitPlayer->SetSpeed(2.5f);
			move = D3DXVECTOR3(0.0f, 0.0f, 2.5f);
			if(pos.z)
		}

		// �M�~�b�N�̍X�V
		CGimmick::Update();

		// �ʒu�X�V
		pos += move;

		// �ړ��ʌ���
		pos.x += (0.0f - move.x) * 0.1f;
		pos.y += (0.0f - move.y) * 0.1f;
		pos.z += (0.0f - move.z) * 0.1f;

		SetPos(pos);	// ���W�̐ݒ�
		SetMove(move);	// �ړ��ʂ̐ݒ�
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPushMoveWall::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// ���쏈��
//=============================================================================
void CPushMoveWall::ConstOperate()
{
	if (GetHitPlayer())
	{
		return;
	}

	/* ���v���C���[�ƐڐG������ */

	if (GetCompletion())
	{
		return;
	}
}

//=============================================================================
// ��������
//=============================================================================
CPushMoveWall* CPushMoveWall::Create(const D3DXVECTOR3& pos)
{
	CPushMoveWall *pObstacle = new CPushMoveWall();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_PUSHMOVEWALL);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
