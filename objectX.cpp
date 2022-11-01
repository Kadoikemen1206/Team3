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
	//// 移動量加算
	//m_pos += m_move;
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObjectX::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
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
// 当たり判定
//=============================================================================
void CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	//モデルの左側当たり判定
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f) && 
		(pPos->y + pSize->y / 2.0f > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y - pSize->y / 2.0f < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
	}
	//モデルの右側当たり判定
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->y + pSize->y / 2.0f > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y - pSize->y / 2.0f < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
	}
	//モデルの奥側当たり判定
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->y + pSize->y / 2.0f > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y - pSize->y / 2.0f < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
	}
	//モデルの手前側当たり判定
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->y + pSize->y / 2.0f > m_pos.y - m_MaxVtx.y / 2.0f) && 
		(pPos->y - pSize->y / 2.0f < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
	}
}

//void CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 PosOld)
//{
//	// ターゲットの位置を取得
//	D3DXVECTOR3 TargetPos = *pPos;
//
//	//頂点座標
//	D3DXVECTOR3 vtx[4] =
//	{
//		D3DXVECTOR3(m_pos.x + m_MinVtx.x,0.0f,m_pos.z + m_MaxVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MaxVtx.x,0.0f,m_pos.z + m_MaxVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MaxVtx.x,0.0f,m_pos.z + m_MinVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MinVtx.x,0.0f,m_pos.z + m_MinVtx.z)
//	};
//
//	//ベクトル
//	D3DXVECTOR3 Vec [4] =
//	{
//		vtx[1] - vtx[0],
//		vtx[2] - vtx[1],
//		vtx[3] - vtx[2],
//		vtx[0] - vtx[3]
//	};
//
//	//ターゲットまでのベクトル
//	D3DXVECTOR3 VecPos[4] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
//
//	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//	{
//		VecPos[nCntVtx] = TargetPos - vtx[nCntVtx];
//	}
//
//	// 外積
//	float fCalculation[4] = { 0.0f };
//	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//	{
//		fCalculation[nCntVtx] = Vec[nCntVtx].x * VecPos[nCntVtx].z - VecPos[nCntVtx].x * Vec[nCntVtx].z;
//	}
//
//	//プレイヤーの位置が全部-か+
//	if (fCalculation[0] < 0.0f
//		&& fCalculation[1] < 0.0f
//		&& fCalculation[2] < 0.0f
//		&& fCalculation[3] < 0.0f)
//	{
//		// 目的の頂点
//		D3DXVECTOR3 TargetVtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		// 目的のベクトル
//		D3DXVECTOR3 TargetVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//ターゲットの過去位置までのベクトル
//		D3DXVECTOR3 VecPosOld[4] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			VecPosOld[nCntVtx] = PosOld - vtx[nCntVtx];
//		}
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			fCalculation[nCntVtx] = Vec[nCntVtx].x * VecPosOld[nCntVtx].z - VecPosOld[nCntVtx].x * Vec[nCntVtx].z;
//		}
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			if (fCalculation[nCntVtx] > 0.0f)
//			{
//				TargetVec = Vec[nCntVtx];
//				TargetVtx = vtx[nCntVtx];
//			}
//		}
//
//		// 移動ベクトル
//		D3DXVECTOR3 moveVec = TargetPos - PosOld;
//		D3DXVECTOR3 TargetVtxVec = TargetVtx - PosOld;
//		D3DXVECTOR3 TargetVecNor = TargetVec;
//		D3DXVec3Normalize(&TargetVecNor, &TargetVecNor);
//		float fLength = (moveVec.x * TargetVtxVec.z - TargetVtxVec.x * moveVec.z) / (TargetVecNor.x * moveVec.z - moveVec.x * TargetVecNor.z);
//
//		D3DXVECTOR3 pos = TargetVtx + (TargetVec * fLength);
//
//		*pPos = PosOld;
//	}
//}

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
