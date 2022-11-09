//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "object.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "model.h"
#include "time.h"
#include "number.h"
#include "obstacle.h"
#include "load_stage.h"
#include "barrage_move_wall.h"
#include "alternate_move_wall.h"
#include "push_move_wall.h"
#include "pause.h"
#include "button_move_player.h"
#include "stop_gimmick.h"
#include "goal.h"
#include "random_door.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer *CGame::m_pPlayer1P = nullptr;
CPlayer *CGame::m_pPlayer2P = nullptr;
CCamera *CGame::m_pCamera = nullptr;
CMeshfield *CGame::m_pMeshField = nullptr;
CLight *CGame::m_pLight = nullptr;
CTime *CGame::m_pTime = nullptr;
CObstacle *CGame::m_pObstacle1P = nullptr;
CObstacle *CGame::m_pObstacle2P = nullptr;
CPause *CGame::m_pPause = nullptr;
CGame::EMode CGame::m_mode = CGame::EMode::SOLO;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//����
	srand((unsigned int)time(NULL));	//�N�����Ɉ�񂾂��s�����ߏ������ɏ���

	// ���C�g�̐���
	m_pLight = CLight::Create();

	// �^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 3,CObject::PRIORITY_LEVEL4);

	// ���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// �M�~�b�N�̐���(�A�ŃM�~�b�N)
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 1500.0f));
	// �M�~�b�N�̐���(���ݘA�ŃM�~�b�N)
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 3000.0f));
	// �M�~�b�N�̐���(�����M�~�b�N)
	//CPushMoveWall::Create(D3DXVECTOR3(-700.0f,0.0f,2000.0f));
	// �M�~�b�N�̐���(�{�^���������班�����i�ރM�~�b�N)
	//CButtonMovePlayer::Create(D3DXVECTOR3(-700.0f, -200.0f, 2000.0f));
	// �M�~�b�N�̐���(����������~�܂�M�~�b�N)
	//CStopGimmick::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));

	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	CRandomDoor::Create(D3DXVECTOR3(-800.0f + 75.0f * nCnt, 0.0f, 2000.0f));
	//}

	//�v���C���[�̐���
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	CLoadStage::LoadAll(m_pPlayer1P->GetPos());
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_ONE);
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 20.0f, 2000.0f));
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 45.0f, 2800.0f));
	//CButtonMovePlayer::Create(D3DXVECTOR3(-700.0f, -200.0f, 3600.0f));
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 4000.0f));
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 4300.0f));

	if (m_mode == EMode::VS)
	{
		//CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));
		// �M�~�b�N�̐���(�����M�~�b�N)
		CButtonMovePlayer::Create(D3DXVECTOR3(700.0f, 0.0f, 2000.0f));
		CAlternateMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 2800.0f));
		CButtonMovePlayer::Create(D3DXVECTOR3(700.0f, 0.0f, 3600.0f));
		CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 4000.0f));
		CBarrageMoveWall::Create(D3DXVECTOR3(700.0f, 0.0f, 4300.0f));

		m_pPlayer2P = CPlayer::Create(CPlayer::EPLAYER_2P, D3DXVECTOR3(700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
		CLoadStage::LoadAll(m_pPlayer2P->GetPos());
		CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TWO);
	}

	// �J�����̐ݒ�
	CApplication::GetCamera()->Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �i���o�[�̍폜
	CNumber::Unload();

	// �J�����̐ݒ�
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);

	// ���C�g�̉���E�폜
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	// �C���X�^���X�̉������
	CObject::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInput();

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (m_pPause == nullptr)
		{
			if (pInputKeyboard->Trigger(DIK_P))
			{
				m_pPause = CPause::Create();
			}
		}
		else
		{
			if (m_pPause->GetEndFlag())
			{
				static int count = 0;
				count++;

				if (count <= 20)
				{
					count = 0;
					m_pPause = nullptr;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CGame * CGame::Create()
{
	//�|�C���^�錾
	CGame *pGame = nullptr;

	//�C���X�^���X����
	pGame = new CGame;

	if (pGame != nullptr)
	{//�|�C���^�����݂�������s
		pGame->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pGame;
}