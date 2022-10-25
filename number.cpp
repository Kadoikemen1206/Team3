#include "object2d.h"
#include "number.h"
#include "renderer.h"
#include "application.h"
#include <assert.h>

LPDIRECT3DTEXTURE9 CNumber::m_pTexture = nullptr;

CNumber::CNumber()
{

}

CNumber::~CNumber()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CNumber::Init()
{
	CObject2D::Init();

	////�e�N�X�`���̓ǂݍ���
	//LoadTexture("Data\\TEXTURE\\number000.png");

	//���_�J���[�̐ݒ�
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��

	BindTexture(m_pTexture);

	////�e�N�X�`�����W������
	//float fShiftWidth = 1.0f / 10;
	//CObject2D::SetUV((m_nPattrenAnim * fShiftWidth), (fShiftWidth + (m_nPattrenAnim * fShiftWidth)), 0.0f, 1.0f);

	return S_OK;
}

void CNumber::Draw()
{
	//�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//=============================================================================
//���������̐���
//=============================================================================
CNumber *CNumber::Create(const D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber = nullptr;

	pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->Init();
		pNumber->SetSize(size);
		pNumber->SetPos(pos);
	}
	else
	{
		assert(false);
	}
	return pNumber;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CNumber::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���*
	D3DXCreateTextureFromFile(pDevice,
		"Data\\TEXTURE\\number000.png",
		&m_pTexture);

	return S_OK;
}

void CNumber::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
