#include "application.h"
#include "renderer.h"
#include "objectX.h"
#include "object3D.h"
#include "object2D.h"
#include "object.h"
#include "input.h"
#include "tutorial.h"
#include "fade.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "time.h"
#include "obstacle.h"
#include "load_stage.h"

CPlayer *CTutorial::m_pPlayer = nullptr;
CCamera *CTutorial::m_pCamera = nullptr;
CMeshfield *CTutorial::m_pMeshField = nullptr;
CLight *CTutorial::m_pLight = nullptr;
CTime *CTutorial::m_pTime = nullptr;
CObstacle *CTutorial::m_pObstacle = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	m_pObject2D[0] = CObject2D::Create("TUTORIAL", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f), PRIORITY_LEVEL3);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// インスタンスの解放処理
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	//これがないと上手く表示されない
	if (m_pObject2D != nullptr)
	{
		m_pObject2D[0]->Update();
		m_pObject2D[0]->Draw();
	}

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInputKeyboard->Trigger(DIK_RETURN))
		{
			// 遷移
			CFade::SetFade(CApplication::MODE_TITLE);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
CTutorial * CTutorial::Create()
{
	//ポインタ宣言
	CTutorial *pTutorial = nullptr;

	//インスタンス生成
	pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{//ポインタが存在したら実行
		pTutorial->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pTutorial;
}