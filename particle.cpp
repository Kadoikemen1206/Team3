#include <assert.h>
#include "application.h"
#include "input.h"
#include "main.h"
#include "particle.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle(int nPriority) :
	m_nTime(0),
	m_nDelay(60),
	m_nDestroyTime(300),
	m_fAngle(0.0f),
	m_fRadius(0.0f),
	m_fAttenuation(0.05f),
	m_fSpeed(5.0f),
	m_bGravity(true),			// �d��
	m_bFade(true),				// �A���t�@�l����
	m_bRotate(true),			// �r���{�[�h�̉�]
	m_bScaling(true),			// �g�k
	m_bLocus(true),				// �p�[�e�B�N���ɋO�Ղ�����i���d�ł��j
	m_bTransition(true),		// �F�̕ω�
	m_bPosSpecify(false)		// �ʒu�̎w��
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
	//�e�N�X�`���̓ǂݍ���
	BindTexture("PARTICLE_FLARE");

	m_beginPos = CBillboard::GetPos();

	//�e�X�g�p
	m_fRadius = 75.0f;
	m_fFadeValue = -0.005f;
	m_fFallSpeed = 0.05f;
	m_fRotateSpeed = 0.1f;
	m_fScalingValue = 0.05f;
	m_destPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destCol = D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);
	m_fAttenuation = 0.08f;

	//�ʒu�̎w��e�X�g
	m_effect.destPos = m_beginPos + D3DXVECTOR3(0.0f,50.0f, 0.0f);
	m_effect.frame = 100;
	m_data.push_back(m_effect);

	m_effect.destPos = m_beginPos + D3DXVECTOR3(0.0f, 150.0f, 0.0f);
	m_effect.frame = 250;
	m_data.push_back(m_effect);

	//�I�u�W�F�N�g�̏�����
	CBillboard::Init();
	CBillboard::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update()
{
	CBillboard::Update();

	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	m_pos = CBillboard::GetPos();
	m_col = CBillboard::GetCol();

	if (m_bPosSpecify)
	{// �ʒu�̎w�������ꍇ
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
			m_pos += (m_destPos - m_pos) * m_fAttenuation;
		}
	}

	DetailSetting();

	CBillboard::SetPos(m_pos);
	m_nTime++;

	// ======================
	// ���K��
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
		return;
	}
}

//=============================================================================
// ��������
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

//�ڍאݒ�
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
		m_col.r += (m_destCol.r - m_col.r) / m_nDestroyTime;
		m_col.g += (m_destCol.g - m_col.g) / m_nDestroyTime;
		m_col.b += (m_destCol.b - m_col.b) / m_nDestroyTime;
	}

	if (m_bLocus && (m_nTime % 2) == 0)
	{// �p�[�e�B�N���ɋO�Ղ�����ꍇ
		m_pParticle = CParticle::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_col, PRIORITY_LEVEL3);
		m_pParticle->SetFade(true, -0.1f);
		m_pParticle->SetGravity(false);
		m_pParticle->SetLocus(false);
		m_pParticle->SetPosSpecify(false);
	}

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}