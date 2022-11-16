//=============================================================================
//
// ギミック処理 [gimmick.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "application.h"
#include "main.h"
#include "objectX.h"
#include "gimmick.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGimmick::CGimmick(int nPriority) 
{
	// メンバ変数のクリア
	m_GimmickType = GIMMICKTYPE_NONE;
	m_Pos = {};
	m_Completion = false;
	m_pHitPlayer = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGimmick::~CGimmick()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGimmick::Init()
{
	// ObjectXの初期化処理
	CObjectX::Init();

	// モデルタイプ
	SetType(OBJTYPE_GIMMICK);

	//モデルのロード
	LoadModel("TRIANGLE");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGimmick::Uninit()
{
	// ObjectXの終了処理
	CObjectX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGimmick::Update()
{
	// ObjectXの更新処理
	CObjectX::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGimmick::Draw()
{
	// ObjectXの描画処理
	CObjectX::Draw();
}

//=============================================================================
// ギミックの種類の設定処理
//=============================================================================
void CGimmick::SetGimmickType(GIMMICKTYPE type)
{
	m_GimmickType = type;
}

//=============================================================================
// 当たったかどうかの判定
//=============================================================================
bool CGimmick::Collision(CPlayer* inPlayer)
{
	if (inPlayer == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 playerPos = inPlayer->GetPos();		// 指定したプレイヤーのPos取得
	D3DXVECTOR3 thisPos = GetPos();					// ギミックのPos取得

	// ギミックの範囲
	if (((thisPos.x + 150.0f) >= playerPos.x) && ((thisPos.z + 150.0f) >= playerPos.z)
		&& ((thisPos.x - 150.0f) <= playerPos.x) && ((thisPos.z - 150.0f) <= playerPos.z))
	{// プレイヤーを動かさないようにするフラグを有効にする
		m_pHitPlayer = inPlayer;
		return true;
	}

	return false;
}

//=============================================================================
// ギミックに当たったかどうかの判定
//=============================================================================
bool CGimmick::CollisionGimmick(CPlayer* Player)
{
	if (Player == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 PlayerPos = Player->GetPos();	// 指定したプレイヤーのPos取得
	D3DXVECTOR3 thisPos = GetPos();				// ギミックのPos取得
	D3DXVECTOR3 thisSize = GetSize();			// ギミックのSize取得

	// ギミックの範囲
	if (((thisPos.x + thisSize.x - 10.0f) >= PlayerPos.x) && ((thisPos.z + thisSize.z - 10.0f) >= PlayerPos.z)
		&& ((thisPos.x - thisSize.x + 10.0f) <= PlayerPos.x) && ((thisPos.z - thisSize.z + 10.0f) <= PlayerPos.z))
	{// プレイヤーを動かさないようにするフラグを有効にする
		m_pHitPlayer = Player;
		return true;
	}

	return false;
}
