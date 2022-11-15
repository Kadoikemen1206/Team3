//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : TANAKA KOTA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
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
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle(int nPriority) :
	m_nTime(0),									// ����
	m_nDelay(50),								// �x��
	m_nDestroyTime(200),						// ���ł܂ł̎���
	m_fRotateSpeed(0.1f),						// ��]���x
	m_bGravity(false),							// �d��
	m_bFade(false),								// �A���t�@�l����
	m_bRotate(true),							// �r���{�[�h�̉�]
	m_bScaling(false),							// �g�k
	m_bLocus(false),							// �p�[�e�B�N���ɋO�Ղ�����i���d�ł��j
	m_bBounce(false),							// �o�E���h������
	m_bTransition(false),						// �F�̕ω�
	m_destCol(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)),	// �ړI�̐F
	m_behavior(BEHAVIOR_FIREWORKS)				// ����
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticle::Init()
{
	if (m_behavior != BEHAVIOR_INVALID || m_behavior != BEHAVIOR_NONE)
	{
		Preset();
	}

	//�e�N�X�`���̓ǂݍ���
	BindTexture(m_path);

	m_beginPos = CBillboard::GetPos();

	//�I�u�W�F�N�g�̏�����
	CBillboard::Init();
	CBillboard::SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update()
{
	CBillboard::Update();

	m_pos = CBillboard::GetPos();
	m_col = CBillboard::GetCol();

	m_pos += m_moveTransition;

	//�ڍאݒ�
	DetailSetting();

	CBillboard::SetPos(m_pos);

	m_nTime++;

	if (m_nTime >= m_nDestroyTime || m_col.a <= 0.0f)
	{
		CBillboard::Uninit();
		return;
	}
}

//=============================================================================
// ��������
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, EBehaviorType type, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetBehavior(type);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//=============================================================================
// ��������
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const std::string url, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->SetMove(move);
		pParticle->SetCol(col);
		pParticle->SetPath(url);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//=============================================================================
//�ڍאݒ�
//=============================================================================
void CParticle::DetailSetting()
{
	D3DXVECTOR3 move = CBillboard::GetMove();
	D3DXVECTOR3 scale = CBillboard::GetSize();

	if (m_bGravity)
	{// �d�͂��g�p����ꍇ
		if (m_nTime >= m_nDelay)
		{
			move.y -= m_fFallSpeed;
		}
	}

	if (m_bBounce)
	{// �o�E���h���g�p����ꍇ
		if (m_pos.y <= m_lowerPos.y)
		{
			move.y += 1.0f * m_fTouchAttenuation;
			m_fTouchAttenuation -= 0.02f;
		}
	}

	if (m_bFade)
	{// �G�t�F�N�g�̃t�F�[�h���g�p����ꍇ
		m_col.a += m_fFadeValue;
	}

	if (m_bRotate)
	{// �r���{�[�h�̉�]������ꍇ
		D3DXVECTOR3 rot = CBillboard::GetRot();
		D3DXVECTOR3 vec = m_pos - m_beginPos;

		if (vec.x <= 0)
		{// ���݂̈ʒu���J�n�n�_���獶�ɂ���ꍇ
			rot.z += m_fRotateSpeed;
		}
		else
		{// �E�ɂ���ꍇ
			rot.z -= m_fRotateSpeed;
		}

		CBillboard::SetRotate(true);
		CBillboard::SetRot(rot);
	}

	if (m_bScaling)
	{// �g��E�k�����s���ꍇ
		scale.x += m_fScalingValue;
		scale.y += m_fScalingValue;
	}

	if (m_bTransition)
	{// �F�̕ω�������ꍇ
		m_col.r += (m_destCol.r - m_col.r) / (m_nDestroyTime * 0.8f);
		m_col.g += (m_destCol.g - m_col.g) / (m_nDestroyTime * 0.8f);
		m_col.b += (m_destCol.b - m_col.b) / (m_nDestroyTime * 0.8f);
	}

	if (m_bLocus && (m_nTime % 3) == 0 && m_col.a >= 0.2f)
	{// �p�[�e�B�N���ɋO�Ղ�����ꍇ
		m_pParticle = CParticle::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_col, "PARTICLE_FLARE", PRIORITY_LEVEL3);
		m_pParticle->SetSize(D3DXVECTOR3(20.0f,20.0f,0.0f));
		m_pParticle->SetScaling(true, -0.2f);
		m_pParticle->SetFade(true, -0.09f);
		m_pParticle->SetGravity(false);
		m_pParticle->SetLocus(false);
	}

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}

//=============================================================================
//�����̐ݒ�
//=============================================================================
void CParticle::Preset()
{
	switch (m_behavior)
	{
	case BEHAVIOR_FLY:			//���ŗ����鋓��
		m_path = "PARTICLE_FLARE";
		SetCol(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bLocus = false;
		m_bBounce = true;
		m_bTransition = true;
		m_fFadeValue = -0.005f;
		m_fFallSpeed = 0.1f;
		m_fScalingValue = 0.05f;
		break;

	case BEHAVIOR_FIREWORKS:	//��������o���Ɖԉ΂݂����ȋ���
		m_path = "PARTICLE_FLARE";
		SetDestCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_bGravity = true;
		m_bFade = true;
		m_bScaling = true;
		m_bTransition = true;
		m_bLocus = true;
		m_nDelay = 100;
		m_fFallSpeed = 0.001f;
		m_fFadeValue = -0.006f;
		m_fScalingValue = 0.1f;
		break;

	case BEHAVIOR_SMOKE:		//�������̉�
		m_path = "PARTICLE_SMOKE";
		SetMove(D3DXVECTOR3((rand() % 100) * 0.01f, (rand() % 100) * 0.005f, (rand() % 100) * 0.01f));
		SetCol(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_bFade = true;
		m_bScaling = true;
		m_bRotate = true;
		m_fFadeValue = -0.03f;
		m_fScalingValue = 0.1f;
		break;

	default:
		break;
	}
}