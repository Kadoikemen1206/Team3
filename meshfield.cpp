//=============================================================================
//
// メッシュフィールド処理 [meshfield.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "meshfield.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshfield::CMeshfield(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_fRotMove(5.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_MESH);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshfield::~CMeshfield()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshfield::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	BindTexture("FLOOR0");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点座標へのポインタ
	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//m_RandHeight = (float)(rand() % 40 + 1);
			m_RandHeight = sinf(nCntX * 0.5f) * 30;

			//頂点座標の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-POLYGON_WIDTH + (POLYGON_WIDTH * nCntX), 0.0f, POLYGON_DEPTH - (POLYGON_DEPTH * nCntZ));

			//各頂点の法線の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);

			pIdx += 2;
		}

		//縮退ポリゴン
		if (nCntZ != MESHFIELD_Z_BLOCK)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) * nCntZ + MESHFIELD_X_BLOCK;
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) * (nCntZ + 2);

			pIdx += 2;
		}
	}

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	D3DXVECTOR3 IdxPosNor[3];				//Idxのpos
	D3DXVECTOR3 Calculation3DNor[2];		//3次元外積の計算結果
	D3DXVECTOR3 VecAnswer;					//外積の計算結果
	D3DXVECTOR3 SaveVtxNor[MESHFIELD_VERTEX_NUM];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM - 2; nCnt++)
	{
		//Idxのpos
		IdxPosNor[0] = pVtx[pIdx[nCnt]].pos;
		IdxPosNor[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPosNor[2] = pVtx[pIdx[nCnt + 2]].pos;

		//縮退ポリゴンの場合実行
		if (pIdx[nCnt] == pIdx[nCnt + 1] || pIdx[nCnt + 1] == pIdx[nCnt + 2] || pIdx[nCnt + 2] == pIdx[nCnt])
		{
			continue;
		}

		//3次元外積の計算
		Calculation3DNor[0] = IdxPosNor[1] - IdxPosNor[0];
		Calculation3DNor[1] = IdxPosNor[2] - IdxPosNor[0];
		D3DXVec3Cross(&VecAnswer, &Calculation3DNor[1], &Calculation3DNor[0]);

		if (nCnt % 2 == 0)
		{
			VecAnswer *= -1;
		}

		//正規化
		D3DXVec3Normalize(&VecAnswer, &VecAnswer);

		//保存用配列に法線ベクトルを保存
		SaveVtxNor[pIdx[nCnt]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 1]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 2]] += VecAnswer;

		//正規化
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt]], &SaveVtxNor[pIdx[nCnt]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 1]], &SaveVtxNor[pIdx[nCnt + 1]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 2]], &SaveVtxNor[pIdx[nCnt + 2]]);

		pVtx[pIdx[nCnt]].nor = SaveVtxNor[pIdx[nCnt]];
		pVtx[pIdx[nCnt + 1]].nor = SaveVtxNor[pIdx[nCnt + 1]];
		pVtx[pIdx[nCnt + 2]].nor = SaveVtxNor[pIdx[nCnt + 2]];
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshfield::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの解放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//インスタンスの解放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshfield::Update()
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshfield::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITIVE_NUM);

	//テクスチャの設定	(テクスチャがモデルにかぶらないようにする)
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CMeshfield::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_3D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);

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
// 座標設定処理
//=============================================================================
void CMeshfield::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズ設定処理
//=============================================================================
void CMeshfield::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動量設定処理
//=============================================================================
void CMeshfield::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// カラー設定処理
//=============================================================================
void CMeshfield::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定処理
//=============================================================================
void CMeshfield::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CMeshfield::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

//=============================================================================
// テクスチャ座標設定処理
//=============================================================================
void CMeshfield::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

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
CMeshfield * CMeshfield::Create(const D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CMeshfield *pMeshfield = nullptr;

	//インスタンス生成
	pMeshfield = new CMeshfield(nPriority);

	if (pMeshfield != nullptr)
	{//ポインタが存在したら実行
		pMeshfield->SetPos(pos);
		pMeshfield->SetSize(D3DXVECTOR3(100.0f, 50.0f, 100.0f));
		pMeshfield->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pMeshfield->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pMeshfield;
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMeshfield::Collision(D3DXVECTOR3 *PlayerPos)
{
	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;

	//インデックス情報へのポインタ
	WORD * pIdx = nullptr;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM; nCnt++)
	{
		//Idxのpos
		m_IdxPos[0] = pVtx[pIdx[nCnt]].pos;
		m_IdxPos[1] = pVtx[pIdx[nCnt + 1]].pos;
		m_IdxPos[2] = pVtx[pIdx[nCnt + 2]].pos;

		//VecA
		m_VecA[0] = m_IdxPos[1] - m_IdxPos[0];
		m_VecA[1] = m_IdxPos[2] - m_IdxPos[1];
		m_VecA[2] = m_IdxPos[0] - m_IdxPos[2];

		//VecB
		m_VecB[0] = *PlayerPos - (m_IdxPos[0] + m_pos);
		m_VecB[1] = *PlayerPos - (m_IdxPos[1] + m_pos);
		m_VecB[2] = *PlayerPos - (m_IdxPos[2] + m_pos);

		//2次元外積の計算結果
		m_Calculation2D[0] = m_VecA[0].x * m_VecB[0].z - m_VecB[0].x * m_VecA[0].z;
		m_Calculation2D[1] = m_VecA[1].x * m_VecB[1].z - m_VecB[1].x * m_VecA[1].z;
		m_Calculation2D[2] = m_VecA[2].x * m_VecB[2].z - m_VecB[2].x * m_VecA[2].z;

		//プレイヤーの位置が全部-か+
		if ((m_Calculation2D[0] >= 0 && m_Calculation2D[1] >= 0 && m_Calculation2D[2] >= 0) || (m_Calculation2D[0] <= 0 && m_Calculation2D[1] <= 0 && m_Calculation2D[2] <= 0))
		{
			//3次元外積の計算
			m_Calculation3D[0] = m_IdxPos[1] - m_IdxPos[0];
			m_Calculation3D[1] = m_IdxPos[2] - m_IdxPos[0];
			D3DXVec3Cross(&m_Answer, &m_Calculation3D[0], &m_Calculation3D[1]);

			//正規化
			D3DXVec3Normalize(&m_Answer, &m_Answer);

			//内積の計算
			PlayerPos->y = (m_IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (m_IdxPos[0].x + m_pos.x)) * m_Answer.x + (PlayerPos->z - (m_IdxPos[0].z + m_pos.z)) * m_Answer.z) / m_Answer.y;

			//内積の計算結果保存
			m_AnswerKeep = (m_IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (m_IdxPos[0].x + m_pos.x)) * m_Answer.x + (PlayerPos->z - (m_IdxPos[0].z + m_pos.z)) * m_Answer.z) / m_Answer.y;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	//頂点バッファをアンロック
	m_pIdxBuff->Unlock();
}
