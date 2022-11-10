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
#include "motion_model3D.h"
#include "motion.h"
#include "player.h"
#include "meshfield.h"
#include "game.h"
#include "countdown.h"
#include "sound.h"
#include "particle.h"
#include "icon.h"

//=============================================================================
// 定数定義
//=============================================================================
const float CPlayer::SPEED_POWER = 4.0f;
const float CPlayer::JUMP_POWER = 12.0f;
const float CPlayer::GRAVITY_POWER = 0.775f;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) :
	CMotionModel3D(nPriority),
	m_rotDest(0.0f, 0.0f, 0.0f),
	m_posOld(0.0f, 0.0f, 0.0f),
	m_move(0.0f, 0.0f, 0.0f),
	m_nType(EPLAYER_NONE),
	m_nSmokeCnt(0),
	m_keyIndex(-1),
	m_nSpeed(5.0f),
	m_bJumpFlag(false),
	m_bIsLanding(false),
	m_bIsLandingUp(false),
	m_pParticle(nullptr),
	m_isMove(true),
	m_HalfWayPointFlag(false)
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
	CMotionModel3D::Init();

	//モデルのロード
	SetMotion("Data/MODEL/PLAYER/player_new/Motion/motion_new.txt");

	m_bJumpFlag = true;
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	CMotionModel3D::Update();

	static int count = 0;
	if (m_moutionType == MOTION_BURABURA)
	{
		count++;
		if (count >= 240)
		{
			count = 0;
			SetMotionType(MOTION_NONE);
		}
		return;
	}

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 前回の位置を保存
	m_posOld = pos;

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	Move();

	// 移動力取得
	D3DXVECTOR3 move = GetMove();

	// 重力設定
	move.y -= GRAVITY_POWER;

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

	// 移動量加算
	pos += move;
	move.x *= 0.75f;
	move.z *= 0.75f;

	if (pos.x != m_posOld.x && pos.z != m_posOld.z)
	{
		m_nSmokeCnt++;
	}

	if ((m_nSmokeCnt % 10) == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			m_pParticle = CParticle::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, pos.z),
				CParticle::BEHAVIOR_SMOKE,
				PRIORITY_LEVEL3);
		}

		m_nSmokeCnt++;
	}

	// ポインタ宣言
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	m_bIsLandingUp = false;

	// プレイヤーとモデルの当たり判定
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//オブジェクトのタイプを取得
		CObject::EObjType objType = pObject->GetObjType();

		if (objType == OBJTYPE_MODEL)
		{
			CObjectX *pObjectX = (CObjectX*)pObject;

			// 当たり判定
			m_bIsLanding = pObjectX->Collision(&pos, &m_posOld, &GetMaxVtx(), &GetMinVtx());

			if (m_bIsLanding)
			{ // 当たった場合
				move = D3DXVECTOR3(0.0f, move.y, 0.0f);
			}
			// y軸の当たり判定
			if (m_bIsLandingUp)
			{
				pObjectX->UpCollision(&pos, &m_posOld, &GetMaxVtx(), &GetMinVtx(), &move);
			}
			else
			{
 				m_bIsLandingUp = pObjectX->UpCollision(&pos, &m_posOld, &GetMaxVtx(), &GetMinVtx(), &move);
			}
			if (m_bIsLandingUp)
			{
			m_bJumpFlag = false;
			}
		}
		//ポインタを次に進める
		pObject = pObject->GetNext();
	}

	// メッシュフィールドのポインタを取得
	//pMeshField->Collision(&pos);
	CMeshfield *pMeshField = CGame::GetMeshfield();

	if (pMeshField != nullptr)
	{
		float i = pMeshField->GetAnswer();

		// プレイヤーのposとrotの設定
		if (pos.y < pMeshField->GetAnswer())
		{
			m_bJumpFlag = false;
		}

		// メッシュフィールドとの当たり判定
		//if (m_bJumpFlag == false)
		//{
		//	pMeshField->Collision(&pos);
		//}

		// y軸が移動してなかった場合
		if (pos.y == m_posOld.y)
		{
			//move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	if (m_HalfWayPointFlag == false)
	{
		// リスポーン処理
		Respawn(pos);
	}

	// 中間地点
	HalfWayPoint(pos);
	if (m_moutionType != MOTION_JUMP)
	{
		if (!m_bIsLandingUp)
		{
			SetMotionType(MOTION_JUMP);
		}
		else
		{
			if (move.x == 0.0f && move.z == 0.0f)
			{
				if (m_moutionType != MOTION_NONE && m_moutionType != MOTION_SCREW)
				{
					SetMotionType(MOTION_NONE);
				}
				//BGMの設定
				CApplication::GetSound()->Play(CSound::LABEL_SE_HASHIRI);
			}
			else
			{
				if (move.x < 0.25f && move.x > -0.25f)
				{
					move.x = 0.0f;
				}
				if (move.z < 0.25f && move.z > -0.25f)
				{
					move.z = 0.0f;
				}

				if (m_moutionType != MOTION_MOVE)
				{
					SetMotionType(MOTION_MOVE);
				}
			}
		}
	}
	else
	{
		if (m_bIsLandingUp)
		{
			SetMotionType(MOTION_LANDING);
		}
	}

	// リスポーン処理
	Respawn(pos);

	// プレイヤーのposとrotとmoveの設定
	SetPos(pos);
	SetRot(rot);
	SetMove(move);
}

//=============================================================================
// リスポーン処理
//=============================================================================
void CPlayer::Respawn(D3DXVECTOR3 &pos)
{
	// 位置変更
	if (pos.y <= -100.0f && m_nType == EPLAYER_1P)
	{
		SetMotionType(MOTION_BURABURA);
		pos = D3DXVECTOR3(-700.0f,80.0f,0.0f);
	}
	if (pos.y <= -100.0f && m_nType == EPLAYER_2P)
	{
		pos = D3DXVECTOR3(700.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
void CPlayer::HalfWayPoint(D3DXVECTOR3 & pos)
{
	// 位置変更
	if (pos.z >= 2800.0f)
	{
		m_HalfWayPointFlag = true;
		if (pos.y <= -100.0f && m_HalfWayPointFlag == true && m_nType == EPLAYER_1P)
		{
			pos = D3DXVECTOR3(-700.0f, 0.0f, 2800.0f);
		}
		if (pos.y <= -100.0f && m_HalfWayPointFlag == true && m_nType == EPLAYER_2P)
		{
			pos = D3DXVECTOR3(700.0f, 0.0f, 2800.0f);
		}
	}
	else
	{
		if (pos.y <= -100.0f && m_HalfWayPointFlag == true && m_nType == EPLAYER_1P)
		{
			pos = D3DXVECTOR3(-700.0f, 0.0f, 2800.0f);
		}
		if (pos.y <= -100.0f && m_HalfWayPointFlag == true && m_nType == EPLAYER_2P)
		{
			pos = D3DXVECTOR3(-700.0f, 0.0f, 2800.0f);
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
void CPlayer::Move()
{
	if (!m_isMove)
	{
		return;
	}

	/* ↓移動処理↓ */

	// キーボードの情報取得
	CInput *pInputKeyboard = CApplication::GetInput();

	// 移動力取得
	D3DXVECTOR3 move = GetMove();

	// カメラの情報取得
	D3DXVECTOR3 pCameraRot = CCamera::GetRot();

	if (pInputKeyboard->Press(KEY_UP, m_keyIndex))
	{// 上に移動
		if (pInputKeyboard->Press(KEY_LEFT, m_keyIndex))
		{
			move.x = sinf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			move.z = cosf(D3DX_PI * -0.25f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.75f;
		}
		else if (pInputKeyboard->Press(KEY_RIGHT, m_keyIndex))
		{
			move.x = sinf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
			move.z = cosf(D3DX_PI * 0.25f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.75f;
		}
		else
		{
			move.x = sinf(pCameraRot.y) * m_nSpeed;
			move.z = cosf(pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI;
		}
	}

	else if (pInputKeyboard->Press(KEY_DOWN, m_keyIndex))
	{// 下に移動
		if (pInputKeyboard->Press(KEY_LEFT, m_keyIndex))
		{
			move.x = sinf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			move.z = cosf(D3DX_PI * -0.75f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->Press(KEY_RIGHT, m_keyIndex))
		{
			move.x = sinf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
			move.z = cosf(D3DX_PI * 0.75f + pCameraRot.y) * m_nSpeed;
			m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.25f;
		}
		else
		{
			move.x = sinf(pCameraRot.y) * -m_nSpeed;
			move.z = cosf(pCameraRot.y) * -m_nSpeed;
			m_rotDest.y = pCameraRot.y + 0.0f;
		}

	}
	else if (pInputKeyboard->Press(KEY_LEFT, m_keyIndex))
	{// 左に移動
		move.x = sinf(D3DX_PI * 0.5f + pCameraRot.y) * -m_nSpeed;
		move.z = cosf(D3DX_PI * 0.5f + pCameraRot.y) * -m_nSpeed;
		m_rotDest.y = pCameraRot.y + D3DX_PI * 0.5f;
	}
	else if (pInputKeyboard->Press(KEY_RIGHT, m_keyIndex))
	{// 右に移動
		move.x = sinf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		move.z = cosf(D3DX_PI * 0.5f + pCameraRot.y) * m_nSpeed;
		m_rotDest.y = pCameraRot.y + -D3DX_PI * 0.5f;
	}

	if (pInputKeyboard->Trigger(KEY_JUMP, m_keyIndex) && m_bJumpFlag == false)
	{// ジャンプ
		m_bJumpFlag = true;
		move.y += JUMP_POWER;
		////BGMの設定
		//CApplication::GetSound()->Play(CSound::LABEL_SE_JUMP_01);
	}
	SetMove(move);

	//テスト用
#ifdef _DEBUG

	D3DXVECTOR3 pos = GetPos();

	if (pInputKeyboard->Trigger(DIK_PERIOD))
	{
		int max = 100;
		for (int i = 0; i < max; i++)
		{
			m_pParticle = CParticle::Create(D3DXVECTOR3(pos.x, pos.y + 180.0f, pos.z),
				D3DXVECTOR3(sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), sinf((rand() % max * ((360 / max) * (D3DX_PI / 180)))) * cosf((rand() % max * ((360 / max) * (D3DX_PI / 180)))), cosf((rand() % max * ((360 / max) * (D3DX_PI / 180))))),
				D3DXCOLOR((rand() % 100) * 0.01f, (rand() % 100) * 0.01f, (rand() % 100) * 0.01f, 1.0f),
				"PARTICLE_FLARE",
				PRIORITY_LEVEL3);
			//m_pParticle->SetLower(pos);
		}
	}

	if (pInputKeyboard->Trigger(DIK_BACKSPACE))
	{
		m_pIcon->SetDestroy(true);
	}

#endif // _DEBUG
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

void CPlayer::SetMotionType(EMotion inMotion)
{
	// 同じモーションには遷移しない。
	if (m_moutionType == inMotion)
	{
		return;
	}

	m_moutionType = inMotion;
	GetMotion()->SetNumMotion(m_moutionType);
}
