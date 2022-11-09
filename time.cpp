//=============================================================================
//
// �^�C������ [time.cpp]
// Author : kubota yuuki
// Author : kado takuma
//
//=============================================================================
#include "number.h"
#include "object2D.h"
#include "time.h"
#include <time.h>
#include <math.h>

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CNumber *CTime::m_apNumBer[5] = {};
CObject2D *CTime::m_apObject2D[2] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority) :
	CObject(nPriority),
	m_apnTime(0)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_apNumBer[nCnt] = nullptr;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// �^�C���̏�����
//=============================================================================
HRESULT CTime::Init()
{
	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < 5; nCntScore++)
	{
		m_apNumBer[nCntScore] = CNumber::Create(D3DXVECTOR3(100.0f + (80.0f * nCntScore), 80.0f, 0.0f),D3DXVECTOR3(60.0f, 90.0f, 0.0f));
	}

	m_apObject2D[0] = CObject2D::Create("TIMER_DOT", D3DXVECTOR3(135.0f, 90.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), CObject::PRIORITY_LEVEL5);
	m_apObject2D[1] = CObject2D::Create("TIMER_DOT", D3DXVECTOR3(295.0f, 90.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), CObject::PRIORITY_LEVEL5);

	// �~���b�ݒ�
	m_nTime = timeGetTime();

	return S_OK;
}

//=============================================================================
// �^�C���̏I��
//=============================================================================
void CTime::Uninit()
{
}

//=============================================================================
// �^�C���̍X�V
//=============================================================================
void CTime::Update()
{
	//�o�ߎ��Ԃ̍X�V
	AddTime(1);
}

//=============================================================================
// �^�C���̕`��
//=============================================================================
void CTime::Draw()
{

}

//=============================================================================
//�^�C���̃N���G�C�g
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nScore, int nPriority)
{
	CTime *pTime = nullptr;

	pTime = new CTime(nPriority);

	if (pTime != nullptr)
	{
		pTime->Init();
		pTime->SetPos(pos);
		pTime->SetSize(size);
		pTime->SetTime(nScore);
	}

	return pTime;
}

//=============================================================================
//�Z�b�g�^�C��
//=============================================================================
void CTime::SetTime(int nScore)
{
	//�e���̐������i�[
	int nNumber[5];

	//�l�i�[
	int time;
	time = nScore;

	//for (int nCnt = 0; nCnt < 5; nCnt++)
	//{
	//	nNumber[nCnt] = time % (int)powf(10, (5 - nCnt) + 1) / (int)powf(10, (5 - nCnt));
	//}

	nNumber[0] = time % 1000000 / 100000;
	nNumber[1] = time % 100000 / 10000;
	nNumber[2] = time % 10000 / 1000;
	nNumber[3] = time % 1000 / 100;
	nNumber[4] = time % 100 / 10;

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntTime = 0; nCntTime < 5; nCntTime++)
	{
		float fShiftWidth = 1.0f / 10;
		m_apNumBer[nCntTime]->SetUV((nNumber[nCntTime] * fShiftWidth), (fShiftWidth + (nNumber[nCntTime] * fShiftWidth)), 0.0f, 1.0f);
	}
}

//=============================================================================
// ���W�ݒ菈��
//=============================================================================
void CTime::SetPos(D3DXVECTOR3 pos)
{
	//���g�̃T�C�Y���擾
	D3DXVECTOR3 size = GetSize();

	//���W
	m_pos = pos;

	//�^�C���̍��W�ݒ�
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		if (m_apNumBer[nCnt] != nullptr)
		{
			m_apNumBer[nCnt]->SetPos(D3DXVECTOR3((m_pos.x + (nCnt * size.x)) - (m_nDigit * size.x / 2) + (size.x / 2), m_pos.y, m_pos.z));
		}
	}
}

//=============================================================================
//�^�C�����Z
//=============================================================================
void CTime::AddTime(int nValue)
{
	SetTime((int)(timeGetTime() - m_nTime));
}

//=============================================================================
//�^�C���̏����擾
//=============================================================================
int CTime::GetTime()
{
	return m_nTime;
}