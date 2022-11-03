//=============================================================================
//
// �^�C�g�����j���[���� [title_menu.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "title_menu.h"
#include "title_rogo.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CObject2D * CTitleMenu::m_apObject2D[4] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleMenu::CTitleMenu(int nPriority) :
	m_nTextureMax(4)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleMenu::~CTitleMenu()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleMenu::Init()
{
	// �^�C�g�����j���[ [�w�i]
	m_apObject2D[0] = CObject2D::Create("TITLEMENU_BG", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [GAME]
	m_apObject2D[1] = CObject2D::Create("TITLEMENU_GAME", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [TUTORIAL]
	m_apObject2D[2] = CObject2D::Create("TITLEMENU_TUTORIAL", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �^�C�g�����j���[ [RANKING]
	m_apObject2D[3] = CObject2D::Create("TITLEMENU_RANKING", D3DXVECTOR3(-(float)SCREEN_WIDTH_HALF, (float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	// �I�u�W�F�N�g�̏���������
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitleMenu::Uninit()
{
	// �I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitleMenu::Update()
{
	// ���W�擾
	D3DXVECTOR3 pos[4];
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		pos[nCnt] = m_apObject2D[nCnt]->GetPos();
	}

	// �^�C�g�����j���[[�ǎ�]�o��
	if (CTitleRogo::GetTitleMenuFlag())
	{
		if (pos[0].x < SCREEN_WIDTH_HALF)
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
		if (pos[3].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[3]->SetMove(D3DXVECTOR3(25.0f, 0.0f, 0.0f));
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
		if (pos[2].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[2]->SetMove(D3DXVECTOR3(35.0f, 0.0f, 0.0f));
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
		if (pos[1].x < SCREEN_WIDTH_HALF)
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(25.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apObject2D[1]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	// �I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitleMenu::Draw()
{
	// �I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CTitleMenu * CTitleMenu::Create(void)
{
	//�|�C���^�錾
	CTitleMenu *pTitleMenu = nullptr;

	//�C���X�^���X����
	pTitleMenu = new CTitleMenu;

	if (pTitleMenu != nullptr)
	{//�|�C���^�����݂�������s
		pTitleMenu->Init();
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	return pTitleMenu;
}
