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
	m_nSpeed(5.0f)
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
	BindTexture("FLOOR2");

	//objectx��pos��rot
	m_pos = CBillboard::GetPos();

	//�I�u�W�F�N�g�̏�����
	CBillboard::Init();
	CBillboard::SetMove(D3DXVECTOR3(rand() % 5, 1.5f, rand() % 5));
	CBillboard::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update()
{
	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::GetInputKeyboard();
	CBillboard::Update();

	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	m_pos = CBillboard::GetPos();

	CBillboard::SetPos(m_pos);
	CBillboard::SetCol(D3DXCOLOR(0.0f,1.0f,1.0f,0.6f));
}

//=============================================================================
// ��������
//=============================================================================
CParticle * CParticle::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetPos(pos);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}