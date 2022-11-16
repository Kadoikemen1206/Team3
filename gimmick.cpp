//=============================================================================
//
// �M�~�b�N���� [gimmick.cpp]
// Author : saito shian
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <assert.h>
#include "application.h"
#include "main.h"
#include "objectX.h"
#include "gimmick.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGimmick::CGimmick(int nPriority) 
{
	// �����o�ϐ��̃N���A
	m_GimmickType = GIMMICKTYPE_NONE;
	m_Pos = {};
	m_Completion = false;
	m_pHitPlayer = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGimmick::~CGimmick()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGimmick::Init()
{
	// ObjectX�̏���������
	CObjectX::Init();

	// ���f���^�C�v
	SetType(OBJTYPE_GIMMICK);

	//���f���̃��[�h
	LoadModel("TRIANGLE");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGimmick::Uninit()
{
	// ObjectX�̏I������
	CObjectX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGimmick::Update()
{
	// ObjectX�̍X�V����
	CObjectX::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGimmick::Draw()
{
	// ObjectX�̕`�揈��
	CObjectX::Draw();
}

//=============================================================================
// �M�~�b�N�̎�ނ̐ݒ菈��
//=============================================================================
void CGimmick::SetGimmickType(GIMMICKTYPE type)
{
	m_GimmickType = type;
}

//=============================================================================
// �����������ǂ����̔���
//=============================================================================
bool CGimmick::Collision(CPlayer* inPlayer)
{
	if (inPlayer == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 playerPos = inPlayer->GetPos();		// �w�肵���v���C���[��Pos�擾
	D3DXVECTOR3 thisPos = GetPos();					// �M�~�b�N��Pos�擾

	// �M�~�b�N�͈̔�
	if (((thisPos.x + 150.0f) >= playerPos.x) && ((thisPos.z + 150.0f) >= playerPos.z)
		&& ((thisPos.x - 150.0f) <= playerPos.x) && ((thisPos.z - 150.0f) <= playerPos.z))
	{// �v���C���[�𓮂����Ȃ��悤�ɂ���t���O��L���ɂ���
		m_pHitPlayer = inPlayer;
		return true;
	}

	return false;
}

//=============================================================================
// �M�~�b�N�ɓ����������ǂ����̔���
//=============================================================================
bool CGimmick::CollisionGimmick(CPlayer* Player)
{
	if (Player == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 PlayerPos = Player->GetPos();	// �w�肵���v���C���[��Pos�擾
	D3DXVECTOR3 thisPos = GetPos();				// �M�~�b�N��Pos�擾
	D3DXVECTOR3 thisSize = GetSize();			// �M�~�b�N��Size�擾

	// �M�~�b�N�͈̔�
	if (((thisPos.x + thisSize.x - 10.0f) >= PlayerPos.x) && ((thisPos.z + thisSize.z - 10.0f) >= PlayerPos.z)
		&& ((thisPos.x - thisSize.x + 10.0f) <= PlayerPos.x) && ((thisPos.z - thisSize.z + 10.0f) <= PlayerPos.z))
	{// �v���C���[�𓮂����Ȃ��悤�ɂ���t���O��L���ɂ���
		m_pHitPlayer = Player;
		return true;
	}

	return false;
}
