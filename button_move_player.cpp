//=============================================================================
//
// �{�^���������ƃv���C���[���i�ރM�~�b�N
// Author : saito shian
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include "button_move_player.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "billboard.h"
#include "icon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CButtonMovePlayer::CButtonMovePlayer(int nPriority)
{
	m_MoveCount = MAX_WALK_COUNT;
	m_TimeToMove = 0;
	m_RandNumber = 0;
	m_MoveFlag = false;
	m_RandFlag = false;

	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButtonMovePlayer::~CButtonMovePlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CButtonMovePlayer::Init()
{
	// �M�~�b�N�̏�����
	CGimmick::Init();

	//����
	srand((unsigned int)time(NULL));	//�N�����Ɉ�񂾂��s�����ߏ������ɏ���

	//���f���̃��[�h
	LoadModel("TABLE04");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CButtonMovePlayer::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CButtonMovePlayer::Update()
{
	// �M�~�b�N�̍X�V
	CGimmick::Update();

	// �M�~�b�N�̍��W,�ړ��ʎ擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// �����蔻��̃`�F�b�N
	bool bCollision1P = Collision(CGame::GetPlayer1P());
	bool bCollision2P = false;
	if (CGame::GetPlayer2P() != nullptr)
	{
		bCollision2P = Collision(CGame::GetPlayer2P());
	}

	// �v���C���[���ڐG�������̃|�C���^
	CPlayer* hitPlayer = GetHitPlayer();

	if (GetHitPlayer() != nullptr)
	{
		if (m_pIcon[0] == nullptr)
		{
			m_pIcon[0] = CIcon::Create(D3DXVECTOR3(hitPlayer->GetPos().x, hitPlayer->GetPos().y + 150.0f, hitPlayer->GetPos().z), D3DXVECTOR3(50.0f, 30.0f, 0.0f), "SPEECH_BUBBLE", PRIORITY_LEVEL3);
		}
		hitPlayer->SetSpeed(0.0f);
		hitPlayer->SetIsMove(false);
		ButtonPush();
	}

	// �M�~�b�N����
	ConstOperate();

	SetPos(pos);	// ���W�̐ݒ�
	SetMove(move);	// �ړ��ʂ̐ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CButtonMovePlayer::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// ���쏈��
//=============================================================================
void CButtonMovePlayer::ConstOperate()
{
	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	/* ���v���C���[�ƐڐG������ */

	if (!Collision(GetHitPlayer()))
	{
		// �v���C���[���ڐG�������̃|�C���^
		CPlayer* hitPlayer = GetHitPlayer();

		hitPlayer->SetIsMove(true);
		hitPlayer->SetSpeed(5.0f);
		hitPlayer = nullptr;
		SetCompletion(true);

		for (int i = 0; i < 2; i++)
		{
			if (m_pIcon[i] != nullptr)
			{
				m_pIcon[i]->Uninit();
			}
		}
		Uninit();
		return;
	}
}

//=============================================================================
// �L�[����������
//=============================================================================
void CButtonMovePlayer::ButtonPush()
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInput();

	// �v���C���[���ڐG�������̃|�C���^
	CPlayer* hitPlayer = GetHitPlayer();

	// �����_���ŉ����L�[�����܂�
	if (m_RandFlag == false)
	{
		m_RandNumber = rand() % 4 + 1;
		m_RandFlag = true;
	}
	else if (m_RandFlag == true && m_RandNumber == 1)
	{
		if (hitPlayer->GetKeyIndex() == -1)
		{
			str = "BUTTON_MKEY";
		}
		else
		{
			str = "BUTTON_B";
		}

		if (pInputKeyboard->Trigger(KEY_RIGHT_BUTTON)) //M
		{
			m_RandFlag = false;
		}
	}
	else if (m_RandFlag == true && m_RandNumber == 2)
	{
		if (hitPlayer->GetKeyIndex() == -1)
		{
			str = "BUTTON_VKEY";
		}
		else
		{
			str = "BUTTON_X";
		}

		if (pInputKeyboard->Trigger(KEY_LEFT_BUTTON)) //V
		{
			m_RandFlag = false;
		}
	}
	else if (m_RandFlag == true && m_RandNumber == 3)
	{
		if (hitPlayer->GetKeyIndex() == -1)
		{
			str = "BUTTON_BKEY";
		}
		else
		{
			str = "BUTTON_A";
		}

		if (pInputKeyboard->Trigger(KEY_DOWN_BUTTON)) //B
		{
			m_RandFlag = false;
		}
	}
	else if (m_RandFlag == true && m_RandNumber == 4)
	{
		if (hitPlayer->GetKeyIndex() == -1)
		{
			str = "BUTTON_NKEY";
		}
		else
		{
			str = "BUTTON_Y";
		}

		if (pInputKeyboard->Trigger(KEY_UP_BUTTON)) //N
		{
			m_RandFlag = false;
		}
	}

	auto pos = hitPlayer->GetPos();

	if (m_pIcon[1] == nullptr)
	{
		m_pIcon[1] = CIcon::Create(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z - 10.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), str, PRIORITY_LEVEL3);
		m_pIcon[1]->SetAnimation(2, 1, 12, 1, true);
	}
	else
	{
		m_pIcon[0]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		m_pIcon[1]->SetPos(D3DXVECTOR3(pos.x, pos.y + 150.0f, pos.z));
		m_pIcon[1]->BindTexture(str);
	}

	if (m_RandFlag == false && m_MoveFlag == false)
	{// �����_���Ō��܂����L�[���������Ƃ� && �v���C���[���~�܂�Ȃ��Ƃ����Ȃ��Ƃ����s
		m_MoveFlag = true;	
	}
	if (m_MoveFlag == true)
	{// �v���C���[��������悤�ɂȂ�Ƃ����s
		hitPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 2.0f));
		m_MoveCount--;
		if (m_MoveCount <= 0)
		{// �J�E���g��0�ȉ��ɂȂ�������s
			hitPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			// �ϐ���������
			m_MoveCount = MAX_WALK_COUNT;
			m_MoveFlag = false;
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CButtonMovePlayer* CButtonMovePlayer::Create(const D3DXVECTOR3& pos)
{
	CButtonMovePlayer *pObstacle = new CButtonMovePlayer();

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
