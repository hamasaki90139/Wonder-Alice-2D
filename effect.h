//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

// �}�N����`
#define EFFECT_TEXTURE			_T("data/TEXTURE/��effect_001.png")	// �摜
#define EFFECT_TEXTURE_SIZE_X	(64/2)		// �e�N�X�`���T�C�Y
#define EFFECT_TEXTURE_SIZE_Y	(64/2)		// ����

#define EFFECT_TEXTURE_PATTERN_DIVIDE_X	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define EFFECT_TEXTURE_PATTERN_DIVIDE_Y	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define EFFECT_ANIM_PATTERN_NUM			(EFFECT_TEXTURE_PATTERN_DIVIDE_X*EFFECT_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define EFFECT_TIME_ANIMATION			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define EFFECT_NUM_PARTS 16
#define EFFECT_NUM_EFFECTS 10

enum {
	EFFECT_TYPE_PLAYER,
	EFFECT_TYPE_ENEMY,
	EFFECT_TYPE_ITEM,

};


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�t�F�N�g�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	int				liveTime;

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	bool			isFinish;
}PARTICLE;

typedef struct	// �G�t�F�N�g�\����
{
	int				use;
	int				isEnding;
	bool			isRemoveOnFinish;

	D3DXVECTOR3		pos;						// �|���S���̈ړ���

	int				duration;
	int				elapsed;
	int				numFinish;

	int				effectCount;
	int				emitCounter;

	PARTICLE		pParticle[EFFECT_NUM_PARTS];

}EFFECT;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(float x, float y, int duration, int type);