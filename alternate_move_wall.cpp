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
#include "alternate_move_wall.h"
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
CAlternateMoveWall::CAlternateMoveWall(int nPriority)
{
	m_PosOld = {};
	m_nTriggerCount = 0;

	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAlternateMoveWall::~CAlternateMoveWall()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CAlternateMoveWall::Init()
{
	// �M�~�b�N�̏�����
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//���f���̃��[�h
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CAlternateMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CAlternateMoveWall::Update()
{
	if (GetCompletion())
	{
		/* ��Gimmick�N���A���Ă��遫 */

		// �M�~�b�N�̍��W,�ړ��ʎ擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		move = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

		// �ʒu�X�V
		pos += move;

		// �ړ��ʌ���
		pos.x += (0.0f - move.x) * 0.1f;
		pos.y += (0.0f - move.y) * 0.1f;
		pos.z += (0.0f - move.z) * 0.1f;

		SetPos(pos);	// ���W�̐ݒ�
		SetMove(move);	// �ړ��ʂ̐ݒ�
	}
	else
	{
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

		CPlayer* hitPlayer = GetHitPlayer();

		hitPlayer->SetSpeed(0.0f);
		if (GetCompletion())
		{// ���삪�����������Ɏ��s
		 // �v���C���[�̃X�s�[�h�����ɖ߂�
			hitPlayer->SetSpeed(5.0f);
		}

		// �M�~�b�N�̍X�V
		CGimmick::Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CAlternateMoveWall::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// ��������
//=============================================================================
void CAlternateMoveWall::ConstOperate()
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInput();

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	/* ���v���C���[�ƐڐG���ĂȂ��� */

	if (GetCompletion())
	{
		return;
	}

	/* �����삪�������Ă��Ȃ��� */

	if (pInputKeyboard->Trigger(DIK_Z) && m_nAlternateFlag == false)
	{// Z�L�[������������s
		m_nTriggerCount++;
		m_nAlternateFlag = true;
	}
	if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag == true)
	{// C�L�[������������s
		m_nTriggerCount++;
		m_nAlternateFlag = false;
	}
	if (m_nTriggerCount >= 20)
	{
		// ���삪��������
		CGimmick::SetCompletion(true);
	}
}

//=============================================================================
// �L�[���J�E���g����֐�
//=============================================================================
void CAlternateMoveWall::KeyCount()
{
	m_nTriggerCount++;
}

//=============================================================================
// ���쏈��
//=============================================================================
CAlternateMoveWall* CAlternateMoveWall::Create(const D3DXVECTOR3& pos)
{
	CAlternateMoveWall *pObstacle = new CAlternateMoveWall();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_BARRAGEMOVEWALL);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
