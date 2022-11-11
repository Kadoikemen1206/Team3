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
#include "goal.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"
#include "model.h"
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal(int nPriority)
{
	m_GoalCount = MAX_REVERBERATION_TIME;
	m_GoalFlag = false;

	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_GIMMICK);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGoal::Init()
{
	// �M�~�b�N�̏�����
	CGimmick::Init();

	//���f���̃��[�h
	LoadModel("CROWN");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGoal::Uninit()
{
	CGimmick::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGoal::Update()
{
	// �M�~�b�N�̍��W,�ړ��ʎ擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	if (GetHitPlayer() == nullptr)
	{
		return;
	}

	// �����蔻��̃`�F�b�N
	CollisionGimmick(CGame::GetPlayer1P());
	if (CGame::GetPlayer2P() != nullptr)
	{
		CollisionGimmick(CGame::GetPlayer2P());
	}

	// �M�~�b�N����
	ConstOperate();

	CPlayer* hitPlayer = GetHitPlayer();

	hitPlayer->SetSpeed(0.0f);
	m_GoalCount--;
	if ((m_GoalCount % 20) == 0)
	{
		int max = 50;
		int minPosZ = -(rand() % 350);
		int maxPosZ = rand() % 350;

		for (int i = 0; i < max; i++)
		{
			m_pParticle = CParticle::Create(D3DXVECTOR3(pos.x, pos.y + 180.0f, (rand() % maxPosZ) - minPosZ),
				D3DXVECTOR3(sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))) * cosf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), cosf((rand() % max * ((360 / max) * (D3DX_PI / 180))))),
				D3DXCOLOR((rand() % 100) * 0.01f, (rand() % 100) * 0.01f, (rand() % 100) * 0.01f, 1.0f),
				"PARTICLE_FLARE",
				PRIORITY_LEVEL3);
		}
	}
	if (m_GoalCount <= 0)
	{
		// �t�F�[�h����
		CFade::SetFade(CApplication::MODE_RANKING);
		m_GoalCount = MAX_REVERBERATION_TIME;
	}

	// �M�~�b�N�̍X�V
	CGimmick::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGoal::Draw()
{
	CGimmick::Draw();
}

//=============================================================================
// ��������
//=============================================================================
void CGoal::ConstOperate()
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
}

//=============================================================================
// ���쏈��
//=============================================================================
CGoal* CGoal::Create(const D3DXVECTOR3& pos)
{
	CGoal *pObstacle = new CGoal();

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
