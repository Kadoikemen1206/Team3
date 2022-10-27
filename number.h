#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "object2d.h"

class CNumber : public CObject2D
{
public:
	CNumber();
	~CNumber()override;

	HRESULT Init()override;
	void Draw() override;									// •`‰æˆ—
	static void Unload();

	static CNumber *Create(const D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
};

#endif