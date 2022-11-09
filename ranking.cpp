//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdio.h>
#include "application.h"
#include "fade.h"
#include "input.h"
#include "ranking.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "ranking_rogo.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "load_stage.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CNumber *CRanking::m_apNumber[MAX_RANKINGRANK][MAX_RANKING] = {};
int CRanking::aData[MAX_RANKINGRANK] = {};
int CRanking::m_nRanking = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_TITLE);
	CApplication::GetCamera()->Init();

	// ライトの生成
	m_pLight = CLight::Create();

	// メッシュフィールドの生成
	CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ステージのロード
	CLoadStage::LoadAll();

	// ランキングロゴの生成
	CRankingRogo::Create();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
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

	//インスタンスの解放処理
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	// カメラの情報取得
	CCamera *pCamera = CApplication::GetCamera();

	// カメラの視点と注視点取得
	D3DXVECTOR3 posV = pCamera->GetPosV();
	D3DXVECTOR3 posR = pCamera->GetPosR();

	// 視点と注視点を後ろにずらしていく処理
	posV += D3DXVECTOR3(0.0f, 0.0f, 2.0f);
	posR += D3DXVECTOR3(0.0f, 0.0f, 2.0f);

	// 視点と注視点を設定
	pCamera->SetPosV(posV);
	pCamera->SetPosR(posR);

	// キーボードの情報取得
	CInput *pInput = CApplication::GetInput();

	if (pInput->Trigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		CFade::SetFade(CApplication::MODE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// ファイル読み込み処理
//=============================================================================
void CRanking::Load(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("Data\\FILE\\ranking.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCntData = 0; nCntData < MAX_RANKINGRANK; nCntData++)
		{
			//ファイルに数値を書き出す
			fscanf(pFile, "%d\n", &aData[nCntData]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//=============================================================================
// ファイル書き出し処理
//=============================================================================
void CRanking::Save(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("Data\\FILE\\ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
		{
			//ファイルに数値を書き出す
			fprintf(pFile, "%d\n", aData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//=============================================================================
// スコアの設定処理
//=============================================================================
void CRanking::SetRankingScore()
{
	int aPosTexU[MAX_RANKINGRANK][MAX_RANKING];

	if (m_nRanking > aData[MAX_RANKINGRANK - 1])
	{
		aData[MAX_RANKINGRANK - 1] = m_nRanking;
	}

	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (aData[nCount] < aData[nCount2])
			{
				int nMin = aData[nCount];
				aData[nCount] = aData[nCount2];
				aData[nCount2] = nMin;
			}
		}
	}

	for (int nCntScore = 0; nCntScore < MAX_RANKINGRANK; nCntScore++)
	{
		aPosTexU[nCntScore][0] = aData[nCntScore] % 100000 / 10000;
		aPosTexU[nCntScore][1] = aData[nCntScore] % 10000 / 1000;
		aPosTexU[nCntScore][2] = aData[nCntScore] % 1000 / 100;
		aPosTexU[nCntScore][3] = aData[nCntScore] % 100 / 10;
		aPosTexU[nCntScore][4] = aData[nCntScore] % 10 / 1;
	}

	////テクスチャ座標の設定
	//for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	//{
	//	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
	//	{
	//		float fShiftWidth = 1.0f / 10;
	//		m_apNumber[nCnt][nCntScore]->SetUV((float)aPosTexU[nCnt][nCntScore] * fShiftWidth, (fShiftWidth + (float)aPosTexU[nCnt][nCntScore] * fShiftWidth), 0.0f, 1.0f);
	//	}
	//}
}

//=============================================================================
// 情報の取得
//=============================================================================
void CRanking::GetRanking(int Ranking)
{
	m_nRanking = Ranking;
}

//=============================================================================
// 生成処理
//=============================================================================
CRanking * CRanking::Create()
{
	CRanking *pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}

	return pRanking;
}
