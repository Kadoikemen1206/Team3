//=============================================================================
//
// �v���C���[���� [player.h]
// Author : KADO TAKUMA
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "motion_model3D.h"

//=============================================================================
// �O����`
//=============================================================================
class CShadow;
class CParticle;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CPlayer : public CMotionModel3D
{
public:
	static const float SPEED_POWER;
	static const float JUMP_POWER;
	static const float GRAVITY_POWER;

public:
	//-------------------------------------------------------------------------
	// �񋓌^
	//-------------------------------------------------------------------------
	enum EPLAYER
	{
		EPLAYER_NONE = 0,
		EPLAYER_1P,
		EPLAYER_2P,
		EPLAYER_MAX
	};

	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CPlayer(int nPriority = PRIORITY_LEVEL3);
	~CPlayer() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;							// ����������
	void Update() override;								// �X�V����
	void Respawn(D3DXVECTOR3 &pos);						// ���X�|�[������

	// Setter
	void SetType(EPLAYER type);							// �^�C�v�ݒ菈��
	void SetSpeed(float speed);							// �v���C���[�ړ��X�s�[�h�ݒ菈��

	// Getter
	EPLAYER GetPlayerType(void) { return m_nType; }		// �v���C���[�^�C�v�擾����

	static CPlayer *Create(EPLAYER type, const D3DXVECTOR3 pos, int nPriority);	// ��������

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_move;					// �v���C���[�̈ړ���
	D3DXVECTOR3 m_rotDest;				// �ړI�̊p�x
	D3DXVECTOR3 m_posOld;				// �O��̈ʒu
	EPLAYER m_nType;					// 1P��2P�̃^�C�v����
	int m_nSmokeCnt;					// �X���[�N�̏��
	float m_nSpeed;						// �X�s�[�h
	bool m_bJumpFlag;					// �W�����v�������ǂ����̃t���O
	bool m_bIsLanding;					// ���f���Ƃ̓����蔻��t���O(���E,��,��O)
	bool m_bIsLandingUp;				// ���f���Ƃ̓����蔻��t���O(�㑤)

	int m_moutionType;

	CParticle *m_pParticle;				// �p�[�e�B�N���̃|�C���^
};
#endif