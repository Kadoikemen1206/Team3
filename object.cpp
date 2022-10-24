//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <assert.h>
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop = nullptr;
CObject *CObject::m_pCurrent = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(int nPriority /* = PRIORITY_LEVEL0 */) :
	m_pNext(nullptr),
	m_pPrev(nullptr),
	m_bDeath(false)
{
	//�I�u�W�F�N�g(�������g)���A���X�g�ɒǉ�
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
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// �S�ẴC���X�^���X�̏I������
//=============================================================================
void CObject::UninitAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject)
	{
		pObject->Release();
	}

	pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->m_pNext;	//Update()�ō폜�����ƁApNext��������̂Ŏ��O�ɕۑ����Ă���

		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}

		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//=============================================================================
// �S�ẴC���X�^���X�̍X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == false)
		{
			pObject->Update();
		}

		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}

	pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}
		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//=============================================================================
// �S�ẴC���X�^���X�̕`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->m_pNext;	//Update()�ō폜�����ƁApNext��������̂Ŏ��O�ɕۑ����Ă���

		if (pObject->m_bDeath == false)
		{
			//�`�揈���̊֐��Ăяo��
			pObject->Draw();
		}

		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//=============================================================================
// �I�u�W�F�N�g�j������
//=============================================================================
void CObject::Death(void)
{
	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă���Ƃ�
	if (m_pNext != nullptr)
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//�������g��m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;

			//�������g��m_pPrev������m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�������g��m_pNext��擪�ɑ��
			m_pTop = this->m_pNext;

			//�������g��m_pPrev�����̃I�u�W�F�N�g��m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă��Ȃ��Ƃ�
	else
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//����m_pPrev��nullptr����
			m_pCurrent = this->m_pPrev;

			//����m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�擪�̃I�u�W�F�N�g��nullptr����
			m_pTop = nullptr;

			//���̃I�u�W�F�N�g��nullptr����
			m_pCurrent = nullptr;
		}
	}

	//�I�u�W�F�N�g(�������g)���A�j��
	delete this;
}

//=============================================================================
// �C���X�^���X�̉������
//=============================================================================
void CObject::Release()
{
	m_bDeath = true;
}

//=============================================================================
// ���[�h�ȊO��������j������
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
// �I�u�W�F�N�g�̎��
//=============================================================================
void CObject::SetType(const EObjType type)
{
	m_objType = type;
}

//=============================================================================
// �I�u�W�F�N�g�̃^�C�v��Ԃ�����
//=============================================================================
CObject::EObjType CObject::GetObjType(void)
{
	return m_objType;
}