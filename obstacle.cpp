//=============================================================================
//
// ��Q������ [obstacle.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "obstacle.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObstacle::CObstacle(int nPriority)
{
	m_nTriggerCount1 = 0;
	m_nTriggerCount2 = 0;
	m_nAlternateFlag = false;
	PlayerGoalFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObstacle::Init()
{
	CGimmick::Init();

	//���f���̃��[�h
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObstacle::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObstacle::Update()
{
	//�M�~�b�N�̍X�V
	CGimmick::Update();
	D3DXVECTOR3 ObstacleMove = GetMove();
	D3DXVECTOR3 ObstaclePos = CGimmick::GetPos();
	D3DXVECTOR3 PlayerPos1 = CGame::GetPlayer1P()->GetPos();		//�v���C���[1POS���̎擾
	D3DXVECTOR3 PlayerPos2 = CGame::GetPlayer2P()->GetPos();		//�v���C���[2POS���̎擾

	// �A�łœ����ǂ̏����֐��Ăяo��
	ObstacleMove = BarrageMoveWall(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);

	//************************************************
	// ���ݘA�łœ�����
	//************************************************
	//if (CGimmick::GetGimmickType() == GIMMICKTYPE_ALTERNATEMOVEWALL)
	//{// �M�~�b�N�̃^�C�v�����݂ɘA�łœ����ǂ����������s
	//	if (pInputKeyboard->Trigger(DIK_Z) && m_nAlternateFlag == false)
	//	{// Z�L�[������������s
	//		m_nTriggerCount++;
	//		m_nAlternateFlag = true;
	//	}
	//	if (pInputKeyboard->Trigger(DIK_C) && m_nAlternateFlag == true)
	//	{// C�L�[������������s
	//		m_nTriggerCount++;
	//		m_nAlternateFlag = false;
	//	}
	//	if (m_nTriggerCount >= 10)
	//	{
	//		// �M�~�b�N(��)����Ɉړ�
	//		ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	//
	//		// ���삪��������
	//		CGimmick::SetCompletion(true);
	//	}
	//}
	//if (CGimmick::GetGimmickType() == GIMMICKTYPE_SHAPE)
	//{// �M�~�b�N�̃^�C�v���}�`���ăM�~�b�N�����������s
	//	if (CGimmick::GetShapeType() == SHAPETYPE_AQUARE)
	//	{
	//		if (pInputKeyboard->Trigger(DIK_A))
	//		{// A�L�[������������s
	//			CGimmick::Uninit();
	//			return;
	//		}
	//	}
	//}

	// �v���C���[���S�[���������̊֐��Ăяo��
	//PlayerGoal(ObstaclePos, PlayerPos1, PlayerPos2, ObstacleMove);

	if (CGimmick::GetCompletion1P() == true)
	{// ���삪�����������Ɏ��s
		// �v���C���[�̃X�s�[�h�����ɖ߂�
		CGame::GetPlayer1P()->SetSpeed(5.0f);
	}
	if (CGimmick::GetCompletion2P() == true)
	{// ���삪�����������Ɏ��s
	 // �v���C���[�̃X�s�[�h�����ɖ߂�
		CGame::GetPlayer2P()->SetSpeed(5.0f);
	}

	//�ʒu�X�V
	ObstaclePos.x += ObstacleMove.x;
	ObstaclePos.y += ObstacleMove.y;
	ObstaclePos.z += ObstacleMove.z;

	//�ړ��ʌ���
	ObstaclePos.x += (0.0f - ObstacleMove.x) * 0.1f;
	ObstaclePos.y += (0.0f - ObstacleMove.y) * 0.1f;
	ObstaclePos.z += (0.0f - ObstacleMove.z) * 0.1f;

	SetMove(ObstacleMove);
	SetPos(ObstaclePos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObstacle::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// ��������
//=============================================================================
void CObstacle::ConstOperate(int barrage, int rotate)
{
}

//=============================================================================
// ���쏈��
//=============================================================================
CObstacle * CObstacle::Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype, SHAPETYPE shapetype, int nPriority)
{
	CObstacle *pObstacle = new CObstacle(nPriority);

	if (pObstacle != nullptr)
	{
		pObstacle->SetGimmickType(gimmicktype);
		pObstacle->SetShapeType(shapetype);
		pObstacle->Init();
		pObstacle->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObstacle;
}

//************************************************
// �A�łœ����ǂ̏���
//************************************************
D3DXVECTOR3 CObstacle::BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInput();

	if (CGimmick::GetCompletion1P() == false || CGimmick::GetCompletion2P() == false)
	{// ������������Ă��Ȃ������s
		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
			&&ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 150.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 150.0f <= P1Pos.z)
		{// �v���C���[�^�C�v��1P�������� && �M�~�b�N�͈͓̔��ɂ�����
			//�v���C���[1�𓮂����Ȃ��悤�ɂ���
			CGame::GetPlayer1P()->SetSpeed(0.0f);
		}
		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
			&&ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 150.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 150.0f <= P2Pos.z)
		{// �v���C���[�^�C�v��2P�������� && �M�~�b�N�͈͓̔��ɂ�����
			//�v���C���[2�𓮂����Ȃ��悤�ɂ���
			CGame::GetPlayer2P()->SetSpeed(0.0f);
		}
		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
		{// �M�~�b�N�̃^�C�v���A�łœ����ǂ����������s
			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P
				&&pInputKeyboard->Trigger(DIK_SPACE))
			{// �v���C���[�^�C�v��1P�������� && SPACE�L�[����������
				//�L�[���������ƂɃJ�E���g�������Ă���
				m_nTriggerCount1++;
				if (m_nTriggerCount1 >= 20)
				{// �J�E���g��20��ȏ�s��������s
					 // �M�~�b�N(��)����Ɉړ�
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
					// ���삪��������
					CGimmick::SetCompletion1P(true);
				}
			}
			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P
				&&pInputKeyboard->Trigger(DIK_LSHIFT))
			{// �v���C���[�^�C�v��2P�������� && SPACE�L�[����������
				//�L�[���������ƂɃJ�E���g�������Ă���
				m_nTriggerCount2++;
				if (m_nTriggerCount2 >= 20)
				{// �J�E���g��20��ȏ�s��������s
				 // �M�~�b�N(��)����Ɉړ�
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
					// ���삪��������
					CGimmick::SetCompletion2P(true);
				}
			}
		}
	}
	return ObstacleMove;
}

//************************************************
// �v���C���[���S�[���������̏���
//************************************************
bool CObstacle::PlayerGoal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove)
{
	if (CGimmick::GetGimmickType() == GIMMICKTYPE_GOAL)
	{
		if (ObstaclePos.x + 150.0f >= P1Pos.x && ObstaclePos.z + 50.0f >= P1Pos.z
			&&ObstaclePos.x - 150.0f <= P1Pos.x && ObstaclePos.z - 50.0f <= P1Pos.z
			&&CGimmick::GetCompletion1P() == false && PlayerGoalFlag == false
			|| ObstaclePos.x + 150.0f >= P2Pos.x && ObstaclePos.z + 50.0f >= P2Pos.z
			&&ObstaclePos.x - 150.0f <= P2Pos.x && ObstaclePos.z - 50.0f <= P2Pos.z
			&&CGimmick::GetCompletion2P() == false && PlayerGoalFlag == false)
		{// �M�~�b�N�͈̔� && ������������Ă��Ȃ������s
		 //�Q�[���N���A
			PlayerGoalFlag = true;
			if (PlayerGoalFlag == true)
			{
				// �J��
				CFade::SetFade(CApplication::MODE_TITLE);
			}
		}
	}

	return false;
}
