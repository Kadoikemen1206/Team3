//=============================================================================
//
// 2D�I�u�W�F�N�g���� [object2d.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �}�N����`
//=============================================================================
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//=============================================================================
// �\���̒�`
//=============================================================================
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
};

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObject2D : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObject2D(int nPriority = PRIORITY_LEVEL3);
	~CObject2D() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;									// ����������
	void Uninit() override;										// �I������						
	void Update() override;										// �X�V����
	void Draw() override;										// �`�揈��
	void VtxUpdate() override;									// ���_���W�X�V����
	void SetPos(D3DXVECTOR3 pos) override;						// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size) override;					// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move) override;					// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col) override;						// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) override;						// �����ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �h���̃e�N�X�`���|�C���^��e�̃e�N�X�`���|�C���^�ɑ�����鏈��
	void SetUV(float x_1, float x_2, float y_1, float y_2);		// �e�N�X�`�����W�X�V����
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			// ���W�擾����
	D3DXVECTOR3 GetSize(void) override { return m_size; }		// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) override { return m_move; }		// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			// �����擾����
	D3DXCOLOR GetCol(void) override { return m_col; }			// �F�擾����
	static CObject2D *Create(D3DXVECTOR3 pos, int nPriority);	// ��������

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_col;						// �F
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �p�x
	EObjType m_type;						// �I�u�W�F�N�g�̃^�C�v
};

#endif