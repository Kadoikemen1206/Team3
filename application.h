//=============================================================================
//
// �}�l�[�W������ [application.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X�̑O����`
//=============================================================================
class CInput;
class CCamera;
class CLight;
class CObjectX;
class CMeshfield;
class CTime;
class CTexture;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CApplication
{
public:

	//=============================================================================
	// �񋓌^
	//=============================================================================
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_TUTORIAL,
		MODE_MAX
	};

	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	CApplication();
	~CApplication();

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer();
	static CInput *GetInputKeyboard();
	static CCamera *GetCamera() { return m_pCamera; }
	static CMeshfield *GetMeshfield() { return m_pMeshField; }
	static CTexture *GetTexture() { return m_pTexture; }

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	static CRenderer *m_pRenderer;
	static CInput *m_pInputKeyboard;
	static MODE m_mode;
	static CObject *m_pMode;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CMeshfield *m_pMeshField;
	static CTime *m_pTime;
	static CTexture *m_pTexture;

	static CObjectX *m_apObject3D[4];
};

#endif