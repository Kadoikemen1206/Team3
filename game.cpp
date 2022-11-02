//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
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

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer *CGame::m_pPlayer1P = nullptr;
CPlayer *CGame::m_pPlayer2P = nullptr;
CCamera *CGame::m_pCamera = nullptr;
CMeshfield *CGame::m_pMeshField = nullptr;
CLight *CGame::m_pLight = nullptr;
CTime *CGame::m_pTime = nullptr;

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
	// ���C�g�̐���
	m_pLight = CLight::Create();

	// �^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL4);

	// ���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ��Q�����쐬
	//CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_BARRAGEMOVEWALL, CGimmick::SHAPETYPE_AQUARE, CObject::PRIORITY_LEVEL3);

	// �M�~�b�N�̐���
	//CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_ARROW, CGimmick::SHAPETYPE_UP, CObject::PRIORITY_LEVEL3);

	//�v���C���[�̐���
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	CLoadStage::LoadAll(m_pPlayer1P->GetPos());
	m_pPlayer2P = CPlayer::Create(CPlayer::EPLAYER_2P, D3DXVECTOR3(700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	CLoadStage::LoadAll(m_pPlayer2P->GetPos());

	// �J�����̐ݒ�
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TWO);
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
		if (pInputKeyboard->Trigger(DIK_RETURN))
		{
			// �J��
			CFade::SetFade(CApplication::MODE_TITLE);
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