#include "pause.h"
#include "object2D.h"
#include "input.h"
#include "application.h"
#include "pause_select.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause():
	CObject(PRIORITY_LEVEL0),
	m_endCount(0),
	m_beginCount(0)
{
	SetType(OBJTYPE_PAUSE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPause * CPause::Create()
{
	CPause *pPause = new CPause();

	if (pPause != nullptr)
	{
		pPause->Init();
		pPause->SetCanPoseUpdate();
	}
	else
	{
		assert(false);
	}

	return pPause;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPause::Init(void)
{
	m_pBg = CObject2D::Create("NONE", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_LEVEL4);
	m_pBg->SetCanPoseUpdate();
	m_pBg->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.5f));
	m_quit = CPauseSelect::Create(CPauseSelect::QUIT);
	m_retry = CPauseSelect::Create(CPauseSelect::RETRY);
	m_exit = CPauseSelect::Create(CPauseSelect::EXIT);
	m_select = QUIT;
	m_isBeginFlag = true;
	m_isEndFlag = false;
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPause::Uninit(void)
{
	m_quit->Uninit();
	m_retry->Uninit();
	m_exit->Uninit();
	m_pBg->Uninit();
	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CPause::Update(void)
{
	if (m_isBeginFlag)
	{
		BeginUpdate();
	}

	if (m_isEndFlag)
	{
		EndUpdate();
	}
	else
	{
		SelectUpdate();
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// 開始中更新
//=============================================================================
void CPause::BeginUpdate()
{
	m_beginCount++;
	m_quit->BeginUpdate();
	m_retry->BeginUpdate();
	m_exit->BeginUpdate();

	if (m_beginCount >= 30)
	{
		m_isBeginFlag = false;
	}
}

//=============================================================================
// 選択中更新
//=============================================================================
void CPause::SelectUpdate()
{
	// キーボードの情報取得
	CInput *pInput = CApplication::GetInput();

	if (pInput->Trigger(KEY_LEFT))
	{
		switch (m_select)
		{
		case CPause::QUIT:
			m_select = EXIT;
			break;
		case CPause::RETRY:
			m_select = QUIT;
			break;
		case CPause::EXIT:
			m_select = RETRY;
			break;
		default:
			break;
		}
	}
	else if (pInput->Trigger(KEY_RIGHT))
	{
		switch (m_select)
		{
		case CPause::QUIT:
			m_select = RETRY;
			break;
		case CPause::RETRY:
			m_select = EXIT;
			break;
		case CPause::EXIT:
			m_select = QUIT;
			break;
		default:
			break;
		}
	}

	switch (m_select)
	{
	case CPause::QUIT:
		m_quit->SelectNowUpdate();
		m_retry->SelectNoUpdate();
		m_exit->SelectNoUpdate();
		break;
	case CPause::RETRY:
		m_quit->SelectNoUpdate();
		m_retry->SelectNowUpdate();
		m_exit->SelectNoUpdate();
		break;
	case CPause::EXIT:
		m_quit->SelectNoUpdate();
		m_retry->SelectNoUpdate();
		m_exit->SelectNowUpdate();
		break;
	default:
		break;
	}

	if (pInput->Trigger(KEY_PAUSE))
	{
		m_select = QUIT;
		m_isEndFlag = true;
	}

	if (pInput->Trigger(KEY_DECISION))
	{
		m_isEndFlag = true;
	}
}

//=============================================================================
// 終了中更新
//=============================================================================
void CPause::EndUpdate()
{
	m_endCount++;

	switch (m_select)
	{
	case CPause::QUIT:
		m_quit->EndNowUpdate();
		m_retry->EndNoUpdate();
		m_exit->EndNoUpdate();
		break;
	case CPause::RETRY:
		m_quit->EndNoUpdate();
		m_retry->EndNowUpdate();
		m_exit->EndNoUpdate();
		break;
	case CPause::EXIT:
		m_quit->EndNoUpdate();
		m_retry->EndNoUpdate();
		m_exit->EndNowUpdate();
		break;
	default:
		break;
	}

	if (m_endCount >= 20)
	{
		Uninit();
		switch (m_select)
		{
		case CPause::QUIT:
			break;
		case CPause::RETRY:
			CFade::SetFade(CApplication::GetMode());
			break;
		case CPause::EXIT:
			CFade::SetFade(CApplication::MODE_TITLE);
			break;
		default:
			break;
		}
		return;
	}
}
