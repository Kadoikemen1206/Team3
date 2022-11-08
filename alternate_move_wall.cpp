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
CAlternateMoveWall::CAlternateMoveWall(int nPriority) :
	m_Screw(nullptr),
	m_buttonPushCount(0)
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
	LoadModel("POCKET_WATCH");

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

		CPlayer* hitPlayer = GetHitPlayer();

		if (hitPlayer->GetPos().x != 0.0f)
		{
			D3DXVECTOR3 pos = hitPlayer->GetPos();
			pos.x = GetPos().x;
			hitPlayer->SetPos(pos);
		}
		hitPlayer->SetMotionType(CPlayer::MOTION_SCREW);

		// �M�~�b�N����
		ConstOperate();

		m_buttonPushCount++;

		if (m_buttonPushCount >= 10)
		{
			hitPlayer->SetUpdateStop(true);
		}
		else
		{
			D3DXVECTOR3 rot = m_Screw->GetRot();
			rot.y += 0.04f;
			m_Screw->SetRot(rot);
		}

		hitPlayer->SetSpeed(0.0f);
		if (GetCompletion())
		{// ���삪�����������Ɏ��s
		 // �v���C���[�̃X�s�[�h�����ɖ߂�
			hitPlayer->SetSpeed(5.0f);
		}

		// �M�~�b�N�̍X�V
		CGimmick::Update();
		m_Screw->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CAlternateMoveWall::Draw()
{
	CGimmick::Draw();
	m_Screw->Draw();
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

	if (pInputKeyboard->Trigger(DIK_Z) && !m_nAlternateFlag)
	{// Z�L�[������������s
		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = true;
	}

	if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag)
	{// C�L�[������������s
		m_nTriggerCount++;
		GetHitPlayer()->SetUpdateStop(false);
		m_buttonPushCount = 0;
		m_nAlternateFlag = false;
	}

	if (m_nTriggerCount >= 40)
	{
		// ���삪��������
		GetHitPlayer()->SetMotionType(CPlayer::MOTION_NONE);
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
		pObstacle->m_Screw = CObjectX::Create(pos - D3DXVECTOR3(0.0f, 0.0f, 130.0f), CObject::PRIORITY_LEVEL3);
		pObstacle->m_Screw->LoadModel("SCREW WINDING");
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
