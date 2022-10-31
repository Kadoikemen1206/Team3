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
	m_nDestroyTime(200),
	m_fSpeed(5.0f),
	m_bGravity(true),
	m_bFade(false),
	m_bRotate(true),
	m_bScaling(true),
	m_bTransition(true)
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
	BindTexture("PARTICLE_STAR");

	m_beginPos = CBillboard::GetPos();

	//�e�X�g�p
	m_fFadeValue = -0.01f;
	m_fFallSpeed = 0.05f;
	m_fRotateSpeed = 0.1f;
	m_fScalingValue = 0.3f;
	m_destCol = D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);

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

	CBillboard::SetMove(move);
	CBillboard::SetSize(scale);
	CBillboard::SetCol(m_col);
}