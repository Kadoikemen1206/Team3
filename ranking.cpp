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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.png",
		&m_pTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_logo.png",
		&m_pTexture[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&m_pTexture[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture[3]);

	//ファイル読み込み処理
	Load();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//インスタンスの解放処理
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	//入力処理用のポインタ宣言
	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{// ENTERキーが押されたら実行
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
	pFile = fopen("Data\\SAVE\\ranking.txt", "r");

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
	pFile = fopen("data\\ranking.txt", "w");

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
