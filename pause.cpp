#include "pause.h"
#include "object2D.h"
#include "input.h"
#include "application.h"
#include "pause_quit.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause():
	CObject(PRIORITY_LEVEL0)
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
	m_quit = CPauseQuit::Create();
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPause::Uninit(void)
{
	m_pBg->Uninit();
	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CPause::Update(void)
{
	CInput* pInput = CApplication::GetInput();

	if (pInput->Trigger(DIK_P))
	{
		Uninit();
		return;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPause::Draw(void)
{
}

void CPause::BeginUpdate()
{
}

void CPause::SelectUpdate()
{
}

void CPause::EndUpdate()
{
}
