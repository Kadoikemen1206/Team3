//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "application.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "objectX.h"
#include "player.h"
#include "shadow.h"
#include "renderer.h"
#include "meshfield.h"
#include "obstacle.h"

#include "particle.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : 
	m_nSpeed(5.0f),					//移動スピード
	m_rotDest(0.0f, 0.0f, 0.0f)		//目的の角度
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_PLAYER);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init()
{
	//オブジェクトの初期化
	CObjectX::Init();

	//モデルのロード
	LoadModel("PLAYER");

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	// カメラの情報取得
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();

	// 座標取得
	D3DXVECTOR3 pos = CObjectX::GetPos();

	// 向き取得
	D3DXVECTOR3 rot = CObjectX::GetRot();

	// 前回の位置を保存
	m_posOld = pos;

	// 1Pの場合下記の移動処理を実行
	if (m_nType == EPLAYER_1P)
	{
		if (pInputKeyboard->Press(DIK_W))
		{// 上に移動
			if (pInputKeyboard->Press(DIK_A))
			{
				pos.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
			}
			else if (pInputKeyboard->Press(DIK_D))
			{
				pos.x += sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
			}
			else
			{
				pos.x += sinf(pCameraRot.y) * m_nSpeed;
				pos.z += cosf(pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI;
			}
		}

		else if (pInputKeyboard->Press(DIK_S))
		{// 下に移動
			if (pInputKeyboard->Press(DIK_A))
			{
				pos.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
			}
			else if (pInputKeyboard->Press(DIK_D))
			{
				pos.x += sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
			}
			else
			{
				pos.x -= sinf(pCameraRot.y) * m_nSpeed;
				pos.z -= cosf(pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + 0.0f;
			}

		}
		else if (pInputKeyboard->Press(DIK_A))
		{// 左に移動
			pos.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
		}
		else if (pInputKeyboard->Press(DIK_D))
		{// 右に移動
			pos.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
		}
	}
	
	// 2Pの場合下記の移動処理を実行
	if (m_nType == EPLAYER_2P)
	{
		if (pInputKeyboard->Press(DIK_UP))
		{// 上に移動
			if (pInputKeyboard->Press(DIK_LEFT))
			{
				pos.x += sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
			}
			else if (pInputKeyboard->Press(DIK_RIGHT))
			{
				pos.x += sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
			}
			else
			{
				pos.x += sinf(pCameraRot.y) * m_nSpeed;
				pos.z += cosf(pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI;
			}
		}

		else if (pInputKeyboard->Press(DIK_DOWN))
		{// 下に移動
			if (pInputKeyboard->Press(DIK_LEFT))
			{
				pos.x += sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
			}
			else if (pInputKeyboard->Press(DIK_RIGHT))
			{
				pos.x += sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
				pos.z += cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
			}
			else
			{
				pos.x -= sinf(pCameraRot.y) * m_nSpeed;
				pos.z -= cosf(pCameraRot.y) * m_nSpeed;
				m_rotDest.y = pCameraRot.y + 0.0f;
			}

		}
		else if (pInputKeyboard->Press(DIK_LEFT))
		{// 左に移動
			pos.x -= sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z -= cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
		}
		else if (pInputKeyboard->Press(DIK_RIGHT))
		{// 右に移動
			pos.x += sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			pos.z += cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
		}
	}

	//テスト用
	if (pInputKeyboard->Press(DIK_PERIOD))
	m_pParticle = CParticle::Create(pos, 
		D3DXVECTOR3(sinf((rand() % 25 * ((360 / 25) * (D3DX_PI / 180)))), 1.0f, cosf((rand() % 25 * ((360 / 25) * (D3DX_PI / 180))))), 
		D3DXCOLOR(rand() % 100 * 0.01f, rand() % 100 * 0.01f, rand() % 100 * 0.01f, 1.0f),
		PRIORITY_LEVEL3);

	//角度の正規化(目的の角度)
	if (m_rotDest.y - rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	// 少しずつ向く
	rot.y += (m_rotDest.y - rot.y) * 0.08f;

	// 角度の正規化(現在の角度)
	if (rot.y > D3DX_PI)
	{
		rot.y = rot.y - D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = rot.y + D3DX_PI * 2;
	}

	// ポインタ宣言
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	// プレイヤーとモデルの当たり判定
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//変数宣言
		CObject::EObjType objType;

		//オブジェクトのタイプを取得
		objType = pObject->GetObjType();

		if (objType == OBJTYPE_MODEL)
		{
			CObjectX *pObjectX = (CObjectX*)pObject;
			pObjectX->Collision(&pos, &m_posOld, &CObjectX::GetSize());
		}

		//ポインタを次に進める
		pObject = pObject->GetNext();
	}

	// メッシュフィールドのポインタを取得
	CMeshfield *pMeshField = CApplication::GetMeshfield();
	//pMeshField->Collision(&pos);

	// プレイヤーのposとrotの設定
	CObjectX::SetPos(pos);
	CObjectX::SetRot(rot);

	// CObjectXの更新処理
	CObjectX::Update();
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer * CPlayer::Create(EPLAYER type, const D3DXVECTOR3 pos, int nPriority)
{
	CPlayer *pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetType(type);
		pPlayer->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pPlayer;
}

//=============================================================================
// タイプ設定処理
//=============================================================================
void CPlayer::SetType(EPLAYER type)
{
	m_nType = type;
}
//=============================================================================
// スピードの設定
//=============================================================================
void CPlayer::SetSpeed(float speed)
{
	m_nSpeed = speed;
}