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

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObstacle::CObstacle(int nPriority)
{
	m_nTriggerCount = 0;
	m_nAlternateFlag = false;
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
	LoadModel("Data\\MODEL\\aquare.x");

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
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();		//�v���C���[POS���̎擾
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	if (ObstaclePos.x + 150.0f >= PlayerPos.x && ObstaclePos.z + 150.0f >= PlayerPos.z
		&&ObstaclePos.x - 150.0f <= PlayerPos.x && ObstaclePos.z - 150.0f <= PlayerPos.z
		&&CGimmick::GetCompletion() == false)
	{// �M�~�b�N�͈̔�&&������������Ă��Ȃ������s

		// �v���C���[�𓮂����Ȃ��悤�ɂ���
		CGame::GetPlayer()->SetSpeed(0.0f);

		if (CGimmick::GetGimmickType() == GIMMICKTYPE_BARRAGEMOVEWALL)
		{// �M�~�b�N�̃^�C�v���A�łœ����ǂ����������s
			if (pInputKeyboard->Trigger(DIK_SPACE))
			{// SPACE�L�[������������s

				//�L�[���������ƂɃJ�E���g�������Ă���
				m_nTriggerCount++;
				if (m_nTriggerCount >= 20)
				{// �J�E���g��20��ȏ�s��������s

					 // �M�~�b�N(��)����Ɉړ�
					ObstacleMove = D3DXVECTOR3(0.0f, 2.5f, 0.0f);

					// ���삪��������
					CGimmick::SetCompletion(true);
				}
			}
		}
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
	}
	if (CGimmick::GetCompletion() == true)
	{// ���삪�����������Ɏ��s

		// �v���C���[�̃X�s�[�h�����ɖ߂�
		CGame::GetPlayer()->SetSpeed(5.0f);
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
