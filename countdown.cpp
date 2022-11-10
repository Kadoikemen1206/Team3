//=============================================================================
//
// カウントダウン処理 [countdown.cpp]
// Author : KADO TAKUMA
//
//=============================================================================
#include "countdown.h"
#include "application.h"
#include "sound.h"
#include "renderer.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CCountDown::m_pTexture[4] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CCountDown::CCountDown(int nPriority) :
	CObject2D(nPriority)
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_COUNTDOWN);
}

//=============================================================================
// デストラクタ
//=============================================================================
CCountDown::~CCountDown()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCountDown::Init(void)
{
	//オブジェクトの初期化処理
	CObject2D::Init();

	//頂点カラーの設定
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//頂点サイズの設定
	CObject2D::SetSize(D3DXVECTOR3(COUNTDOWN_WIDTH, COUNTDOWN_HEIGHT, 0.0f));

	//BGMの設定
	CApplication::GetSound()->Play(CSound::LABEL_SE_COUNTDOWN);

	//派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	BindTexture("COUNTDOWN_3");

	m_pObject[0] = CObject2D::Create("COUNTFRAME", D3DXVECTOR3(640.0f,360.0f,0.0f), GetSize() * 1.1f, CObject::PRIORITY_LEVEL3);
	m_pObject[1] = CObject2D::Create("COUNT_LOCUS", D3DXVECTOR3(640.0f, 360.0f, 0.0f), GetSize(), CObject::PRIORITY_LEVEL3);
	m_pObject[1]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,0.7f));
	m_pObject[1]->SetRotate(true, 450);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCountDown::Uninit(void)
{
	//オブジェクトの終了処理
	CObject2D::Uninit();

	//BGMを止める設定
	CApplication::GetSound()->Stop(CSound::LABEL_SE_COUNTDOWN);
}

//=============================================================================
// 更新処理
//=============================================================================
void CCountDown::Update(void)
{
	auto col = CObject2D::GetCol();
	auto scale = CObject2D::GetSize();

	//カウンター加算
	m_nCounter++;

	if (m_nCounter >= 220)
	{
		col.a -= 0.05f;
		scale.x += 25.0f;
		scale.y += 25.0f;
	}

	//カウントダウンに合わせて画像変更
	if (m_nCounter == 60)
	{
		//派生のテクスチャポインタを親のテクスチャポインタに代入する処理
		BindTexture("COUNTDOWN_2");
	}
	else if (m_nCounter == 120)
	{
		//派生のテクスチャポインタを親のテクスチャポインタに代入する処理
		BindTexture("COUNTDOWN_1");
	}
	else if (m_nCounter == 180)
	{
		//派生のテクスチャポインタを親のテクスチャポインタに代入する処理
		BindTexture("COUNTDOWN_START");
	}
	else if (m_nCounter == 240)
	{
		//終了処理
		for (int i = 0; i < 2; i++)
		{
			if (m_pObject[i] == nullptr)
			{
				continue;
			}
			m_pObject[i]->Uninit();
		}

		Uninit();
		return;
	}

	//オブジェクトの更新処理
	CObject2D::Update();
	CObject2D::SetCol(col);
	CObject2D::SetSize(scale);
}

//=============================================================================
// 描画処理
//=============================================================================
void CCountDown::Draw(void)
{
	//オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CCountDown * CCountDown::Create(D3DXVECTOR3 pos)
{
	//ポインタ宣言
	CCountDown *pCountDown;

	//インスタンス生成
	pCountDown = new CCountDown;

	if (pCountDown != nullptr)
	{//ポインタが存在したら実行
		pCountDown->Init();
		pCountDown->SetPos(pos);
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	return pCountDown;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CCountDown::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み*
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/CountDown_3.png",
		&m_pTexture[COUNTDOWN_3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/CountDown_2.png",
		&m_pTexture[COUNTDOWN_2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/CountDown_1.png",
		&m_pTexture[COUNTDOWN_1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/CountDown_0.png",
		&m_pTexture[COUNTDOWN_START]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CCountDown::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < COUNTDOWN_TEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
