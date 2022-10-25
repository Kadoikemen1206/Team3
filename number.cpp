#include "object2d.h"
#include "number.h"
#include "renderer.h"
#include "application.h"
#include <assert.h>

LPDIRECT3DTEXTURE9 CNumber::m_pTexture = nullptr;

CNumber::CNumber()
{

}

CNumber::~CNumber()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CNumber::Init()
{
	CObject2D::Init();

	////テクスチャの読み込み
	//LoadTexture("Data\\TEXTURE\\number000.png");

	//頂点カラーの設定
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//派生のテクスチャポインタを親のテクスチャポインタに代入する処理

	BindTexture(m_pTexture);

	////テクスチャ座標初期化
	//float fShiftWidth = 1.0f / 10;
	//CObject2D::SetUV((m_nPattrenAnim * fShiftWidth), (fShiftWidth + (m_nPattrenAnim * fShiftWidth)), 0.0f, 1.0f);

	return S_OK;
}

void CNumber::Draw()
{
	//オブジェクトの描画処理
	CObject2D::Draw();
}

//=============================================================================
//爆発処理の生成
//=============================================================================
CNumber *CNumber::Create(const D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber = nullptr;

	pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->Init();
		pNumber->SetSize(size);
		pNumber->SetPos(pos);
	}
	else
	{
		assert(false);
	}
	return pNumber;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CNumber::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み*
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\number000.png",
		&m_pTexture);

	return S_OK;
}

void CNumber::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
