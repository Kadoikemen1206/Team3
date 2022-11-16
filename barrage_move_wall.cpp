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
#include "barrage_move_wall.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "sound.h"
#include "billboard.h"
#include "icon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBarrageMoveWall::CBarrageMoveWall(int nPriority)
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
CBarrageMoveWall::~CBarrageMoveWall()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBarrageMoveWall::Init()
{
	// �M�~�b�N�̏�����
	CGimmick::Init();

	m_PosOld = CObjectX::GetPos();

	//���f���̃��[�h
	LoadModel("BOOK04");
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	D3DXVECTOR3 pos = GetPos();
	pos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	SetPos(pos);

	//���f���̃��[�h
	m_Door = CObjectX::Create(GetPos() - D3DXVECTOR3(200.0f, 0.0f, 0.0f),PRIORITY_LEVEL3);
	m_Door->Init();
	m_Door->LoadModel("BOOK04");
	//m_Door->SetPos(GetPos() - D3DXVECTOR3(50.0f, 0.0f, 100.0f));
	pos = GetPos();
	pos -= D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_Door->SetPos(pos);
	m_Door->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));

	m_pIcon[0] = nullptr;
	m_pIcon[1] = nullptr;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBarrageMoveWall::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBarrageMoveWall::Update()
{
	if (GetCompletion())
	{
		/* ��Gimmick�N���A���Ă��遫 */

		// �M�~�b�N�̍��W,�ړ��ʎ擾
		D3DXVECTOR3 rot = GetRot();
		D3DXVECTOR3 move = GetMove();

		if (rot.y <= D3DX_PI * 0.5f)
		{
			move = D3DXVECTOR3(0.0f, -0.01f, 0.0f);
			rot = m_Door->GetRot();
			rot += move;
			m_Door->SetRot(rot);
			
			move = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
			// �ʒu�X�V
			rot = GetRot();
			rot += move;
			SetRot(rot);
		}
	}
	else
	{
		/* ��Gimmick�N���A���Ă��Ȃ��� */

		// �����蔻��̃`�F�b�N
		Collision(CGame::GetPlayer1P());
		if (CGame::GetPlayer2P() != nullptr)
		{
			Collision(CGame::GetPlayer2P());
		}

		if (GetHitPlayer() == nullptr)
		{
			return;
		}

		// �M�~�b�N����
		ConstOperate();

		CPlayer* hitPlayer = GetHitPlayer();

		hitPlayer->SetSpeed(0.0f);
		hitPlayer->SetMotionType(CPlayer::MOTION_PUSH);

		if (GetCompletion())
		{// ���삪�����������Ɏ��s
		 // �v���C���[�̃X�s�[�h�����ɖ߂�
			hitPlayer->SetMotionType(CPlayer::MOTION_NONE);
			hitPlayer->SetSpeed(5.0f);
		}

		auto pos = hitPlayer->GetPos();

		if (m_pIcon[0] != nullptr)
		{
			m_pIcon[0]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		}
		if (m_pIcon[1] != nullptr)
		{
			m_pIcon[1]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		}

		// �M�~�b�N�̍X�V
		CGimmick::Update();
		m_Door->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBarrageMoveWall::Draw()
{
	CGimmick::Draw();
	m_Door->Draw();
}

//=============================================================================
// ��������
//=============================================================================
void CBarrageMoveWall::ConstOperate()
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

	if (m_pIcon[0] == nullptr)
	{
		m_pIcon[0] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), "SPEECH_BUBBLE", PRIORITY_LEVEL3);
		m_pIcon[0]->SetScaling(true, true);
		m_pIcon[0]->SetAnimation(1, 1, 12, 1, true);
	}

	if (GetHitPlayer()->GetKeyIndex() == -1)
	{
		if (m_pIcon[1] == nullptr)
		{
			m_pIcon[1] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), "BUTTON_ENTER", PRIORITY_LEVEL3);
			m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
		}
	}
	else
	{
		if (m_pIcon[1] == nullptr)
		{
			m_pIcon[1] = CIcon::Create(GetHitPlayer()->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), "BUTTON_B", PRIORITY_LEVEL3);
			m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
		}
	}

	/* �����삪�������Ă��Ȃ��� */

	if (pInputKeyboard->Trigger(KEY_DECISION))
	{// SPACE�L�[����������J�E���g�𑝂₷
		m_nTriggerCount++;
		if (m_nTriggerCount >= 20)
		{// �J�E���g��20��ȏ�s��������s
		 // �M�~�b�N(��)����Ɉړ�
			m_pIcon[0]->Uninit();
			m_pIcon[1]->Uninit();
			// ���삪��������
			SetCompletion(true);
		}
	}
}

//=============================================================================
// �L�[���J�E���g����֐�
//=============================================================================
void CBarrageMoveWall::KeyCount()
{
	m_nTriggerCount++;
}

//=============================================================================
// ���쏈��
//=============================================================================
CBarrageMoveWall* CBarrageMoveWall::Create(const D3DXVECTOR3& pos)
{
	CBarrageMoveWall *pObstacle = new CBarrageMoveWall();

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(GIMMICKTYPE_BARRAGEMOVEWALL);
		pObstacle->SetPos(pos);
		pObstacle->Init();
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}
