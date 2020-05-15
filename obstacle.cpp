//=============================================================================
//
// �I�u�W�F�N�g���� [obstacle.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "obstacle.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexThorn(int no);
HRESULT MakeVertexBrick(int no);
HRESULT MakeVertexCake(int no);
HRESULT MakeVertexTea(int no);
HRESULT MakeVertexCookie(int no);
HRESULT MakeVertexGoal(int i);
void SetTextureThorn(int no, int cntPattern);
void SetTextureBrick(int no, int cntPattern);
void SetTextureCake(int no, int cntPattern);
void SetTextureTea(int no, int cntPattern);
void SetTextureCookie(int no, int cntPattern);
void SetTextureGoal(int i, int cntPattern);
void SetVertexThorn(int no);
void SetVertexBrick(int no);
void SetVertexCake(int no);
void SetVertexTea(int no);
void SetVertexCookie(int no);
void SetVertexGoal(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static THORN				thornWk[THORN_MAX];				// ���΂�\����
static BRICK				brickWk[BRICK_MAX];				// �u���b�N�\����
static CAKE					cakeWk[CAKE_MAX];				// �P�[�L�\����
static TEA					teaWk[TEA_MAX];					// �g���\����
static COOKIE				cookieWk[COOKIE_MAX];			// �N�b�L�[�\����
static GOAL					goalWk[GOAL_MAX];				// �S�[���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitObstacle(int type)
{
	srand((unsigned)time(NULL));	//�����_�������l�̏�����
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// ���΂�̏���������
	for (int i = 0; i < THORN_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				THORN_TEXTURE01,										// �t�@�C���̖��O
				&thornWk[i].g_pD3DTextureObstacle);								// �ǂݍ��ރ������̃|�C���^

		}

		thornWk[i].use = true;										// �g�p
		thornWk[i].s_cnt = true;										// ���J�E���g
		thornWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 1650.0f, 440.0f, 0.0f);	// ���W�f�[�^��������
		thornWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);			// �ړ���
		thornWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		thornWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		thornWk[i].CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(THORN_TEXTURE_SIZE_X, THORN_TEXTURE_SIZE_Y);
		thornWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		thornWk[i].BaseAngle = atan2f(THORN_TEXTURE_SIZE_Y, THORN_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		thornWk[i].Texture = thornWk[i].g_pD3DTextureObstacle;

		MakeVertexThorn(i);											// ���_���̍쐬
	}

	// �u���b�N�̏���������
	for (int i = 0; i < BRICK_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				BRICK_TEXTURE01,										// �t�@�C���̖��O
				&brickWk[i].g_pD3DTextureObstacle);								// �ǂݍ��ރ������̃|�C���^

		}

		brickWk[i].use = true;										// �g�p
		brickWk[i].h_cnt = true;									//���J�E���g
		brickWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 1750.0f, ((rand() % (2 + 1) + 2)*100.0f), 0.0f);	// ���W�f�[�^��������
		brickWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);			// �ړ���
		brickWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		brickWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		brickWk[i].CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(BRICK_TEXTURE_SIZE_X, BRICK_TEXTURE_SIZE_Y);
		brickWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		brickWk[i].BaseAngle = atan2f(BRICK_TEXTURE_SIZE_Y, BRICK_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		brickWk[i].Texture = brickWk[i].g_pD3DTextureObstacle;

		MakeVertexBrick(i);											// ���_���̍쐬
	}

	// �P�[�L�̏���������
	for (int i = 0; i < CAKE_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				CAKE_TEXTURE01,										// �t�@�C���̖��O
				&cakeWk[i].g_pD3DTextureObstacle);					// �ǂݍ��ރ������̃|�C���^

		}

		cakeWk[i].use = true;										// �g�p
		cakeWk[i].b_hitcnt = true;									//���J�E���g
		cakeWk[i].s_cnt = true;										//���J�E���g
		cakeWk[i].scale_plus = true;								//�g�咆
		cakeWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 500) + 2500.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// ���W�f�[�^��������
		cakeWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);			// �ړ���
		cakeWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������
		cakeWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		cakeWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		cakeWk[i].CountAnim = 0;									// �A�j���J�E���g��������
		cakeWk[i].scale_cnt = 0;									// �g��k���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		cakeWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		cakeWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		cakeWk[i].Texture = cakeWk[i].g_pD3DTextureObstacle;

		MakeVertexCake(i);											// ���_���̍쐬
	}

	// �g���̏���������
	for (int i = 0; i < TEA_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				TEA_TEXTURE01,										// �t�@�C���̖��O
				&teaWk[i].g_pD3DTextureObstacle);					// �ǂݍ��ރ������̃|�C���^

		}

		teaWk[i].use = true;										// �g�p
		teaWk[i].b_hitcnt = true;									//���J�E���g
		teaWk[i].s_cnt = true;										//���J�E���g
		teaWk[i].scale_plus = true;									//�g�咆
		teaWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 400) + 1500.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// ���W�f�[�^��������
		teaWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);				// �ړ���
		teaWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������
		teaWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		teaWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		teaWk[i].CountAnim = 0;										// �A�j���J�E���g��������
		teaWk[i].scale_cnt = 0;										// �g��k���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		teaWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		teaWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		teaWk[i].Texture = teaWk[i].g_pD3DTextureObstacle;

		MakeVertexTea(i);											// ���_���̍쐬
	}

	// �N�b�L�[�̏���������
	for (int i = 0; i < COOKIE_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				COOKIE_TEXTURE01,									// �t�@�C���̖��O
				&cookieWk[i].g_pD3DTextureObstacle);				// �ǂݍ��ރ������̃|�C���^

		}

		cookieWk[i].use = true;										// �g�p
		cookieWk[i].b_hitcnt = true;								//���J�E���g
		cookieWk[i].h_cnt = true;									//���J�E���g
		cookieWk[i].scale_plus = true;								//�g�咆
		cookieWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 2000.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// ���W�f�[�^��������
		cookieWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);			// �ړ���
		cookieWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ������
		cookieWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		cookieWk[i].PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		cookieWk[i].CountAnim = 0;									// �A�j���J�E���g��������
		cookieWk[i].scale_cnt = 0;									// �g��k���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		cookieWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		cookieWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		cookieWk[i].Texture = cookieWk[i].g_pD3DTextureObstacle;

		MakeVertexCookie(i);											// ���_���̍쐬
	}

	// �S�[���̏���������
	for (int i = 0; i < GOAL_MAX; i++)
	{
		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				GOAL_TEXTURE01,										// �t�@�C���̖��O
				&goalWk[i].g_pD3DTextureObstacle);					// �ǂݍ��ރ������̃|�C���^
		}

		goalWk[i].use = false;										// ���g�p
		goalWk[i].pos = D3DXVECTOR3(1000.0f, 270.0f, 0.0f);			// ���W�f�[�^��������
		goalWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
		goalWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		goalWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		goalWk[i].CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(GOAL_TEXTURE_SIZE_X, GOAL_TEXTURE_SIZE_Y);
		goalWk[i].Radius = D3DXVec2Length(&temp);					// �I�u�W�F�N�g�̔��a��������
		goalWk[i].BaseAngle = atan2f(GOAL_TEXTURE_SIZE_Y, GOAL_TEXTURE_SIZE_X);	// �I�u�W�F�N�g�̊p�x��������
		goalWk[i].Texture = goalWk[i].g_pD3DTextureObstacle;

		MakeVertexGoal(i);											// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitObstacle(void)
{
	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			thornWk[i].g_pD3DTextureObstacle->Release();
			thornWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			brickWk[i].g_pD3DTextureObstacle->Release();
			brickWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			cakeWk[i].g_pD3DTextureObstacle->Release();
			cakeWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			teaWk[i].g_pD3DTextureObstacle->Release();
			teaWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			cookieWk[i].g_pD3DTextureObstacle->Release();
			cookieWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].g_pD3DTextureObstacle != NULL)
		{	// �e�N�X�`���̊J��
			goalWk[i].g_pD3DTextureObstacle->Release();
			goalWk[i].g_pD3DTextureObstacle = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObstacle(void)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������

	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			thornWk[i].CountAnim++;
			if ((thornWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				thornWk[i].PatternAnim = (thornWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureThorn(i, thornWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			thornWk[i].pos += thornWk[i].move;

			// ��ʊO�܂Ői�񂾁H
			if (thornWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - THORN_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				thornWk[i].use = false;
			}

			SetVertexThorn(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			brickWk[i].CountAnim++;
			if ((brickWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				brickWk[i].PatternAnim = (brickWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureBrick(i, brickWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			brickWk[i].pos += brickWk[i].move;

			// ��ʊO�܂Ői�񂾁H
			if (brickWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - BRICK_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				brickWk[i].use = false;
			}

			SetVertexBrick(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			cakeWk[i].CountAnim++;
			if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				cakeWk[i].PatternAnim = (cakeWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureCake(i, cakeWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			cakeWk[i].pos += cakeWk[i].move;

			D3DXVECTOR3 oldpos = cakeWk[i].pos;
			cakeWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������

			cakeWk[i].pos += cakeWk[i].move;

			//��������
			if (cakeWk[i].pos.x < SCREEN_WIDTH)
			{
				if (cakeWk[i].b_hitcnt == false)
				{
					cakeWk[i].fall.y += 0.5f;
					cakeWk[i].rot.z += 0.05f;
					cakeWk[i].pos.y += cakeWk[i].fall.y;

					// �n�ʐݒ�
					if ((cakeWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						cakeWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// �P�[�L�ƃu���b�N(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((cakeWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(cakeWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(cakeWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(cakeWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					cakeWk[i].pos.y = oldpos.y;
					cakeWk[i].b_hitcnt = true;
				}
				else
				{
					cakeWk[i].b_hitcnt = false;
				}
			}

			// ��ʊO�܂Ői�񂾁H
			if (cakeWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				cakeWk[i].use = false;
			}

			SetVertexCake(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			teaWk[i].CountAnim++;
			if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				teaWk[i].PatternAnim = (teaWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureTea(i, teaWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			teaWk[i].pos += teaWk[i].move;

			D3DXVECTOR3 oldpos = teaWk[i].pos;
			teaWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������

			teaWk[i].pos += teaWk[i].move;

			//��������
			if (teaWk[i].pos.x < SCREEN_WIDTH)
			{
				if (teaWk[i].b_hitcnt == false)
				{
					teaWk[i].fall.y += 0.5f;
					teaWk[i].rot.z += 0.05f;
					teaWk[i].pos.y += teaWk[i].fall.y;

					// �n�ʐݒ�
					if ((teaWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						teaWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// �g���ƃu���b�N(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((teaWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(teaWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(teaWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(teaWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					teaWk[i].pos.y = oldpos.y;
					teaWk[i].b_hitcnt = true;
				}
				else
				{
					teaWk[i].b_hitcnt = false;
				}
			}

			// ��ʊO�܂Ői�񂾁H
			if (teaWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				teaWk[i].use = false;
			}

			SetVertexTea(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			cookieWk[i].CountAnim++;
			if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				cookieWk[i].PatternAnim = (cookieWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureCookie(i, cookieWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			cookieWk[i].pos += cookieWk[i].move;

			D3DXVECTOR3 oldpos = cookieWk[i].pos;
			cookieWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������

			cookieWk[i].pos += cookieWk[i].move;

			//��������
			if (cookieWk[i].pos.x < SCREEN_WIDTH)
			{
				if (cookieWk[i].b_hitcnt == false)
				{
					cookieWk[i].fall.y += 0.5f;
					cookieWk[i].rot.z += 0.05f;
					cookieWk[i].pos.y += cookieWk[i].fall.y;

					// �n�ʐݒ�
					if ((cookieWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						cookieWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// �P�[�L�ƃu���b�N(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((cookieWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(cookieWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(cookieWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(cookieWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					cookieWk[i].pos.y = oldpos.y;
					cookieWk[i].b_hitcnt = true;
				}
				else
				{
					cookieWk[i].b_hitcnt = false;
				}
			}

			// ��ʊO�܂Ői�񂾁H
			if (cookieWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				cookieWk[i].use = false;
			}

			SetVertexCookie(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}


	//�S�[������
	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			goalWk[i].CountAnim++;
			if ((goalWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				goalWk[i].PatternAnim = (goalWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureGoal(i, goalWk[i].PatternAnim);
			}

			// ���t���[�����s���鏈��
			goalWk[i].pos += goalWk[i].move;

			// �G�S���|���Ă�����ʂ��ăQ�[���N���A
			if (player[i].pos.x>goalWk[i].pos.x)
			{
				// SetStage(STAGE_GAME_CLEAR);
				SetFade(FADE_OUT, SCENE_RESULT, SOUND_LABEL_BGM_GAMECLEAR);
			}
			SetVertexGoal(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, thornWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, thornWk[i].vertexWk, sizeof(VERTEX_2D));
		}

	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, brickWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, brickWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, cakeWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, cakeWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, teaWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, teaWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, cookieWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, cookieWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, goalWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, goalWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬(���΂�)
//=============================================================================
HRESULT MakeVertexThorn(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexThorn(i);

	// rhw�̐ݒ�
	thornWk[i].vertexWk[0].rhw =
		thornWk[i].vertexWk[1].rhw =
		thornWk[i].vertexWk[2].rhw =
		thornWk[i].vertexWk[3].rhw = 1.0f;

	thornWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	thornWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	thornWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	thornWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	thornWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬(�u���b�N)
//=============================================================================
HRESULT MakeVertexBrick(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexBrick(i);

	// rhw�̐ݒ�
	brickWk[i].vertexWk[0].rhw =
		brickWk[i].vertexWk[1].rhw =
		brickWk[i].vertexWk[2].rhw =
		brickWk[i].vertexWk[3].rhw = 1.0f;

	brickWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	brickWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	brickWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	brickWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	brickWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬(�P�[�L)
//=============================================================================
HRESULT MakeVertexCake(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexCake(i);

	// rhw�̐ݒ�
	cakeWk[i].vertexWk[0].rhw =
		cakeWk[i].vertexWk[1].rhw =
		cakeWk[i].vertexWk[2].rhw =
		cakeWk[i].vertexWk[3].rhw = 1.0f;

	cakeWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	cakeWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	cakeWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	cakeWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	cakeWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬(�g��)
//=============================================================================
HRESULT MakeVertexTea(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexTea(i);

	// rhw�̐ݒ�
	teaWk[i].vertexWk[0].rhw =
		teaWk[i].vertexWk[1].rhw =
		teaWk[i].vertexWk[2].rhw =
		teaWk[i].vertexWk[3].rhw = 1.0f;

	teaWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	teaWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	teaWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	teaWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	teaWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬(�N�b�L�[)
//=============================================================================
HRESULT MakeVertexCookie(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexCookie(i);

	// rhw�̐ݒ�
	cookieWk[i].vertexWk[0].rhw =
		cookieWk[i].vertexWk[1].rhw =
		cookieWk[i].vertexWk[2].rhw =
		cookieWk[i].vertexWk[3].rhw = 1.0f;

	cookieWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	cookieWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	cookieWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	cookieWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	cookieWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬(�S�[��)
//=============================================================================
HRESULT MakeVertexGoal(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexGoal(i);

	// rhw�̐ݒ�
	goalWk[i].vertexWk[0].rhw =
		goalWk[i].vertexWk[1].rhw =
		goalWk[i].vertexWk[2].rhw =
		goalWk[i].vertexWk[3].rhw = 1.0f;

	goalWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	goalWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	goalWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	goalWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	goalWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�(���΂�)
//=============================================================================
void SetTextureThorn(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	thornWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	thornWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	thornWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	thornWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�u���b�N)
//=============================================================================
void SetTextureBrick(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	brickWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	brickWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	brickWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	brickWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�P�[�L)
//=============================================================================
void SetTextureCake(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	cakeWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	cakeWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	cakeWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	cakeWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�g��)
//=============================================================================
void SetTextureTea(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	teaWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	teaWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	teaWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	teaWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�N�b�L�[)
//=============================================================================
void SetTextureCookie(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	cookieWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	cookieWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	cookieWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	cookieWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�S�[��)
//=============================================================================
void SetTextureGoal(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	goalWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	goalWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	goalWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	goalWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexThorn(int i)
{
	// ���_���W�̐ݒ�
	thornWk[i].vertexWk[0].vtx.x = thornWk[i].pos.x - cosf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[0].vtx.y = thornWk[i].pos.y - sinf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[0].vtx.z = 0.0f;

	thornWk[i].vertexWk[1].vtx.x = thornWk[i].pos.x + cosf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[1].vtx.y = thornWk[i].pos.y - sinf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[1].vtx.z = 0.0f;

	thornWk[i].vertexWk[2].vtx.x = thornWk[i].pos.x - cosf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[2].vtx.y = thornWk[i].pos.y + sinf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[2].vtx.z = 0.0f;

	thornWk[i].vertexWk[3].vtx.x = thornWk[i].pos.x + cosf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[3].vtx.y = thornWk[i].pos.y + sinf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBrick(int i)
{
	// ���_���W�̐ݒ�
	brickWk[i].vertexWk[0].vtx.x = brickWk[i].pos.x - cosf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[0].vtx.y = brickWk[i].pos.y - sinf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[0].vtx.z = 0.0f;

	brickWk[i].vertexWk[1].vtx.x = brickWk[i].pos.x + cosf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[1].vtx.y = brickWk[i].pos.y - sinf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[1].vtx.z = 0.0f;

	brickWk[i].vertexWk[2].vtx.x = brickWk[i].pos.x - cosf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[2].vtx.y = brickWk[i].pos.y + sinf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[2].vtx.z = 0.0f;

	brickWk[i].vertexWk[3].vtx.x = brickWk[i].pos.x + cosf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[3].vtx.y = brickWk[i].pos.y + sinf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ���_���W�̐ݒ�(�P�[�L)
//=============================================================================
void SetVertexCake(int i)
{
	if (cakeWk[i].scale_plus == true)
	{
		float len = (cakeWk[i].Radius + (cakeWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// ���_���W�̐ݒ�
		cakeWk[i].vertexWk[0].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.z = 0.0f;

		cakeWk[i].vertexWk[1].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.z = 0.0f;

		cakeWk[i].vertexWk[2].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.z = 0.0f;

		cakeWk[i].vertexWk[3].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �g��I���H
		{														// Yes
			cakeWk[i].scale_plus = false;
		}
	}
	else if (cakeWk[i].scale_plus == false)
	{
		float len = (cakeWk[i].Radius + (cakeWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// ���_���W�̐ݒ�
		cakeWk[i].vertexWk[0].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.z = 0.0f;

		cakeWk[i].vertexWk[1].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.z = 0.0f;

		cakeWk[i].vertexWk[2].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.z = 0.0f;

		cakeWk[i].vertexWk[3].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �k���I���H
		{														// Yes
			cakeWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// ���_���W�̐ݒ�(�g��)
//=============================================================================
void SetVertexTea(int i)
{
	if (teaWk[i].scale_plus == true)
	{
		float len = (teaWk[i].Radius + (teaWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// ���_���W�̐ݒ�
		teaWk[i].vertexWk[0].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.z = 0.0f;

		teaWk[i].vertexWk[1].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.z = 0.0f;

		teaWk[i].vertexWk[2].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.z = 0.0f;

		teaWk[i].vertexWk[3].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �g��I���H
		{														// Yes
			teaWk[i].scale_plus = false;
		}
	}
	else if (teaWk[i].scale_plus == false)
	{
		float len = (teaWk[i].Radius + (teaWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// ���_���W�̐ݒ�
		teaWk[i].vertexWk[0].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.z = 0.0f;

		teaWk[i].vertexWk[1].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.z = 0.0f;

		teaWk[i].vertexWk[2].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.z = 0.0f;

		teaWk[i].vertexWk[3].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �k���I���H
		{														// Yes
			teaWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// ���_���W�̐ݒ�(�N�b�L�[)
//=============================================================================
void SetVertexCookie(int i)
{
	if (cookieWk[i].scale_plus == true)
	{
		float len = (cookieWk[i].Radius + (cookieWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// ���_���W�̐ݒ�
		cookieWk[i].vertexWk[0].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.z = 0.0f;

		cookieWk[i].vertexWk[1].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.z = 0.0f;

		cookieWk[i].vertexWk[2].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.z = 0.0f;

		cookieWk[i].vertexWk[3].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �g��I���H
		{														// Yes
			cookieWk[i].scale_plus = false;
		}
	}
	else if (cookieWk[i].scale_plus == false)
	{
		float len = (cookieWk[i].Radius + (cookieWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// ���_���W�̐ݒ�
		cookieWk[i].vertexWk[0].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.z = 0.0f;

		cookieWk[i].vertexWk[1].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.z = 0.0f;

		cookieWk[i].vertexWk[2].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.z = 0.0f;

		cookieWk[i].vertexWk[3].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// �k���I���H
		{														// Yes
			cookieWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// ���_���W�̐ݒ�(�S�[��)
//=============================================================================
void SetVertexGoal(int i)
{
	//// ���_���W�̐ݒ�
	//if (goalWk[i].use == true)
	//{
		// ���_���W�̐ݒ�
	goalWk[i].vertexWk[0].vtx.x = goalWk[i].pos.x - cosf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[0].vtx.y = goalWk[i].pos.y - sinf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[0].vtx.z = 0.0f;

	goalWk[i].vertexWk[1].vtx.x = goalWk[i].pos.x + cosf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[1].vtx.y = goalWk[i].pos.y - sinf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[1].vtx.z = 0.0f;

	goalWk[i].vertexWk[2].vtx.x = goalWk[i].pos.x - cosf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[2].vtx.y = goalWk[i].pos.y + sinf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[2].vtx.z = 0.0f;

	goalWk[i].vertexWk[3].vtx.x = goalWk[i].pos.x + cosf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[3].vtx.y = goalWk[i].pos.y + sinf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[3].vtx.z = 0.0f;
	/*}*/
}
//=============================================================================
// ���΂�擾�֐�
//=============================================================================
THORN *GetThorn(void)
{
	return(&thornWk[0]);
}

//=============================================================================
// �u���b�N�擾�֐�
//=============================================================================
BRICK *GetBrick(void)
{
	return(&brickWk[0]);
}

//=============================================================================
// �P�[�L�擾�֐�
//=============================================================================
CAKE *GetCake(void)
{
	return(&cakeWk[0]);
}

//=============================================================================
// �g���擾�֐�
//=============================================================================
TEA *GetTea(void)
{
	return(&teaWk[0]);
}

//=============================================================================
// �N�b�L�[�擾�֐�
//=============================================================================
COOKIE *GetCookie(void)
{
	return(&cookieWk[0]);
}

//=============================================================================
// �S�[���擾�֐�
//=============================================================================
GOAL *GetGoal(void)
{
	return(&goalWk[0]);
}