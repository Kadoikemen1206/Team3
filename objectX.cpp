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
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(OBJTYPE_MODEL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObjectX::Init()
{
	//���f���̓ǂݍ���
	LoadModel("Data\\MODEL\\Box.x");

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


	int nNumVtx;		//���_���ۑ��p�ϐ�
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

						//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < m_MinVtx.x)
		{//�ŏ��l
			m_MinVtx.x = vtx.x;
		}
		if (vtx.x > m_MaxVtx.x)
		{//�ő�l
			m_MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < m_MinVtx.y)
		{//�ŏ��l
			m_MinVtx.y = vtx.y;
		}
		if (vtx.y > m_MaxVtx.y)
		{//�ő�l
			m_MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < m_MinVtx.z)
		{//�ŏ��l
			m_MinVtx.z = vtx.z;
		}
		if (vtx.z > m_MaxVtx.z)
		{//�ő�l
			m_MaxVtx.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^�i�߂�
		pVtxBuff += sizeFVF;
	}

	// �T�C�Y�ݒ�
	m_size = D3DXVECTOR3((m_MaxVtx.x - m_MinVtx.x), (m_MaxVtx.y - m_MinVtx.y), (m_MaxVtx.z - m_MinVtx.z));

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
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
	pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
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

//=============================================================================
// �����蔻��
//=============================================================================
void CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	//���f���̍��������蔻��
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f))
	{
		pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
	}
	//���f���̉E�������蔻��
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f))
	{
		pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
	}
	//���f���̉��������蔻��
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f))
	{
		pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
	}
	//���f���̎�O�������蔻��
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f))
	{
		pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
	}
}

//void CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 PosOld)
//{
//	// �^�[�Q�b�g�̈ʒu���擾
//	D3DXVECTOR3 TargetPos = *pPos;
//
//	//���_���W
//	D3DXVECTOR3 vtx[4] =
//	{
//		D3DXVECTOR3(m_pos.x + m_MinVtx.x,0.0f,m_pos.z + m_MaxVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MaxVtx.x,0.0f,m_pos.z + m_MaxVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MaxVtx.x,0.0f,m_pos.z + m_MinVtx.z),
//		D3DXVECTOR3(m_pos.x + m_MinVtx.x,0.0f,m_pos.z + m_MinVtx.z)
//	};
//
//	//�x�N�g��
//	D3DXVECTOR3 Vec [4] =
//	{
//		vtx[1] - vtx[0],
//		vtx[2] - vtx[1],
//		vtx[3] - vtx[2],
//		vtx[0] - vtx[3]
//	};
//
//	//�^�[�Q�b�g�܂ł̃x�N�g��
//	D3DXVECTOR3 VecPos[4] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
//
//	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//	{
//		VecPos[nCntVtx] = TargetPos - vtx[nCntVtx];
//	}
//
//	// �O��
//	float fCalculation[4] = { 0.0f };
//	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//	{
//		fCalculation[nCntVtx] = Vec[nCntVtx].x * VecPos[nCntVtx].z - VecPos[nCntVtx].x * Vec[nCntVtx].z;
//	}
//
//	//�v���C���[�̈ʒu���S��-��+
//	if (fCalculation[0] < 0.0f
//		&& fCalculation[1] < 0.0f
//		&& fCalculation[2] < 0.0f
//		&& fCalculation[3] < 0.0f)
//	{
//		// �ړI�̒��_
//		D3DXVECTOR3 TargetVtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		// �ړI�̃x�N�g��
//		D3DXVECTOR3 TargetVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//�^�[�Q�b�g�̉ߋ��ʒu�܂ł̃x�N�g��
//		D3DXVECTOR3 VecPosOld[4] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			VecPosOld[nCntVtx] = PosOld - vtx[nCntVtx];
//		}
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			fCalculation[nCntVtx] = Vec[nCntVtx].x * VecPosOld[nCntVtx].z - VecPosOld[nCntVtx].x * Vec[nCntVtx].z;
//		}
//
//		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
//		{
//			if (fCalculation[nCntVtx] > 0.0f)
//			{
//				TargetVec = Vec[nCntVtx];
//				TargetVtx = vtx[nCntVtx];
//			}
//		}
//
//		// �ړ��x�N�g��
//		D3DXVECTOR3 moveVec = TargetPos - PosOld;
//		D3DXVECTOR3 TargetVtxVec = TargetVtx - PosOld;
//		D3DXVECTOR3 TargetVecNor = TargetVec;
//		D3DXVec3Normalize(&TargetVecNor, &TargetVecNor);
//		float fLength = (moveVec.x * TargetVtxVec.z - TargetVtxVec.x * moveVec.z) / (TargetVecNor.x * moveVec.z - moveVec.x * TargetVecNor.z);
//
//		D3DXVECTOR3 pos = TargetVtx + (TargetVec * fLength);
//
//		*pPos = PosOld;
//	}
//}

//=============================================================================
// ���_�ő�l�ݒ菈��
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// ���_�ŏ��l�ݒ菈��
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
