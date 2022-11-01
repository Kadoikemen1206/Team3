#include "object2d.h"
#include "number.h"
#include "renderer.h"
#include "application.h"
#include <assert.h>

CNumber::CNumber() : CObject2D(CObject::PRIORITY_LEVEL4)
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

	//頂点カラーの設定
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//派生のテクスチャポインタを親のテクスチャポインタに代入する処理
	BindTexture("NUMBER");
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

void CNumber::Unload()
{
}
