#include "pause_select.h"
#include "object2D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPauseSelect::CPauseSelect() :
	CObject(PRIORITY_LEVEL5)
{
	SetType(OBJTYPE_PAUSE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseSelect::~CPauseSelect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPauseSelect * CPauseSelect::Create(ESelect inSelect)
{
	CPauseSelect *pLogo = new CPauseSelect();

	auto TextCreate = [](const char* inTag, float inPosX)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(inPosX, (float)-SCREEN_HEIGHT_HALF, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(400.0f * 0.25f, 850.0f * 0.5f, 0.0f);
		CObject2D* object = CObject2D::Create(inTag, pos, size, CObject::PRIORITY_LEVEL5);
		object->SetCanPoseUpdate();
		return object;
	};

	if (pLogo != nullptr)
	{
		pLogo->Init();
		switch (inSelect)
		{
		case CPauseSelect::QUIT:
		{

			pLogo->m_pText.resize(4);
			pLogo->m_pText[0] = TextCreate("QUIT_Q", (float)SCREEN_WIDTH_HALF - 100.0f - 400.0f);
			pLogo->m_pText[1] = TextCreate("QUIT_I", (float)SCREEN_WIDTH_HALF - 100.0f - 300.0f);
			pLogo->m_pText[2] = TextCreate("QUIT_U", (float)SCREEN_WIDTH_HALF - 100.0f - 200.0f);
			pLogo->m_pText[3] = TextCreate("QUIT_T", (float)SCREEN_WIDTH_HALF - 100.0f - 100.0f);
		}
			break;
		case CPauseSelect::RETRY:
		{
			pLogo->m_pText.resize(5);
			pLogo->m_pText[0] = TextCreate("RETRY_R1", (float)SCREEN_WIDTH_HALF);
			pLogo->m_pText[1] = TextCreate("RETRY_E", (float)SCREEN_WIDTH_HALF);
			pLogo->m_pText[2] = TextCreate("RETRY_T", (float)SCREEN_WIDTH_HALF);
			pLogo->m_pText[3] = TextCreate("RETRY_R2", (float)SCREEN_WIDTH_HALF);
			pLogo->m_pText[4] = TextCreate("RETRY_Y", (float)SCREEN_WIDTH_HALF);
		}
		break;
		case CPauseSelect::EXIT:
		{
			pLogo->m_pText.resize(4);
			pLogo->m_pText[0] = TextCreate("EXIT_E",(float)SCREEN_WIDTH_HALF + 200.0f);
			pLogo->m_pText[1] = TextCreate("EXIT_X",(float)SCREEN_WIDTH_HALF + 200.0f);
			pLogo->m_pText[2] = TextCreate("EXIT_I",(float)SCREEN_WIDTH_HALF + 200.0f);
			pLogo->m_pText[3] = TextCreate("EXIT_T",(float)SCREEN_WIDTH_HALF + 200.0f);
		}
		break;
		default:
			break;
		}
	}
	else
	{
		assert(false);
	}

	return pLogo;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPauseSelect::Init()
{

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPauseSelect::Uninit()
{
	for (int i = 0; i < (int)m_pText.size(); i++)
	{
		m_pText[i]->Uninit();
	}
	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CPauseSelect::Update()
{
}

//=============================================================================
// 描画
//=============================================================================
void CPauseSelect::Draw()
{
}

//=============================================================================
// 登場更新
//=============================================================================
void CPauseSelect::BeginUpdate()
{
	for (int i = 0; i < (int)m_pText.size(); i++)
	{
		m_pText[i]->SetPos(m_pText[i]->GetPos() + D3DXVECTOR3(0.0f, 22.0f,0.0f));
	}
}

//=============================================================================
// 選択中更新
//=============================================================================
void CPauseSelect::SelectNowUpdate()
{
	static float time = 0.0f;
	for (int i = 0; i < (int)m_pText.size(); i++)
	{
		time += 0.05f;
		//D3DXVECTOR3 size = D3DXVECTOR3(400.0f * 0.5f, 850.0f * 0.5f, 0.0f);
		m_pText[i]->SetSize(D3DXVECTOR3(400.0f * 0.5f + sinf(time) * 40.0f, 850.0f * 0.5f + sinf(time) * 40.0f, 0.0f));
	}
}

//=============================================================================
// 選択してない更新
//=============================================================================
void CPauseSelect::SelectNoUpdate()
{
}

void CPauseSelect::EndNowUpdate()
{
	static float time = 0.0f;
	for (int i = 0; i < (int)m_pText.size(); i++)
	{
		time += 0.05f;
		m_pText[i]->SetSize(D3DXVECTOR3(400.0f * 0.5f + sinf(time) * 50.0f, 850.0f * 0.5f + sinf(time) * 50.0f, 0.0f));
	}
}

void CPauseSelect::EndNoUpdate()
{
	for (int i = 0; i < (int)m_pText.size(); i++)
	{
		m_pText[i]->SetPos(m_pText[i]->GetPos() - D3DXVECTOR3(0.0f, 22.0f, 0.0f));
	}
}
