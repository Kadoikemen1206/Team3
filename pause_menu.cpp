//=============================================================================
//
// �^�C�g�����j���[���� [title_menu.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "pause_menu.h"
#include "pause_logo.h"
#include "application.h"
#include "input.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CObject2D * CPauseMenu::m_apObject2D[6] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPauseMenu::CPauseMenu(int nPriority) :
	m_nTextureMax(6),
	m_bGame(false),
	m_bTutorial(false),
	m_bRanking(false),
	m_bSelect(false),
	m_bGameMenu(false)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPauseMenu::~CPauseMenu()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPauseMenu::Init()
{
	// �^�C�g�����j���[ [�w�i]
	m_apObject2D[0] = CObject2D::Create("TITLEMENU_BG", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF - 30.0f, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1300.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [GAME]
	m_apObject2D[1] = CObject2D::Create("TITLEMENU_GAME", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [TUTORIAL]
	m_apObject2D[2] = CObject2D::Create("TITLEMENU_TUTORIAL", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [RANKING]
	m_apObject2D[3] = CObject2D::Create("TITLEMENU_RANKING", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [SOLO]
	m_apObject2D[4] = CObject2D::Create("TITLEMENU_SOLO", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_apObject2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// �^�C�g�����j���[ [VS]
	m_apObject2D[5] = CObject2D::Create("TITLEMENU_VS", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	m_apObject2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// �I�u�W�F�N�g�̏���������
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPauseMenu::Uninit()
{
	// �I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPauseMenu::Update()
{
	// ���W�擾
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		m_pos[nCnt] = m_apObject2D[nCnt]->GetPos();
	}

	// ���j���[���o������
	PutoutMenu();

	// ���j���[���I������
	SelectMenu();

	// �I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPauseMenu::Draw()
{
	// �I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//=============================================================================
// ���j���[���o������
//=============================================================================
void CPauseMenu::PutoutMenu(void)
{
	// �^�C�g�����j���[[�ǎ�]�o��
	//if (CPauseMenu::GetTitleMenuFlag())
	{
		if (m_pos[0].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[0]->SetMove(D3DXVECTOR3(30.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[0]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bRanking = true;
		}
	}

	// �^�C�g�����j���[[RANKING]�o��
	if (m_bRanking)
	{
		if (m_pos[3].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bTutorial = true;
		}
	}

	// �^�C�g�����j���[[TUTORIAL]�o��
	if (m_bTutorial)
	{
		if (m_pos[2].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bGame = true;
		}
	}

	// �^�C�g�����j���[[GAME]�o��
	if (m_bGame)
	{
		if (m_pos[1].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_bSelect = true;
		}
	}
}

//=============================================================================
// ���j���[���I������
//=============================================================================
void CPauseMenu::SelectMenu(void)
{
	//// �L�[�{�[�h�̏��擾
	//CInput *pInput = CApplication::GetInput();

	//if (m_bSelect)
	//{
	//	if (m_bGameMenu == false)
	//	{
	//		// ���j���[�I��
	//		if (pInput->Trigger(DIK_A))
	//		{//W�L�[�����͂��ꂽ�Ƃ�
	//			m_eMenu--;
	//			if (m_eMenu < 0)
	//			{
	//				m_eMenu = 2;
	//			}
	//		}
	//		else if (pInput->Trigger(DIK_D))
	//		{//S�L�[�����͂��ꂽ�Ƃ�
	//			m_eMenu++;
	//			if (m_eMenu >= 3)
	//			{
	//				m_eMenu = 0;
	//			}
	//		}

	//		// ���j���[���̐F�̒���
	//		if (m_eMenu == MENU_GAME)
	//		{
	//			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//			m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//			m_apObject2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//			if (pInput->Trigger(DIK_RETURN))
	//			{
	//				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//				m_apObject2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//				m_bGameMenu = true;
	//			}
	//		}
	//		else if (m_eMenu == MENU_TUTORIAL)
	//		{
	//			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//			m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//			m_apObject2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//			if (m_pFade->GetFade() == CFade::FADE_NONE)
	//			{
	//				if (pInput->Trigger(DIK_RETURN))
	//				{
	//					// �t�F�[�h����
	//					CFade::SetFade(CApplication::MODE_TUTORIAL);
	//				}
	//			}
	//		}
	//		else
	//		{
	//			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//			m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//			m_apObject2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//			if (m_pFade->GetFade() == CFade::FADE_NONE)
	//			{
	//				if (pInput->Trigger(DIK_RETURN))
	//				{
	//					// �t�F�[�h����
	//					CFade::SetFade(CApplication::MODE_RANKING);
	//				}
	//			}
	//		}
	//	}

	//	else
	//	{
	//		// ���j���[�I��
	//		if (pInput->Trigger(DIK_A))
	//		{//W�L�[�����͂��ꂽ�Ƃ�
	//			m_eGameMenu--;
	//			if (m_eGameMenu < 0)
	//			{
	//				m_eGameMenu = 1;
	//			}
	//		}
	//		else if (pInput->Trigger(DIK_D))
	//		{//S�L�[�����͂��ꂽ�Ƃ�
	//			m_eGameMenu++;
	//			if (m_eGameMenu >= 2)
	//			{
	//				m_eGameMenu = 0;
	//			}
	//		}

	//		// ���j���[���̐F�̒���
	//		if (m_eGameMenu == MENU_SOLO)
	//		{
	//			m_apObject2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//			m_apObject2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//			if (pInput->Trigger(DIK_RETURN))
	//			{
	//				if (m_pFade->GetFade() == CFade::FADE_NONE)
	//				{
	//					if (pInput->Trigger(DIK_RETURN))
	//					{
	//						// �t�F�[�h����
	//						CFade::SetFade(CApplication::MODE_GAME_SOLO);
	//					}
	//				}
	//			}
	//		}
	//		else
	//		{
	//			m_apObject2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//			m_apObject2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//			if (pInput->Trigger(DIK_RETURN))
	//			{
	//				if (m_pFade->GetFade() == CFade::FADE_NONE)
	//				{
	//					if (pInput->Trigger(DIK_RETURN))
	//					{
	//						// �t�F�[�h����
	//						CFade::SetFade(CApplication::MODE_GAME_VS);
	//					}
	//				}
	//			}
	//		}

	//		if (pInput->Trigger(DIK_BACKSPACE))
	//		{
	//			m_apObject2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//			m_apObject2D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//			m_bGameMenu = false;
	//		}
	//	}
	//}

	//else
	//{
	//	if (pInput->Trigger(DIK_RETURN))
	//	{
	//		for (int nCnt = 0; nCnt < m_nTextureMax - 2; nCnt++)
	//		{
	//			// �^�C�g�����j���[ �V���[�g�J�b�g
	//			m_apObject2D[nCnt]->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f));
	//			m_bSelect = true;
	//		}
	//	}
	//}
}

//=============================================================================
// ��������
//=============================================================================
CPauseMenu * CPauseMenu::Create(void)
{
	//�|�C���^�錾
	CPauseMenu *pMenu = nullptr;

	//�C���X�^���X����
	pMenu = new CPauseMenu;

	if (pMenu != nullptr)
	{//�|�C���^�����݂�������s
		pMenu->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	return pMenu;
}