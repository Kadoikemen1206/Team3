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
	//���C�g�̐���
	m_pLight = CLight::Create();

	// �^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0, CObject::PRIORITY_LEVEL5);

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL2);

	//���f���̐���
	CObjectX::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);
	CObjectX::Create(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), CObject::PRIORITY_LEVEL3);

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		//���f���̐���(��)
		CModel::Create(D3DXVECTOR3(-150.0f, 0.0f, 200.0f + (380.0f * nCnt)), CObject::PRIORITY_LEVEL1);
	}

	//�v���C���[�̐���
	m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-50.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_pPlayer2P = CPlayer::Create(CPlayer::EPLAYER_2P, D3DXVECTOR3(50.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// ��Q�����쐬
	CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_BARRAGEMOVEWALL, CGimmick::SHAPETYPE_AQUARE, CObject::PRIORITY_LEVEL3);

	// �M�~�b�N�̐���
	CObstacle::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), CGimmick::GIMMICKTYPE_GOAL, CGimmick::SHAPETYPE_NONE, CObject::PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�i���o�[�̍폜
	CNumber::Unload();

	//���C�g�̉���E�폜
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//�C���X�^���X�̉������
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