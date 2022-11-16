//=============================================================================
//
// �r���{�[�h�ŃA�C�R���̕\�� [icon.h]
// Author : Tanaka Kouta
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CIcon : public CBillboard
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CIcon(int nPriority = PRIORITY_LEVEL3);
	~CIcon() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��

	//�Z�b�^�[
	void SetPath(std::string path) { m_path = path; }
	void SetDestroy(bool set) { m_bDestroy = set; }
	void SetScaling(bool set) { m_bScaling = set; }
	void SetFade(bool set) { m_bFade = set; }
	void SetScaling(bool set, bool limit) { m_bScaling = set, m_bLimit = limit; }

	static CIcon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, std::string url, int nPriority);    // ����

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_beginScale;		//�ŏ��̑傫��
	std::string m_path;				//�e�N�X�`���̃p�X
	bool m_bScaling;				//�g������邩�ǂ���
	bool m_bFade;					//�t�F�[�h�������邩�ǂ���
	bool m_bLimit;					//��萔�g�傳������k�����邩�ǂ���
	bool m_bDestroy;				//�A�C�R�����������ǂ���
	bool m_bAnim;					//�A�j���[�V���������邩�ǂ���
};

#endif