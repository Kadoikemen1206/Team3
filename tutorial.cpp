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

CTutorial::CTutorial()
{

}

CTutorial::~CTutorial()
{

}

HRESULT CTutorial::Init(void)
{
	// ライトの生成
	m_pLight = CLight::Create();

	//// タイマーの生成
	//m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 0.0f), 0,CObject::PRIORITY_LEVEL4);

	// メッシュフィールドの生成
	m_pMeshField = CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ギミックの生成(連打ギミック)
	//CBarrageMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// ギミックの生成(交互連打ギミック)
	//CAlternateMoveWall::Create(D3DXVECTOR3(-700.0f, 0.0f, 2000.0f));
	// ギミックの生成(押すギミック)
	//CPushMoveWall::Create(D3DXVECTOR3(-700.0f,0.0f,2000.0f));

	//プレイヤーの生成
	//m_pPlayer1P = CPlayer::Create(CPlayer::EPLAYER_1P, D3DXVECTOR3(-700.0f, 0.0f, 0.0f), CObject::PRIORITY_LEVEL3);
	//CLoadStage::LoadAll(m_pPlayer1P->GetPos());
	//CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_ONE);

	// カメラの設定
	CApplication::GetCamera()->Init();

	return S_OK;
}

void CTutorial::Uninit(void)
{
	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);

	// ライトの解放・削除
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// インスタンスの解放処理
	CObject::Release();
}

void CTutorial::Update(void)
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInputKeyboard->Trigger(DIK_RETURN))
		{
			// 遷移
			CFade::SetFade(CApplication::MODE_TITLE);
		}
	}
}

void CTutorial::Draw(void)
{

}

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