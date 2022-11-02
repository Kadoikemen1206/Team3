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

//=============================================================================
// �O����`
//=============================================================================

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

	void ConstOperate(int barrage, int rotate) override;			// ���̑���(�A�ŁA��])
	D3DXVECTOR3 BarrageMoveWall(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);	// �A�łœ����ǂ̏���
	D3DXVECTOR3 AlternateMoveWal(D3DXVECTOR3 ObstaclePos, D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);	// ���ݘA�łœ����ǂ̏���
	bool PlayerGoal(D3DXVECTOR3 ObstaclePos , D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos, D3DXVECTOR3 ObstacleMove);				// �v���C���[���S�[���������̏���

	static CObstacle *Create(const D3DXVECTOR3 pos, GIMMICKTYPE gimmicktype,SHAPETYPE shapetype, int nPriority);			// ��������

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	int m_nTriggerCount1;			// �L�[����������
	int m_nTriggerCount2;			// �L�[����������
	int m_ArrowRand;				// ���̎�ރ����_��

	bool m_ArrowRandFlag;			// ���̎�ރ����_���t���O
	bool m_ArrowFlag;				// ���̃t���O
	bool m_nAlternateFlag;			// ���݂ɃL�[�������Ă��邩
	bool PlayerGoalFlag;			// �v���C���[���S�[��������
};
#endif
