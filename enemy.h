//=============================================================================
//
// �G���� [enemy.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once


// �}�N����`
#define ENEMY_TEXTURE01			_T("data/TEXTURE/��heart02m.png")	// �摜
#define ENEMY_TEXTURE02			_T("data/TEXTURE/��heart03m.png")	// �摜
#define ENEMY_TEXTURE03			_T("data/TEXTURE/��heart04m.png")	// �摜
#define ENEMY_TEXTURE04			_T("data/TEXTURE/��heart05m.png")	// �摜
#define ENEMY_TEXTURE05			_T("data/TEXTURE/��heart06m.png")	// �摜
#define ENEMY_TEXTURE06			_T("data/TEXTURE/��heart07m.png")	// �摜
#define ENEMY_TEXTURE07			_T("data/TEXTURE/��heart08m.png")	// �摜
#define ENEMY_TEXTURE08			_T("data/TEXTURE/��heart09m.png")	// �摜
#define ENEMY_TEXTURE09			_T("data/TEXTURE/��heart10m.png")	// �摜
#define ENEMY_TEXTURE10			_T("data/TEXTURE/��dia02m.png")		// �摜
#define ENEMY_TEXTURE11			_T("data/TEXTURE/��dia03m.png")		// �摜
#define ENEMY_TEXTURE12			_T("data/TEXTURE/��dia04m.png")		// �摜
#define ENEMY_TEXTURE13			_T("data/TEXTURE/��dia05m.png")		// �摜
#define ENEMY_TEXTURE14			_T("data/TEXTURE/��dia06m.png")		// �摜
#define ENEMY_TEXTURE15			_T("data/TEXTURE/��dia07m.png")		// �摜
#define ENEMY_TEXTURE16			_T("data/TEXTURE/��dia08m.png")		// �摜
#define ENEMY_TEXTURE17			_T("data/TEXTURE/��dia09m.png")		// �摜
#define ENEMY_TEXTURE18			_T("data/TEXTURE/��dia10m.png")		// �摜
#define ENEMY_TEXTURE19			_T("data/TEXTURE/��club02m.png")	// �摜
#define ENEMY_TEXTURE20			_T("data/TEXTURE/��club03m.png")	// �摜
#define ENEMY_TEXTURE21			_T("data/TEXTURE/��club04m.png")	// �摜
#define ENEMY_TEXTURE22			_T("data/TEXTURE/��club05m.png")	// �摜
#define ENEMY_TEXTURE23			_T("data/TEXTURE/��club06m.png")	// �摜
#define ENEMY_TEXTURE24			_T("data/TEXTURE/��club07m.png")	// �摜
#define ENEMY_TEXTURE25			_T("data/TEXTURE/��club08m.png")	// �摜
#define ENEMY_TEXTURE26			_T("data/TEXTURE/��club09m.png")	// �摜
#define ENEMY_TEXTURE27			_T("data/TEXTURE/��club10m.png")	// �摜
#define ENEMY_TEXTURE28			_T("data/TEXTURE/��spade02m.png")	// �摜
#define ENEMY_TEXTURE29			_T("data/TEXTURE/��spade03m.png")	// �摜
#define ENEMY_TEXTURE30			_T("data/TEXTURE/��spade04m.png")	// �摜
#define ENEMY_TEXTURE31			_T("data/TEXTURE/��spade05m.png")	// �摜
#define ENEMY_TEXTURE32			_T("data/TEXTURE/��spade06m.png")	// �摜
#define ENEMY_TEXTURE33			_T("data/TEXTURE/��spade07m.png")	// �摜
#define ENEMY_TEXTURE34			_T("data/TEXTURE/��spade08m.png")	// �摜
#define ENEMY_TEXTURE35			_T("data/TEXTURE/��spade09m.png")	// �摜
#define ENEMY_TEXTURE36			_T("data/TEXTURE/��spade10m.png")	// �摜
#define ENEMY_TEXTURE_SIZE_X	(100/2)		// �e�N�X�`���T�C�Y
#define ENEMY_TEXTURE_SIZE_Y	(100/2)		// ����

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(2)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ENEMY_TIME_ANIMATION			(10)		// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY_MAX						(36)		// �G�̍ő吔
#define ENEMY_Y_MAX						(400)		//�G�l�~�[��Y���W�ő�l
#define	ENEMY_ROT_CNT_MAX				(30)		// 30�t���[���̉�]


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		fall;						// ������
	bool			rotflag;					// ��]�t���O�@	true:���@false:�E
	int				rot_cnt;					// ���t���[����]���Ă��邩
	int				rot_cnt_max;				// ���t���[����]���Ă��邩
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x
} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);


