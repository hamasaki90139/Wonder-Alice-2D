//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

// �}�N����`
#define BULLET_TEXTURE01			_T("data/TEXTURE/��heart_001.png")	// �摜
#define BULLET_TEXTURE02			_T("data/TEXTURE/��dia_001.png")	// �摜
#define BULLET_TEXTURE03			_T("data/TEXTURE/��club_001.png")	// �摜
#define BULLET_TEXTURE04			_T("data/TEXTURE/��spade_001.png")	// �摜
#define BULLET_TEXTURE_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define BULLET_TEXTURE_SIZE_Y	(50/2)		// ����

#define BULLET_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define BULLET_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define BULLET_ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define BULLET_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET_MAX						(100)	// �o���b�g�̍ő吔
#define BULLET_SPEED					(4.0f)		// �o���b�g�̈ړ��X�s�[�h
#define BULLET_CNT						(4)		//��x�ɔ��˂ł���o���b�g�̐�
#define CHARGE_CNT						(3) //�G�l�~�[3�̂ɂ��`���[�W+1

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureBullet;// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	int				type;						// �e�̎��
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// ���a
	float			BaseAngle;					// �p�x			

} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, int type);
BULLET *GetBullet(void);


