//=============================================================================
//
// �M�~�b�N�̊�Տ��� [gimmick.h]
// Author : saito shian
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"

//=============================================================================
// �O����`
//=============================================================================

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CGimmick : public CObjectX
{
public:
	//-------------------------------------------------------------------------
	// �M�~�b�N�̃^�C�v
	//-------------------------------------------------------------------------
	enum GIMMICKTYPE
	{
		GIMMICKTYPE_NONE = 0,
		GIMMICKTYPE_BARRAGEMOVEWALL,		// �A�łœ�����
		GIMMICKTYPE_ALTERNATEMOVEWALL,		// ���݂ɘA�łœ�����
		GIMMICKTYPE_SHAPE,					// �}�`���ăM�~�b�N
		GIMMICKTYPE_GOAL,					// �S�[��
		GIMMICKTYPE_MAX
	};
	//-------------------------------------------------------------------------
	// �}�`�̃^�C�v
	//-------------------------------------------------------------------------
	enum SHAPETYPE
	{
		SHAPETYPE_NONE = 0,
		SHAPETYPE_CIRCLE,				// �~�`
		SHAPETYPE_AQUARE,				// �l�p�`
		SHAPETYPE_TRIANGLE,				// �O�p�`
		SHAPETYPE_MAX
	};
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CGimmick(int nPriority = PRIORITY_LEVEL3);
	~CGimmick() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��

	GIMMICKTYPE GetGimmickType(void) { return m_GimmickType; }	// �M�~�b�N�̎�ނ̎擾
	void SetGimmickType(GIMMICKTYPE type);						// �M�~�b�N�̎�ނ̐ݒ�

	SHAPETYPE GetShapeType(void) { return m_ShapeType; }	// �}�`�̎�ނ̎擾
	void SetShapeType(SHAPETYPE type);						// �}�`�̎�ނ̐ݒ�

	D3DXVECTOR3 GetArea() { return m_Area; }					// �M�~�b�N�̃G���A�擾����

	virtual void ConstOperate(int barrage,int rotate) = 0;		// ���̑���(�A�ŁA��])

	static bool GetCompletion1P();			// ������������m�点��
	static bool GetCompletion2P();			// ������������m�点��
	static void SetCompletion1P(bool flag);	// 1P��������������ݒ�
	static void SetCompletion2P(bool flag);	// 2P��������������ݒ�

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_Pos;				// �M�~�b�N�̈ʒu
	GIMMICKTYPE m_GimmickType;		// �M�~�b�N�̎��
	SHAPETYPE m_ShapeType;			// �}�`�̎��
	static bool m_Completion1P;		// 1P�������������ۂ��t���O
	static bool m_Completion2P;		// 2P�������������ۂ��t���O
	static D3DXVECTOR3 m_Area;		// �M�~�b�N�͈̔�
};
#endif
