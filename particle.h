//=============================================================================
// particle.h
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	explicit CParticle(int nPriority = PRIORITY_LEVEL3);
	~CParticle() override;

	HRESULT Init() override;			// ����������
	void Update() override;				// �X�V����
	void DetailSetting();

	//�Z�b�^�[
	void SetDelay(int time) { m_nDelay = time; }
	void SetGravity(bool set) { m_bGravity = set; }
	void SetGravity(bool set, float value) { m_bGravity = set, m_fFallSpeed = value; }
	void SetFade(bool set) { m_bFade = set; }
	void SetRotation(bool set, float value) { m_bRotate = set, m_fRotateSpeed = value; }
	void SetScaling(bool set) { m_bScaling = set; }
	void SetTransitionColor(bool set, D3DXCOLOR col) { m_bTransition = set, m_destCol = col; }

	//�Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, int nPriority);    // ��������

private:
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_beginPos;		// �J�n���̈ʒu
	D3DXVECTOR3 m_posOld;		// �O��̈ʒu
	D3DXCOLOR m_col;			// �F
	D3DXCOLOR m_destCol;		// �ړI�̐F
	int m_nTime;				// ����
	int m_nDelay;				// �x��
	int m_nDestroyTime;			// �G�t�F�N�g����������
	float m_fSpeed;				// �X�s�[�h
	float m_fFadeValue;			// �G�t�F�N�g���t�F�[�h���鐔�l
	float m_fFallSpeed;			// �������x
	float m_fRotateSpeed;		// ��]���x
	float m_fScalingValue;		// �g�k���鐔�l
	bool m_bGravity;			// ���ɗ����Ă������ǂ���
	bool m_bFade;				// �G�t�F�N�g�̃t�F�[�h���g�p���邩�ǂ���
	bool m_bRotate;				// ��]�����邩�ǂ���
	bool m_bScaling;			// �g�k���s�����ǂ���
	bool m_bTransition;			// �F�̕ω������邩�ǂ���
};
#endif