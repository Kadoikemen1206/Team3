#include "pause.h"
#include "object2D.h"
#include "input.h"
#include "application.h"
#include "sound.h"
#include "pause_select.h"
#include "fade.h"
#include "time.h"

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
	// 背景の作成
	m_pBg = CObject2D::Create("NONE", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_LEVEL5);
	m_pBg->SetCanPoseUpdate();
	m_pBg->SetCol(D3DXCOLOR(0.0f,0.0f,0.0f,0.5f));

	// 選択肢の表示
	m_quit = CPauseSelect::Create(CPauseSelect::QUIT);
	m_retry = CPauseSelect::Create(CPauseSelect::RETRY);
	m_exit = CPauseSelect::Create(CPauseSelect::EXIT);

	// 選択中を決定
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
	// 終了処理
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

	// 選択処理
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

	// 選択されている項目に合わせて更新
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

	// ポーズを戻るように終了
	if (pInput->Trigger(KEY_PAUSE) || pInput->Trigger(KEY_BACK))
	{
		m_select = QUIT;
		m_isEndFlag = true;
	}

	// ポーズの選択項目を決定して終了
	if (pInput->Trigger(KEY_DECISION))
	{
		m_isEndFlag = true;
		//BGMの設定
		CApplication::GetSound()->Play(CSound::LABEL_SE_ENTER_KEY_02);
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
