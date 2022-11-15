//=============================================================================
//
// ��Q������ [obstacle.h]
// Author : saito shian
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "gimmick.h"
#include "player.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObstacle : public CGimmick
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObstacle(int nPriority = PRIORITY_LEVEL3);
	~CObstacle() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��

	void ConstOperate() override;		// ���̑���(�A�ŁA��])

	static CObstacle *Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype,int nPriority);			// ��������

	bool GetCompletion(void) { return m_Completion; }					// �M�~�b�N���N���A���������擾���鏈��
	void SetCompletion(bool bflag) { m_Completion = bflag; }			// �M�~�b�N���N���A�������̐ݒ菈��

	bool GetStopFlag(void) { return m_StopObstacle; }					// ��Q�����~�߂邩�̎擾����
	void SetStopFlag(bool bflag) { m_StopObstacle = bflag; }			// ��Q�����~�߂邩�̐ݒ菈��

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	bool m_Completion;				// Player�������������ۂ��t���O
	bool m_StopObstacle;			// Obstacle�X�g�b�v���邩�̃t���O
};
#endif
