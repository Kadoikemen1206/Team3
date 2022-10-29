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

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CParticle *Create(const D3DXVECTOR3 pos, int nPriority);    // ��������

private:
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_posOld;				// �O��̈ʒu
	float m_nSpeed;						// �X�s�[�h
};
#endif