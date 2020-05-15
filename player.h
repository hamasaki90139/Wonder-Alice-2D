//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once


// �}�N����`
#define PLAYER_TEXTURE					_T("data/TEXTURE/��alice_009.png")	// �摜
#define PLAYER_TEXTURE_SIZE_X			(200/2)		// �e�N�X�`���T�C�Y
#define PLAYER_TEXTURE_SIZE_Y			(200/2)		// ����

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(4)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(2)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_TIME_ANIMATION			(10)			// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX						(1)			// �v���C���[�̍ő吔

#define	PLAYER_JUMP_Y					(-15.0f)	// �W�����v�̍���
#define	PLAYER_JUMP_CNT_MAX				(40)		// 40�t���[���̃W�����v����
#define	PLAYER_DMG_CNT_MAX				(60)		// 40�t���[���̃_���[�W�F�\��
#define	PLAYER_DMG_COLOR_MAX			(2)			//�_���[�W�J���[�F��
#define	PLAYER_JUMPMAX					(2)			// �W�����v��

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	bool			dmg;						//true:�_���[�W��^�����@false:�_���[�W��^����ꂽ
	bool			dmgflag;					//�_���[�W���̏����@true:�ԁ@false:�ʏ�
	bool			direction;					//�����@true:�E�@false:���g�p

	D3DXVECTOR3		pos;						// �|���S���̍��W
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	
	bool			jump;						// �W�����v���t���O
	float			jump_y;						// �W�����v�̍���
	int				jump_cnt;					// ���t���[���W�����v���Ă��邩
	int				jump_cnt_max;				// ���t���[���ŃW�����v�����邩
	int				jumppoint;					// �W�����v��
	D3DXVECTOR3		ofs;						// pos�ɑ΂���I�t�Z�b�g���W

	int				dmg_cnt;					//�v���C���[�̃_���[�W�J�E���g
	float			Radius;						// �v���C���[�̔��a

} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);


