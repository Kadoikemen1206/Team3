//=============================================================================
//
// 2Dオブジェクト処理 [object2d.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CObject2D::CObject2D(int nPriority) : 
	CObject(nPriority),
	m_pTexture(nullptr), 
	m_pVtxBuff(nullptr), 
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2D::~CObject2D()
{
	////バッファが消去されてたら普通に通る(NULLチェック)
	//assert(m_pVtxBuff == nullptr);
}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CObject2D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer((sizeof(VERTEX_2D) * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さ算出
	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y)));

	//角度の算出
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// オブジェクトの終了
//=============================================================================
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インスタンスの解放処理
	Release();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObject2D::Update()
{
	//位置更新
	m_pos += m_move;

	//頂点座標更新処理
	VtxUpdate();
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObject2D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CObject2D::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//対角線の長さ算出
		m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;

		//角度の算出
		m_fAngle = atan2f(m_size.x, m_size.y);

		//頂点座標の更新
		pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		//頂点カラーの更新
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//テクスチャのポインタ
}

//=============================================================================
// テクスチャ座標更新処理
//=============================================================================
void CObject2D::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(x_1, y_1);
	pVtx[1].tex = D3DXVECTOR2(x_2, y_1);
	pVtx[2].tex = D3DXVECTOR2(x_1, y_2);
	pVtx[3].tex = D3DXVECTOR2(x_2, y_2);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 生成処理
//=============================================================================
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObject2D *pObject2D = nullptr;

	//インスタンス生成
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{//ポインタが存在したら実行
		pObject2D->SetPos(pos);
		pObject2D->SetSize(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
		pObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject2D->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObject2D;
}
