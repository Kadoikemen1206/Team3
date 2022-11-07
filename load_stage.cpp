//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "load_stage.h"
#include "file.h"
#include "objectX.h"
#include "application.h"
#include "objectX_group.h"

CLoadStage::CLoadStage()
{
}

CLoadStage::~CLoadStage()
{
}

//-----------------------------------------------------------------------------
// ステージの読込み
//-----------------------------------------------------------------------------
void CLoadStage::LoadAll(const D3DXVECTOR3& inPos)
{
	nlohmann::json list = LoadJsonStage(L"Data/FILE/stage.json");

	int size = (int)list["STAGE"].size();

	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(list["STAGE"][i]["POS"][0], list["STAGE"][i]["POS"][1], list["STAGE"][i]["POS"][2]);
		pos += inPos;
		CObjectX* objectX = CObjectX::Create(pos, CObject::PRIORITY_LEVEL3);

		// 角度の設定
		D3DXVECTOR3 rot = D3DXVECTOR3(list["STAGE"][i]["ROT"][0], list["STAGE"][i]["ROT"][1], list["STAGE"][i]["ROT"][2]);
		objectX->SetRot(rot);

		bool collision = list["STAGE"][i]["COLLISION"] == "TRUE";
		objectX->SetCollisionFlag(collision);

		// モデルの設定
		std::string tag = list["STAGE"][i]["MODEL"];
		objectX->LoadModel(tag.c_str());

		// 位置の再計算
		objectX->CalculationVtx();
	}
}
