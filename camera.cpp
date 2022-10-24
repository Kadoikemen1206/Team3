//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	//視点・注視点・上方向を設定する（構造体の初期化）
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);							//視点
	m_posR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);								//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//上方向ベクトル ←固定でOK!!
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向き
	float fLength1 = (m_posV.x - m_posR.x);									//視点から注視点のX軸の距離
	float fLength2 = (m_posV.z - m_posR.z);									//視点から注視点のZ軸の距離
	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//視点から注視点までの距離

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	//キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();

	//カメラの移動
	if (pInputKeyboard->GetPress(DIK_DOWN))
	{//上に移動
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEED;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_UP))
	{//下に移動
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEED;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_RIGHT))
	{//左に移動
		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	if (pInputKeyboard->GetPress(DIK_LEFT))
	{//右に移動
		m_posV.x -= sinf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posV.z -= cosf(D3DX_PI * 0.5f + m_rot.y) * CAMERA_SPEED;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//注視点の旋回
	if (pInputKeyboard->GetPress(DIK_C))
	{//左に旋回
		m_rot.y += 0.05f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_Z))
	{//右に旋回
		m_rot.y -= 0.05f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//視点の旋回
	if (pInputKeyboard->GetPress(DIK_E))
	{//左に旋回
		m_rot.y += 0.05f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_Q))
	{//右に旋回
		m_rot.y -= 0.05f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//アスペクト比
		10.0f,											//ニア（どこからどこまでカメラで表示するか設定）
		3000.0f);										//ファー

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// 生成処理
//=============================================================================
CCamera * CCamera::Create(void)
{
	//ポインタ宣言
	CCamera *pCamera = nullptr;

	//インスタンス生成
	pCamera = new CCamera;

	if (pCamera != nullptr)
	{//ポインタが存在したら実行
		pCamera->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pCamera;
}
