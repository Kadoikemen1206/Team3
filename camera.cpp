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
const float CCamera::MOVE_SPEED = 5.0f;										// 移動速度
const unsigned int CCamera::MAX_NUMBER = 2;									// 最大数
const D3DXVECTOR3 CCamera::INIT_POSV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);	// 視点の初期値
const D3DXVECTOR3 CCamera::INIT_POSR = D3DXVECTOR3(0.0f, 20.0f, -1.0f);		// 注視点の初期値
const float CCamera::Z_DEPTH = 120.0f;										// 注視点のZを持ってきた位置より奥深い位置にする
const float CCamera::Z_SEPARATE = 250.0f;									// 視点のZを持ってきた位置から離す

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
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_Viewport[nCnt] = {};
	}

	if (CApplication::GetMode() == CApplication::MODE_TITLE)
	{
		// 視点・注視点・上方向を設定する（構造体の初期化）
		m_posV[0] = D3DXVECTOR3(0.0f, 500.0f, -500.0f);	// 視点
		m_posR[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 上方向ベクトル ←固定でOK!!
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
		D3DXVECTOR3 length = m_posV[0] - m_posR[0];		// 差分
		m_fDistance = sqrtf((length.x * length.x) + (length.z * length.z));	// 視点から注視点までの距離
	}

	if (m_nCameraType == CAMERATYPE_ONE)
	{
		// 視点・注視点・上方向を設定する（構造体の初期化）
		m_posV[0] = INIT_POSV;							// 視点
		m_posR[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 上方向ベクトル ←固定でOK!!
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
		D3DXVECTOR3 length = m_posV[0] - m_posR[0];		// 差分
		m_fDistance = sqrtf((length.x * length.x) + (length.z * length.z));	// 視点から注視点までの距離
	}

	if (m_nCameraType == CAMERATYPE_TWO && CApplication::GetMode() == CApplication::MODE_GAME)
	{
		D3DXVECTOR3 PlayerPos1P = CGame::GetPlayer1P()->GetPos();		//プレイヤーPOS情報の取得
		D3DXVECTOR3 PlayerPos2P = CGame::GetPlayer2P()->GetPos();		//プレイヤーPOS情報の取得

		//************************
		// プレイヤーのカメラ
		//************************
		// 視点、注視点、上方向を設定する
		m_posV[0] = INIT_POSV;
		m_posR[0] = INIT_POSR;
		m_posV[0].x = PlayerPos1P.x;
		m_posR[0].x = PlayerPos1P.x;
		m_vecU[0] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//<-固定で良い

		//************************
		// ２プレイヤーのカメラ
		//************************
		// 視点、注視点、上方向を設定する
		m_posV[1] = INIT_POSV;
		m_posR[1] = INIT_POSR;
		m_posV[1].x = PlayerPos2P.x;
		m_posR[1].x = PlayerPos2P.x;
		m_vecU[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// <-固定で良い

		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			D3DXVECTOR3 length = m_posR[nCnt] - m_posV[nCnt];	// 注視点と視点の差分

			// 三平方の定理(sqrtfはルートの役割)
			m_fDistance = sqrtf((length.x * length.x) + (length.z * length.z));
		}

		//************************
		// プレイヤー
		//************************
		// ビューポート構成の保存
		m_Viewport[0].X = 0;		// ビューポートの開始位置(x座標)
		m_Viewport[0].Y = 0;		// ビューポートの開始位置(y座標)
		m_Viewport[0].Width = 639;	// ビューポートの幅
		m_Viewport[0].Height = 720;	// ビューポートの高さ
		m_Viewport[0].MinZ = 0.0f;
		m_Viewport[0].MaxZ = 1.0f;

		//************************
		// 2プレイヤー
		//************************
		// ビューポート構成の保存
		m_Viewport[1].X = 641;		// ビューポートの開始位置(x座標)
		m_Viewport[1].Y = 0;		// ビューポートの開始位置(y座標)
		m_Viewport[1].Width = 640;	// ビューポートの幅
		m_Viewport[1].Height = 720;	// ビューポートの高さ
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
	//************************
	// カメラの追従処理
	//************************
	if (CApplication::GetMode() == CApplication::MODE_GAME)
	{
		switch (m_nCameraType)
		{
		case CCamera::CAMERATYPE_NONE:
			break;
		case CCamera::CAMERATYPE_TITLE:
			break;
		case CCamera::CAMERATYPE_ONE:	// ソロモードの場合実行
		{
			D3DXVECTOR3 PlayerPos = CGame::GetPlayer1P()->GetPos();	//プレイヤーPOS情報の取得

			//*******************************
			// カメラの追従処理
			//*******************************
			//目的の注視点の設定
			m_posRDest.z = PlayerPos.z + Z_DEPTH;
			//目的の視点の設定
			m_posVDest.z = PlayerPos.z - cosf(m_rot.y) * Z_SEPARATE;

			//視点の減衰処理
			for (int nCnt = 0; nCnt < m_nCameraType; nCnt++)
			{
				m_posR[nCnt].z += (m_posRDest.z - m_posR[nCnt].z) * 0.1f;
				m_posV[nCnt].z += (m_posVDest.z - m_posV[nCnt].z) * 0.1f;
			}
		}
		break;
		case CCamera::CAMERATYPE_TWO:
		{
			D3DXVECTOR3 PlayerPos1P = CGame::GetPlayer1P()->GetPos();		//プレイヤーPOS情報の取得
			D3DXVECTOR3 PlayerPos2P = CGame::GetPlayer2P()->GetPos();		//プレイヤーPOS情報の取得

			if (CGame::GetPlayer1P()->GetPlayerType() == CPlayer::EPLAYER_1P)
			{ //1Pの場合実行
			  //目的の注視点の設定
				m_posRDest.z = PlayerPos1P.z + Z_DEPTH;
				//目的の視点の設定
				m_posVDest.z = PlayerPos1P.z - cosf(m_rot.y) * Z_SEPARATE;
				m_posR[0].z += (m_posRDest.z - m_posR[0].z) * 0.5f;
				m_posV[0].z += (m_posVDest.z - m_posV[0].z) * 0.5f;
			}
			if (CGame::GetPlayer2P()->GetPlayerType() == CPlayer::EPLAYER_2P)
			{ //2Pの場合実行
			  //目的の注視点の設定
				m_posRDest.z = PlayerPos2P.z + Z_DEPTH;
				//目的の視点の設定
				m_posVDest.z = PlayerPos2P.z - cosf(m_rot.y) * Z_SEPARATE;
				m_posR[1].z += (m_posRDest.z - m_posR[1].z) * 0.1f;
				m_posV[1].z += (m_posVDest.z - m_posV[1].z) * 0.1f;
			}
		}
		break;
		case CCamera::CAMERATYPE_MAX:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(int nCntCamera)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//**************************************************
	//	ソロモード
	//**************************************************
	if (m_nCameraType == CAMERATYPE_ONE)
	{
		//ビューマトリックスの初期化 
		D3DXMatrixIdentity(&m_mtxView[0]);

		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView[0],
			&m_posV[0],
			&m_posR[0],
			&m_vecU[0]);

		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[0]);

		//プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxProjection[0]);

		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection[0],
			D3DXToRadian(45.0f),						//視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
			10.0f,										//ニア（どこからどこまでカメラで表示するか設定）
			3000.0f);									//ファー

		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[0]);
	}

	//**************************************************
	//	vsモード
	//**************************************************
	if (m_nCameraType == CAMERATYPE_TWO && CApplication::GetMode() == CApplication::MODE_GAME)
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

	//**************************************************
	//	タイトル
	//**************************************************
	if (CApplication::GetMode() == CApplication::MODE_TITLE)
	{
		//ビューマトリックスの初期化 
		D3DXMatrixIdentity(&m_mtxView[0]);

		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView[0],
			&m_posV[0],
			&m_posR[0],
			&m_vecU[0]);

		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView[0]);

		//プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxProjection[0]);

		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection[0],
			D3DXToRadian(45.0f),						//視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
			10.0f,										//ニア（どこからどこまでカメラで表示するか設定）
			3000.0f);									//ファー

		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection[0]);
	}
}
// カメラの種類の設定
void CCamera::SetCameraType(CAMERATYPE type)
{
	m_nCameraType = type;
}

// カメラの視点の設定
void CCamera::SetPosV(D3DXVECTOR3 posV)
{
	m_posV[0] = posV;
}

// カメラの注視点の設定
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posR[0] = posR;
}

