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
#include "sound.h"
#include "load_stage.h"
#include "number.h"
#include "time.h"

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

	//BGMの設定
	CApplication::GetSound()->Play(CSound::LABEL_BGM_RESULT);

	// ライトの生成
	m_pLight = CLight::Create();

	// メッシュフィールドの生成
	CMeshfield::Create(D3DXVECTOR3(-1500.0f, -210.0f, 14000.0f), CObject::PRIORITY_LEVEL2);

	// ステージのロード
	CLoadStage::LoadAll();

	// ランキングロゴの生成
	CRankingRogo::Create();

	//ファイル読み込み処理
	Load();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	// カメラの設定
	CApplication::GetCamera()->SetCameraType(CCamera::CAMERATYPE_NONE);

	//BGMを止める設定
	CApplication::GetSound()->Stop();

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
		//ファイル書き出し処理
		Save();

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
	pFile = fopen("Data\\RANKING\\ranking.txt", "r");

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
	pFile = fopen("Data\\RANKING\\ranking.txt", "w");

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
	if (m_nRanking > aData[MAX_RANKINGRANK - 1])
	{
		aData[MAX_RANKINGRANK - 1] = m_nRanking;
	}

	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (aData[nCount] > aData[nCount2])
			{
				int nMin = aData[nCount];
				aData[nCount] = aData[nCount2];
				aData[nCount2] = nMin;
			}
		}
	}

	CTime::Create(CTime::TYPE_RANKING, D3DXVECTOR3(SCREEN_WIDTH_HALF - 190.0f, 200.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), aData[0], CObject::PRIORITY_LEVEL4);

	CTime::Create(CTime::TYPE_RANKING, D3DXVECTOR3(SCREEN_WIDTH_HALF - 190.0f, 310.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), aData[1], CObject::PRIORITY_LEVEL4);

	CTime::Create(CTime::TYPE_RANKING, D3DXVECTOR3(SCREEN_WIDTH_HALF - 190.0f, 420.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), aData[2], CObject::PRIORITY_LEVEL4);

	CTime::Create(CTime::TYPE_RANKING, D3DXVECTOR3(SCREEN_WIDTH_HALF - 190.0f, 530.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), aData[3], CObject::PRIORITY_LEVEL4);

	CTime::Create(CTime::TYPE_RANKING, D3DXVECTOR3(SCREEN_WIDTH_HALF - 190.0f, 640.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), aData[4], CObject::PRIORITY_LEVEL4);
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
