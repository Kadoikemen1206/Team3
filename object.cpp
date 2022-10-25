//=============================================================================
//
// オブジェクト処理 [object.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <assert.h>
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop = nullptr;
CObject *CObject::m_pCurrent = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject(int nPriority /* = PRIORITY_LEVEL0 */) :
	m_pNext(nullptr),
	m_pPrev(nullptr),
	m_bDeath(false)
{
	//オブジェクト(自分自身)を、リストに追加
	if (m_pTop == nullptr)
	{
		m_pTop = this;
	}
	else if (m_pTop != nullptr)
	{
		m_pCurrent->m_pNext = this;
		this->m_pPrev = m_pCurrent;
	}

	m_pCurrent = this;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// 全てのインスタンスの終了処理
//=============================================================================
void CObject::UninitAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

		pObject->Release();

		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}

	pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}

		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//=============================================================================
// 全てのインスタンスの更新処理
//=============================================================================
void CObject::UpdateAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == false)
		{
			pObject->Update();
		}

		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}

	pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}
		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//=============================================================================
// 全てのインスタンスの描画処理
//=============================================================================
void CObject::DrawAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

		if (pObject->m_bDeath == false)
		{
			//描画処理の関数呼び出し
			pObject->Draw();
		}

		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//=============================================================================
// オブジェクト破棄処理
//=============================================================================
void CObject::Death(void)
{
	//オブジェクトの次に情報が入っているとき
	if (m_pNext != nullptr)
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//自分自身のm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;

			//自分自身のm_pPrevを後ろのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//自分自身のm_pNextを先頭に代入
			m_pTop = this->m_pNext;

			//自分自身のm_pPrevを次のオブジェクトのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//オブジェクトの次に情報が入っていないとき
	else
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//後ろのm_pPrevにnullptrを代入
			m_pCurrent = this->m_pPrev;

			//後ろのm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//先頭のオブジェクトにnullptrを代入
			m_pTop = nullptr;

			//後ろのオブジェクトにnullptrを代入
			m_pCurrent = nullptr;
		}
	}

	//オブジェクト(自分自身)を、破棄
	delete this;
}

//=============================================================================
// インスタンスの解放処理
//=============================================================================
void CObject::Release()
{
	m_bDeath = true;
}

//=============================================================================
// モード以外だったら破棄処理
//=============================================================================
//void CObject::ModeRelease()
//{
//	for (int nPriority = 0; nPriority < PRIORITY_LEVELMAX; nPriority++)
//	{
//		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
//		{
//			if (m_apObject[nPriority][nCnt] != nullptr)
//			{
//				if (m_apObject[nPriority][nCnt]->GetObjType() != OBJTYPE_MODE)
//				{
//					m_apObject[nPriority][nCnt]->Uninit();
//				}
//			}
//		}
//	}
//}

//=============================================================================
// オブジェクトの種類
//=============================================================================
void CObject::SetType(const EObjType type)
{
	m_objType = type;
}

//=============================================================================
// オブジェクトのタイプを返す処理
//=============================================================================
CObject::EObjType CObject::GetObjType(void)
{
	return m_objType;
}