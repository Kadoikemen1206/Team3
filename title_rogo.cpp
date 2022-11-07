//=============================================================================
//
// タイトルロゴ処理 [title_rogo.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "title_rogo.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CTitleRogo::m_apObject2D[14] = {};
bool CTitleRogo::m_bTitleMenuFlag = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleRogo::CTitleRogo(int nPriority) :
	m_bTitleRogoSwitch(false),
	m_nTime(0),
	m_nTextureMax(14),
	m_nSinCount(0),
	m_fRotZ(0.0f)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleRogo::~CTitleRogo()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleRogo::Init()
{
	//THERE IS RUN DOLL
	m_apObject2D[0] = CObject2D::Create("TITLE_D", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[1] = CObject2D::Create("TITLE_E_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[2] = CObject2D::Create("TITLE_E_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[3] = CObject2D::Create("TITLE_I", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[4] = CObject2D::Create("TITLE_L_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[5] = CObject2D::Create("TITLE_L_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[6] = CObject2D::Create("TITLE_N", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[7] = CObject2D::Create("TITLE_H", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[8] = CObject2D::Create("TITLE_O", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[9] = CObject2D::Create("TITLE_R_01", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[10] = CObject2D::Create("TITLE_R_02", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[11] = CObject2D::Create("TITLE_S", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[12] = CObject2D::Create("TITLE_U", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	m_apObject2D[13] = CObject2D::Create("TITLE_T", D3DXVECTOR3((float)SCREEN_WIDTH_HALF, -(float)SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1280.0f, 720.0f, 0.0f), CObject::PRIORITY_LEVEL3);

	for (int i = 0; i < m_nMaxTex; i++)
	{
		m_nDelay[i] = rand() % 35;
		m_fSpeed[i] = (rand() % 7 + 50) * 0.1f;
	}

	// フラグの初期化
	m_bTitleMenuFlag = false;

	// オブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitleRogo::Uninit()
{
	// オブジェクトの終了処理
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitleRogo::Update()
{
	m_nTime++;

	// 座標取得
	D3DXVECTOR3 pos[14];
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		pos[nCnt] = m_apObject2D[nCnt]->GetPos();
	}

	// 角度取得
	D3DXVECTOR3 rot[14];
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		rot[nCnt] = m_apObject2D[nCnt]->GetRot();
	}

	//タイトルロゴの縦の動き
	if (m_bTitleRogoSwitch == false)
	{
		for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
		{
			if (pos[nCnt].y < 360.0f)
			{
				if (m_nDelay[nCnt] >= m_nTime)
				{
					continue;
				}

				m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(0.0f, m_fSpeed[nCnt], 0.0f));
			}
			else
			{
				m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_bTitleRogoSwitch = true;
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
		{
			if (pos[nCnt].y >= 180.0f)
			{
				m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
			}
			else
			{
				m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_bTitleMenuFlag = true;
			}
		}
	}

	// Sin波で角度をずらす
	if (m_bTitleRogoSwitch)
	{
		m_nSinCount++;
		m_fRotZ = (((sinf(m_nSinCount * 0.03f) * 0.5f) * 0.5f) * 0.5f);
	}

	// 角度の設定
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		rot[nCnt] = D3DXVECTOR3(0.0f, 0.0f, m_fRotZ);
		m_apObject2D[nCnt]->SetRot(rot[nCnt]);
	}

	// オブジェクトの更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitleRogo::Draw()
{
	// オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CTitleRogo * CTitleRogo::Create(void)
{
	//ポインタ宣言
	CTitleRogo *pTitleRogo = nullptr;

	//インスタンス生成
	pTitleRogo = new CTitleRogo;

	if (pTitleRogo != nullptr)
	{//ポインタが存在したら実行
		pTitleRogo->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pTitleRogo;
}
