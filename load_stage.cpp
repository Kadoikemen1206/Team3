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

void CLoadStage::LoadAll(const D3DXVECTOR3& inPos)
{
	nlohmann::json list = LoadJsonStage(L"Data/FILE/stage.json");

	int size = (int)list["STAGE"].size();

	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(list["STAGE"][i]["POS"][0], list["STAGE"][i]["POS"][1], list["STAGE"][i]["POS"][2]);
		pos += inPos;
		CObjectX* objectX = CObjectX::Create(pos, CObject::PRIORITY_STAGE);

		// 角度の設定
		D3DXVECTOR3 rot = D3DXVECTOR3(list["STAGE"][i]["ROT"][0], list["STAGE"][i]["ROT"][1], list["STAGE"][i]["ROT"][2]);
		objectX->SetRot(rot);

		// モデルの設定
		std::string tag = list["STAGE"][i]["MODEL"];
		objectX->LoadModel(tag.c_str());
	}
}

void CLoadStage::SaveAll()
{
	//D3DXVECTOR3をvector<float>に変更する
	auto Vector3ToVectorFloat = [](D3DXVECTOR3 inVector)->std::vector<float>
	{
		return{ inVector.x, inVector.y, inVector.z };
	};

	nlohmann::json saveFile;//リストの生成

	CObjectX *pObject = (CObjectX*)CObject::GetTop(CObject::PRIORITY_STAGE);

	int count = 0;;
	while (pObject != nullptr)
	{
		//pNextの保存
		CObjectX *pObjectNext = (CObjectX*)pObject->GetNext();

		std::string tag = CApplication::GetObjectXGroup()->GetTagName(pObject->GetModelIndex());
		saveFile["STAGE"][count]["MODEL"] = tag;
		saveFile["STAGE"][count]["POS"] = Vector3ToVectorFloat(pObject->GetPos());
		saveFile["STAGE"][count]["ROT"] = Vector3ToVectorFloat(pObject->GetRot());

		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
		count++;
	}

	SaveJson(saveFile, "Data/FILE/stage.json");
}
