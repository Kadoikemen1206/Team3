//=============================================================================
//
// �I�u�W�F�N�gX���� [objectX.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "main.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectX::CObjectX(int nPriority) :
	CObject(nPriority),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectX::~CObjectX()
{
	////�o�b�t�@����������Ă��畁�ʂɒʂ�(NULL�`�F�b�N)
	//assert(m_pVtxBuff == nullptr);
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObjectX::Init()
{
	//���f���̓ǂݍ���
	LoadModel("Data\\MODEL\\AstroBot.x");

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I��
//=============================================================================
void CObjectX::Uninit()
{
	//	���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//	�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObjectX::Update()
{
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObjectX::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//(���s��ړ��֐�(��1������x,y,z�����̈ړ��s����쐬))
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	Projection();

	//���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��͐ݒ�֐�
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ��������
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObjectX *pObjectX = nullptr;

	//�C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//�|�C���^�����݂�������s
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetSize(D3DXVECTOR3(100.0f, 100.0f, 50.0f));
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObjectX;
}

//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(aFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_NumMat,
		&m_pMesh);
}

//=============================================================================
// ���s���e����
//=============================================================================
void CObjectX::Projection(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDivice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	//�ϐ��錾
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(1.0f, -0.5f, 0.5f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow,&vecLight, &planeField);

	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		Material = pMat[nCntMat].MatD3D;

		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Material);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
