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

	HRESULT Init() override;			// 初期化処理
	void Update() override;				// 更新処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CParticle *Create(const D3DXVECTOR3 pos, int nPriority);    // 生成処理

private:
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_posOld;				// 前回の位置
	float m_nSpeed;						// スピード
};
#endif