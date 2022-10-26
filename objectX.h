//=============================================================================
//
// �I�u�W�F�N�gX���� [objectX.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObjectX : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObjectX(int nPriority = PRIORITY_LEVEL3);
	~CObjectX() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// ����������
	void Uninit() override;										// �I������	
	void Update() override;										// �X�V����
	void Draw() override;										// �`�揈��
	void VtxUpdate() override {};								// ���_���W�X�V����
	void SetPos(D3DXVECTOR3 pos) override;						// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size) override;					// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move) override;					// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col) override;						// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) override;						// �����ݒ菈��
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// ���W�擾����
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// �����擾����
	D3DXCOLOR GetCol(void) override { return m_col; }			// �F�擾����

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);	// ��������
	void LoadModel(const char *aFileName);						// ���f���̓ǂݍ��ݏ���
	void Projection(void);										// ���s���e����
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);	// �����蔻��
	//void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 PosOld);	// �����蔻��
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);							// ���_�ő�l�ݒ菈��
	void SetMinVtx(D3DXVECTOR3 Minvtx);							// ���_�ŏ��l�ݒ菈��
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }			// ���_�ő�l�擾����
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }			// ���_�ŏ��l�擾����

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_pos;					// ���W
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// ���W
	D3DXVECTOR3 m_move;					// �p�x
	D3DXVECTOR3 m_MinVtx;				// ���f���̒��_�ŏ��l
	D3DXVECTOR3 m_MaxVtx;				// ���f���̒��_�ő�l
	D3DXCOLOR m_col;					// �F
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD m_NumMat;						// �}�e���A�����̐�
};

#endif