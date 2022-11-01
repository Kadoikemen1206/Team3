#include <assert.h>
#include "application.h"
#include "input.h"
#include "main.h"
#include "particle.h"
#include "renderer.h"
#include "meshfield.h"
#include "objectX.h"
#include "model.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle::CParticle(int nPriority) :
	m_nTime(0),
	m_nDelay(50),
	m_nDestroyTime(200),
	m_fAngle(0.0f),
	m_fRadius(0.0f),
	m_fAttenuation(0.05f),
	m_fSpeed(5.0f),
	m_bGravity(false),				// 重力
	m_bFade(false),					// アルファ値増減
	m_bRotate(true),				// ビルボードの回転
	m_bScaling(false),				// 拡縮
	m_bLocus(false),				// パーティクルに軌跡をつける（激重です）
	m_bBounce(false),				// バウンドさせる
	m_bUseMesh(false),
	m_bTransition(false),			// 色の変化
	m_bPosSpecify(false),			// 位置の指定
	m_type(BEHAVIOR_FLY)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticle::Init()
{
	if (m_bUseMesh)
	{
		m_pModel = CModel::Create(CBillboard::GetPos(), PRIORITY_LEVEL3);
		m_pModel->SetMove(m_moveTransition);
		m_pModel->LoadModel("TRIANGLE");

		return S_OK;
	}

	//テクスチャの読み込み
	BindTexture("PARTICLE_FLARE");

	m_beginPos = CBillboard::GetPos();
	m_destPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	if (m_type != BEHAVIOR_INVALID || m_type != BEHAVIOR_NONE)
	{
		Preset();
	}

	//位置の指定テスト
	//m_effect.destPos = m_beginPos + D3DXVECTOR3(0.0f,30.0f, 0.0f);
	//m_effect.frame = 100;
	//m_data.push_back(m_effect);

	//オブジェクトの初期化
	CBillboard::Init();
	CBillboard::SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	// ポインタ宣言
	CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);

	// メッシュのY位置を調べるためのもの（適当にやってる
	if (m_bBounce)
	{
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

			if (objType == OBJTYPE_MESH)
			{
				CObjectX *pObjectX = (CObjectX*)pObject;
				m_lowerPos = pObjectX->GetPos();
			}

			//ポインタを次に進める
			pObject = pObject->GetNext();
		}
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticle::Update()
{
	CBillboard::Update();

	// 前回の位置を保存
	m_posOld = m_pos;

	m_pos = CBillboard::GetPos();
	m_col = CBillboard::GetCol();

	if (m_bPosSpecify)
	{// 位置の指定をする場合
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data.at(i).frame != m_nTime)
			{
				continue;
			}

			m_destPos = m_data.at(i).destPos;
			m_bPosOperate = true;
		}

		if (m_bPosOperate)
		{
			m_moveTransition = (m_destPos - m_pos) * m_fAttenuation;
		}
	}

	m_pos += m_moveTransition;

	DetailSetting();

	CBillboard::SetPos(m_pos);

	if (m_bUseMesh)
	{
		m_pModel->SetPos(m_pos);
	}

	m_nTime++;

	// ======================
	// 正規化
	// ======================
	if (m_fRadius > D3DX_PI)
	{
		m_fRadius -= D3DX_PI * 2;
	}
	else if (m_fRadius < -D3DX_PI)
	{
		m_fRadius += D3DX_PI * 2;
	}

	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2;
	}
	else if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2;
	}

	if (m_nTime >= m_nDestroyTime || m_col.a <= 0.0f)
	{
		CBillboard::Uninit();

		if (m_bUseMesh)
		{
			m_pModel->Uninit();
		}
		return;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetMove(move);
		pParticle->SetCol(col);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//詳細設定
void CParticle::DetailSetting()
{
	CMeshfield *pMeshField = CApplication::GetMeshfield();
	D3DXVECTOR3 move = CBillboard::GetMove();
	D3DXVECTOR3 scale = CBillboard::GetSize();

	if (m_bGravity)
	{// 重力を使用する場合
		if (m_nTime >= m_nDelay)
		{
			move.y -= m_fFallSpeed;
		}
	}

	if (m_bBounce)
	{// バウンドを使用する場合
		if (m_pos.y <= m_lowerPos.y)
		{
			move.y += 1.0f * m_fTouchAttenuation;
			m_fTouchAttenuation -= 0.02f;
		}
	}

	if (m_bFade)
	{// エフェクトのフェードを使用する場合
		m_col.a += m_fFadeValue;
	}

	if (m_bRotate)
	{// ビルボードの回転をする場合
		D3DXVECTOR3 rot = CBillboard::GetRot();
		D3DXVECTOR3 vec = m_pos - m_beginPos;

		if (vec.x <= 0)
		{// 現在の位置が開始地点から左にある場合
			rot.z += m_fRotateSpeed;
		}
		else
		{// 右にある場合
			rot.z -= m_fRotateSpeed;
		}

		CBillboard::SetRotate(true);
		CBillboard::SetRot(rot);
	}

	if (m_bScaling)
	{// 拡大・縮小を行う場合
		scale.x += m_fScalingValue;
		scale.y += m_fScalingValue;
	}

	if (m_bTransition)
	{// 色の変化をつける場合
		m_col.r += (m_destCol.r - m_col.r) / (m_nDestroyTime * 0.5f);
		m_col.g += (m_destCol.g - m_col.g) / (m_nDestroyTime * 0.5f);
		m_col.b += (m_destCol.b - m_col.b) / (m_nDestroyTime * 0.5f);
	}

	if (m_bLocus && (m_nTime % 3) == 0 && m_col.a >= 0.2f)
	{// パーティクルに軌跡をつける場合
		m_pParticle = CParticle::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_col, PRIORITY_LEVEL3);
		m_pParticle->SetSize(D3DXVECTOR3(20.0f,20.0f,0.0f));
		m_pParticle->SetScaling(true, -0.2f);
		m_pParticle->SetFade(true, -0.09f);
		m_pParticle->SetGravity(false);
		m_pParticle->SetLocus(false);
		m_pParticle->SetPosSpecify(false);
	}

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}

//挙動の設定
void CParticle::Preset()
{
	switch (m_type)
	{
	case BEHAVIOR_NONE:
		break;

	case BEHAVIOR_FLY:
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bLocus = true;
		m_bBounce = true;
		m_bTransition = true;
		m_fFadeValue = -0.005f;
		m_fFallSpeed = 0.1f;
		m_fRotateSpeed = 0.1f;
		m_fScalingValue = 0.05f;
		m_fAttenuation = 0.08f;
		break;

	case BEHAVIOR_FIREWORKS:
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bTransition = true;
		m_nDelay = 100;
		m_fFallSpeed = 0.001f;
		m_fFadeValue = -0.006f;
		m_fScalingValue = 0.1f;
		m_fAttenuation = 0.1f;
		break;
	}
}