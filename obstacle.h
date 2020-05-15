//=============================================================================
//
// �I�u�W�F�N�g���� [obstacle.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

// �}�N����`
#define THORN_TEXTURE01			_T("data/TEXTURE/��thorn_001.png")	// �摜
#define BRICK_TEXTURE01			_T("data/TEXTURE/��brick_001.png")	// �摜
#define CAKE_TEXTURE01			_T("data/TEXTURE/��cake_001.png")	// �摜
#define TEA_TEXTURE01			_T("data/TEXTURE/��tea_001.png")	// �摜
#define COOKIE_TEXTURE01		_T("data/TEXTURE/��cookie_001.png")	// �摜
#define GOAL_TEXTURE01			_T("data/TEXTURE/��goal_001.png")	// �摜

#define THORN_TEXTURE_SIZE_X	(100/2)		// �e�N�X�`���T�C�Y
#define THORN_TEXTURE_SIZE_Y	(60/2)		// ����
#define BRICK_TEXTURE_SIZE_X	(150/2)		// �e�N�X�`���T�C�Y
#define BRICK_TEXTURE_SIZE_Y	(30/2)		// ����
#define ITEM_TEXTURE_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define ITEM_TEXTURE_SIZE_Y	(50/2)		// ����
#define GOAL_TEXTURE_SIZE_X	(500/2)		// �e�N�X�`���T�C�Y
#define GOAL_TEXTURE_SIZE_Y	(500/2)		// ����


#define OBSTACLE_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define OBSTACLE_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define OBSTACLE_TIME_ANIMATION			(40)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define THORN_MAX						(10) // ���΂�̍ő吔
#define BRICK_MAX						(30) // �u���b�N�i�����K�j�̍ő吔
#define OBSTACLE_MAX					(20)//��Q���̍ő吔
#define CAKE_MAX						(3) // �P�[�L�̍ő吔
#define TEA_MAX							(5) // �g���̍ő吔
#define COOKIE_MAX						(5)//�N�b�L�[�̍ő吔
#define GOAL_MAX						(1)//�S�[���̍ő吔

#define CAKE_SCORE						(5) // �P�[�L�̃X�R�A�{��
#define TEA_SCORE						(2) // �g���̃X�R�A�{��

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// ���΂�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	bool			s_cnt;						//�X�R�A�J�E���g���� true:���J�E���g�@false:�J�E���g��
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} THORN;

typedef struct	// �u���b�N�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	bool			h_cnt;						//�q�b�g�J�E���g���� true:���J�E���g�@false:�J�E���g��
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} BRICK;

typedef struct	// �P�[�L�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	bool			b_hitcnt;					//�q�b�g�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			s_cnt;						//�X�R�A�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			scale_plus;					//true:�g�咆  false:�k����

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		fall;						// ������

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				scale_cnt;					// �g��k���J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} CAKE;

typedef struct	// �g���\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	bool			b_hitcnt;						//�q�b�g�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			s_cnt;						//�X�R�A�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			scale_plus;					//true:�g�咆  false:�k����

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		fall;						// ������

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				scale_cnt;					// �g��k���J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} TEA;

typedef struct	// �N�b�L�[�\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	bool			b_hitcnt;						//�q�b�g�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			h_cnt;						//�X�R�A�J�E���g���� true:���J�E���g�@false:�J�E���g��
	bool			scale_plus;					//true:�g�咆  false:�k����

	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	D3DXVECTOR3		fall;						// ������

	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int				scale_cnt;					// �g��k���J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} COOKIE;

typedef struct	// �S�[���\����
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// �e�N�X�`���ւ̃|���S��
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �I�u�W�F�N�g�̔��a
	float			BaseAngle;					// �I�u�W�F�N�g�̊p�x

} GOAL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitObstacle(int type);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);
THORN *GetThorn(void);
BRICK *GetBrick(void);
CAKE *GetCake(void);
TEA *GetTea(void);
COOKIE *GetCookie(void);
GOAL *GetGoal(void);


