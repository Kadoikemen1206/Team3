//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : saito shian
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CCamera
{
public:
	static const float MOVE_SPEED;			// 移動速度
	static const unsigned int MAX_NUMBER;	// 最大数
	static const D3DXVECTOR3 INIT_POSV;		// 視点の初期値
	static const D3DXVECTOR3 INIT_POSR;		// 注視点の初期値
	static const float Z_DEPTH;				// 注視点のZを持ってきた位置より奥深い位置にする
	static const float Z_SEPARATE;			// 視点のZを持ってきた位置から離す

public:
	enum CAMERATYPE
	{
		CAMERATYPE_NONE = 0,
		CAMERATYPE_TITLE,		// タイトル時
		CAMERATYPE_ONE,			// カメラ1つ(ソロモード)
		CAMERATYPE_TWO,			// カメラ2つ(対戦)
		CAMERATYPE_RANKING,		// ランキング時
		CAMERATYPE_MAX
	};
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	CCamera();
	~CCamera();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void SetCamera(int nCntCamera = 0);	// 設定処理
	void SetCameraType(CAMERATYPE type);							// カメラの種類の設定
	static CAMERATYPE GetCameraType(void) { return m_nCameraType; }	// カメラの種類の取得
	static D3DXVECTOR3 GetRot() { return m_rot; }

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DVIEWPORT9 m_Viewport[2];			//ビューポート
	D3DXVECTOR3	m_posV[2];				//視点
	D3DXVECTOR3	m_posR[2];				//注視点
	D3DXVECTOR3	m_vecU[2];				//上方向ベクトル
	D3DXMATRIX	m_mtxProjection[2];		//プロジェクションマトリックス
	D3DXMATRIX	m_mtxView[2];			//ビューマトリックス
	D3DXVECTOR3	m_posVDest;				//目的の視点
	D3DXVECTOR3	m_posRDest;				//目的の注視点

	float		m_fDistance;			//視点から注視点の距離

	static D3DXVECTOR3 m_rot;			//向き
	static CAMERATYPE m_nCameraType;	//カメラのタイプ
};

#endif