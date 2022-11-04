//=============================================================================
//
// オブジェクトX処理 [objectX.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "objectX_group.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CObjectX::CObjectX(int nPriority) :
	CObject(nPriority),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_MODEL);
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CObjectX::Init()
{
	//モデルの読み込み
	LoadModel("BOX");

	return S_OK;
}

//=============================================================================
// オブジェクトの終了
//=============================================================================
void CObjectX::Uninit()
{
	//インスタンスの解放処理
	Release();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObjectX::Update()
{

}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObjectX::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL *pMat;					//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);	//(※行列移動関数(第1引数にx,y,z方向の移動行列を作成))
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();

		// 行列掛け算関数
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	//Projection();

	//ワールドマトリックスの設定（ワールド座標行列の設定）
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// 行列掛け算関数

	// 行列掛け算関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::GetTexture();

	// マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	if (m_pBuffMat != nullptr)
	{// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetTexture("NULL"));

			// モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);

			// テクスチャの設定
			pDevice->SetTexture(0, nullptr);
		}
	}

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 頂点最大小値の計算処理
//=============================================================================
void CObjectX::CalculationVtx()
{
	m_MinVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	m_MaxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

		D3DXMatrixIdentity(&mtxWorld);

		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// 行列掛け算関数

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);		// 行列移動関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);		// 行列掛け算関数

		vtx = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &m_mtxWorld);

		//X
		if (vtx.x < m_MinVtx.x)
		{//最小値
			m_MinVtx.x = vtx.x;
		}
		if (vtx.x > m_MaxVtx.x)
		{//最大値
			m_MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < m_MinVtx.y)
		{//最小値
			m_MinVtx.y = vtx.y;
		}
		if (vtx.y > m_MaxVtx.y)
		{//最大値
			m_MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < m_MinVtx.z)
		{//最小値
			m_MinVtx.z = vtx.z;
		}
		if (vtx.z > m_MaxVtx.z)
		{//最大値
			m_MaxVtx.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタ進める
		pVtxBuff += sizeFVF;
	}
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 生成処理
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObjectX *pObjectX = nullptr;

	//インスタンス生成
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//ポインタが存在したら実行
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObjectX;
}

//=============================================================================
// モデルの読み込み
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{
	CObjectXGroup *xGroup = CApplication::GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtx = xGroup->GetMaxVtx(aFileName);
	m_pMesh = xGroup->GetMesh(aFileName);
	m_MinVtx = xGroup->GetMinVtx(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
}

//=============================================================================
// 平行投影処理
//=============================================================================
void CObjectX::Projection(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL *pMat;					//マテリアルデータへのポインタ

	//変数宣言
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(1.0f, -0.5f, 0.5f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow,&vecLight, &planeField);

	//ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//ワールドマトリックスの設定（ワールド座標行列の設定）
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		Material = pMat[nCntMat].MatD3D;

		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetMaterial(&Material);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの左側当たり判定
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f) && 
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
	}
	// モデルの右側当たり判定
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
	}
	// モデルの奥側当たり判定
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
	}
	// モデルの手前側当たり判定
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
	}

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 当たり判定 (上側)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの上側当たり判定
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPos->y <= m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->y = m_pos.y + m_MaxVtx.y;
		if (pPos->y == pPosOld->y)
		{
			pMove->y = 0.0f;
		}
	}

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 頂点最大値設定処理
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// 頂点最小値設定処理
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
