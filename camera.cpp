//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CCamera::CAMERATYPE CCamera::m_nCameraType = CAMERATYPE_NONE;

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
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nCameraType == CAMERATYPE_ONE)
	{
		// 視点・注視点・上方向を設定する（構造体の初期化）
		m_posV[0] = D3DXVECTOR3(0.0f, 200.0f, -400.0f);						// 視点
		m_posR[0] = D3DXVECTOR3(0.0f, 0.0f, .0f);							// 注視点
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// 上方向ベクトル ←固定でOK!!
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 向き
		float fLength1 = (m_posV[0].x - m_posR[0].x);						// 視点から注視点のX軸の距離
		float fLength2 = (m_posV[0].z - m_posR[0].z);						// 視点から注視点のZ軸の距離
		m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));	// 視点から注視点までの距離
	}

	if (m_nCameraType == CAMERATYPE_TWO)
	{
		//************************
		// プレイヤーのカメラ
		//************************
		// 視点、注視点、上方向を設定する
		m_posV[0] = D3DXVECTOR3(0.0f, 200, -400.0f);
		m_posR[0] = D3DXVECTOR3(0.0f, 20.0f, -1.0f);
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//<-固定で良い

		//************************
		// ２プレイヤーのカメラ
		//************************
		// 視点、注視点、上方向を設定する
		m_posV[1] = D3DXVECTOR3(0.0f, 200, -400.0f);
		m_posR[1] = D3DXVECTOR3(0.0f, 20.0f, -1.0f);
		m_vecU[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// <-固定で良い

		for (int nCnt = 0; nCnt < MAX_CAMERA; nCnt++)
		{
			// 三平方の定理(sqrtfはルートの役割)
			m_fDistance = sqrtf(((m_posR[nCnt].x - m_posV[nCnt].x) * (m_posR[nCnt].x - m_posV[nCnt].x)) + ((m_posR[nCnt].z - m_posV[nCnt].z) * (m_posR[nCnt].z - m_posV[nCnt].z)));
		}

		//************************
		// プレイヤー
		//************************
		// ビューポート構成の保存
		m_Viewport[0].X = 0;			// ビューポートの開始位置(x座標)
		m_Viewport[0].Y = 0;			// ビューポートの開始位置(y座標)
		m_Viewport[0].Width = 639;		// ビューポートの幅
		m_Viewport[0].Height = 720;		// ビューポートの高さ
		m_Viewport[0].MinZ = 0.0f;
		m_Viewport[0].MaxZ = 1.0f;

		//************************
		// 2プレイヤー
		//************************
		// ビューポート構成の保存
		m_Viewport[1].X = 641;			// ビューポートの開始位置(x座標)
		m_Viewport[1].Y = 0;			// ビューポートの開始位置(y座標)
		m_Viewport[1].Width = 640;		// ビューポートの幅
		m_Viewport[1].Height = 720;		// ビューポートの高さ
		m_Viewport[1].MinZ = 0.0f;
		m_Viewport[1].MaxZ = 1.0f;
	}

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
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer1P()->GetPos();		//プレイヤーPOS情報の取得

	D3DXVECTOR3 PlayerPos1P = CGame::GetPlayer1P()->GetPos();		//プレイヤーPOS情報の取得
	D3DXVECTOR3 PlayerPos2P = CGame::GetPlayer2P()->GetPos();		//プレイヤーPOS情報の取得

	////************************
	//// カメラの追従処理
	////************************
	//if (m_nCameraType == CAMERATYPE_ONE)
	//{ // ソロモードの場合実行
	//	D3DXVECTOR3 PlayerPos = CGame::GetPlayer1P()->GetPos();        //プレイヤーPOS情報の取得

	//	 //*******************************
	//	 // カメラの追従処理
	//	 //*******************************
	//	 //目的の注視点の設定
	//	m_posRDest.z = PlayerPos.z;
	//	//目的の視点の設定
	//	m_posVDest.z = PlayerPos.z - cosf(m_rot.y) * 250.0f;

	//	//視点の減衰処理
	//	for (int nCnt = 0; nCnt < m_nCameraType; nCnt++)
	//	{
	//		m_posR[nCnt].z += (m_posRDest.z - m_posR[nCnt].z) * 0.1f;
	//		m_posV[nCnt].z += (m_posVDest.z - m_posV[nCnt].z) * 0.1f;
	//	}
	//}

	if (m_nCameraType == CAMERATYPE_TWO)
	{ // VSモードの場合実行
		if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P)
		{ //1Pの場合実行
			//目的の注視点の設定							  
			m_posRDest.z = PlayerPos1P.z;
			//目的の視点の設定																				
			m_posVDest.z = PlayerPos1P.z - cosf(m_rot.y) * 250.0f;
			m_posR[0].z += (m_posRDest.z - m_posR[0].z) * 0.1f;
			m_posV[0].z += (m_posVDest.z - m_posV[0].z) * 0.1f;
		}
		if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P)
		{ //2Pの場合実行
			//目的の注視点の設定							  
			m_posRDest.z = PlayerPos2P.z;
			//目的の視点の設定																				
			m_posVDest.z = PlayerPos2P.z - cosf(m_rot.y) * 250.0f;
			m_posR[1].z += (m_posRDest.z - m_posR[1].z) * 0.1f;
			m_posV[1].z += (m_posVDest.z - m_posV[1].z) * 0.1f;
		}
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(int nCntCamera, CAMERATYPE type)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// タイプ設定
	SetCameraType(type);

	////**************************************************
	////	ソロモード
	////**************************************************
	////if (type == CAMERATYPE_ONE)
	////{
	////	ビューマトリックスの初期化 
	////	D3DXMatrixIdentity(&m_mtxView[0]);

	////	ビューマトリックスの作成
	////	D3DXMatrixLookAtLH(&m_mtxView[0],
	////		&m_posV[0],
	////		&m_posR[0],
	////		&m_vecU[0]);

	////	ビューマトリックスの設定
	////	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[0]);

	////	プロジェクションマトリックスの初期化
	////	D3DXMatrixIdentity(&m_mtxProjection[0]);

	////	プロジェクションマトリックスの作成
	////	D3DXMatrixPerspectiveFovLH(&m_mtxProjection[0],
	////		D3DXToRadian(45.0f),						//視野角
	////		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
	////		10.0f,										//ニア（どこからどこまでカメラで表示するか設定）
	////		3000.0f);									//ファー

	////	プロジェクションマトリックスの設定
	////	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[0]);
	////}

	//**************************************************
	//	vsモード
	//**************************************************
	if (type == CAMERATYPE_TWO)
	{
		//ビューポートの設定
		pDevice->SetViewport(&m_Viewport[nCntCamera]);

		//ビューマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxView[nCntCamera]);

		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView[nCntCamera],
			&m_posV[nCntCamera],
			&m_posR[nCntCamera],
			&m_vecU[nCntCamera]);

		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[nCntCamera]);

		//プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxProjection[nCntCamera]);

		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection[nCntCamera],
			D3DXToRadian(45.0f),																//視野角
			(float)m_Viewport[nCntCamera].Width / (float)m_Viewport[nCntCamera].Height,			//アスペクト比
			10.0f,																				//どこから(ニア)どこまで(ファー)をカメラで
			3000.0f);																			//表示するか設定

		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[nCntCamera]);
	}
}
// カメラの種類の設定
void CCamera::SetCameraType(CAMERATYPE type)
{
	m_nCameraType = type;
}

