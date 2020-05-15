//=============================================================================
//
// HP���� [hp.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

// �}�N����`
#define HP_TEXTURE		_T("data/TEXTURE/��hp_001.png")	// �T���v���p�摜
#define MP_TEXTURE		_T("data/TEXTURE/��mp_001.png")	// �T���v���p�摜
#define HP_SIZE_W		(500)		// �e�N�X�`���T�C�Y
#define HP_SIZE_H		(60)		// ����
#define MP_SIZE_W		(180)		// �e�N�X�`���T�C�Y
#define MP_SIZE_H		(20)		// ����
#define HP_POS_X		(0)		// �|���S���̏����ʒuX
#define HP_POS_Y		(0)		// ����
#define MP_POS_X		(10)		// �|���S���̏����ʒuX
#define MP_POS_Y		(60)		// ����
#define HP_MAX			(5)		// �X�R�A�̍ő�l
#define MP_MAX			(6)		//�`���[�W�Q�[�W�̍ő�l
#define MP_UNIT			(6)		//�`���[�W�U���P��ɏ����MP��

#define HP_TEXTURE_PATTERN_DIVIDE_X	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define HP_TEXTURE_PATTERN_DIVIDE_Y	(6)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define HP_ANIM_PATTERN_NUM			(HP_TEXTURE_PATTERN_DIVIDE_X*HP_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define HP_TIME_ANIMATION			(4)			// �A�j���[�V�����̐؂�ւ��J�E���g

#define MP_TEXTURE_PATTERN_DIVIDE_X	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define MP_TEXTURE_PATTERN_DIVIDE_Y	(7)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define MP_ANIM_PATTERN_NUM			(HP_TEXTURE_PATTERN_DIVIDE_X*HP_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define MP_TIME_ANIMATION			(4)			// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
// �A�j���[�V�������ޒ萔(HP)
enum HP_A
{
	HP_0,
	HP_1,
	HP_2,
	HP_3,
	HP_4,
	HP_5
};

// �A�j���[�V�������ޒ萔(MP)
enum MP_A
{
	MP_0,
	MP_1,
	MP_2,
	MP_3,
	MP_4,
	MP_5,
	MP_6
};

typedef struct	// MP�\����
{
	int							mp;				// MP
}MP;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHp(int type);
void UninitHp(void);
void UpdateHp(void);
void DrawHp(void);
void AddHp(int add);
void AddMp(int add);
MP *GetMp(void);

