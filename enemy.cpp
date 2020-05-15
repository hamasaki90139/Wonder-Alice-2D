//=============================================================================
//
// �G���� [enemy.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "obstacle.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy(int no, int cntPattern);
void SetVertexEnemy(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	srand((unsigned)time(NULL));	//�����_�������l�̏�����
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE01,										// �t�@�C���̖��O
			&enemyWk[0].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE02,										// �t�@�C���̖��O
			&enemyWk[1].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE03,										// �t�@�C���̖��O
			&enemyWk[2].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE04,										// �t�@�C���̖��O
			&enemyWk[3].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE05,										// �t�@�C���̖��O
			&enemyWk[4].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE06,										// �t�@�C���̖��O
			&enemyWk[5].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE07,										// �t�@�C���̖��O
			&enemyWk[6].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE08,										// �t�@�C���̖��O
			&enemyWk[7].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE09,										// �t�@�C���̖��O
			&enemyWk[8].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE10,										// �t�@�C���̖��O
			&enemyWk[9].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE11,										// �t�@�C���̖��O
			&enemyWk[10].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE12,										// �t�@�C���̖��O
			&enemyWk[11].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE13,										// �t�@�C���̖��O
			&enemyWk[12].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE14,										// �t�@�C���̖��O
			&enemyWk[13].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE15,										// �t�@�C���̖��O
			&enemyWk[14].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE16,										// �t�@�C���̖��O
			&enemyWk[15].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE17,										// �t�@�C���̖��O
			&enemyWk[16].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE18,										// �t�@�C���̖��O
			&enemyWk[17].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE19,										// �t�@�C���̖��O
			&enemyWk[18].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE20,										// �t�@�C���̖��O
			&enemyWk[19].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE21,										// �t�@�C���̖��O
			&enemyWk[20].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE22,										// �t�@�C���̖��O
			&enemyWk[21].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE23,										// �t�@�C���̖��O
			&enemyWk[22].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE24,										// �t�@�C���̖��O
			&enemyWk[23].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE25,										// �t�@�C���̖��O
			&enemyWk[24].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE26,										// �t�@�C���̖��O
			&enemyWk[25].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE27,										// �t�@�C���̖��O
			&enemyWk[26].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE28,										// �t�@�C���̖��O
			&enemyWk[27].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE29,										// �t�@�C���̖��O
			&enemyWk[28].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE30,										// �t�@�C���̖��O
			&enemyWk[29].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE31,										// �t�@�C���̖��O
			&enemyWk[30].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE32,										// �t�@�C���̖��O
			&enemyWk[31].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE33,										// �t�@�C���̖��O
			&enemyWk[32].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE34,										// �t�@�C���̖��O
			&enemyWk[33].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE35,										// �t�@�C���̖��O
			&enemyWk[34].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			ENEMY_TEXTURE36,										// �t�@�C���̖��O
			&enemyWk[35].g_pD3DTextureEnemy);								// �ǂݍ��ރ������̃|�C���^

	}


	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemyWk[i].use = true;										// �g�p
		enemyWk[i].pos = D3DXVECTOR3(i* (rand() % (200 + 1) + 100) + 1500.0f, rand() % (300 + 1) + 100.0f, 0.0f);	// ���W�f�[�^��������
		enemyWk[i].move = D3DXVECTOR3(-(rand() % (2 + 1) + 3.0f), 0.0f, 0.0f);				// �ړ���
		enemyWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������
		enemyWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������

		enemyWk[i].rotflag = true;		//����]�ŏ�����
		enemyWk[i].rot_cnt = 0;
		enemyWk[i].rot_cnt_max = ENEMY_ROT_CNT_MAX;
		enemyWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemyWk[i].CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y);
		enemyWk[i].Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemyWk[i].BaseAngle = atan2f(ENEMY_TEXTURE_SIZE_Y, ENEMY_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������
		enemyWk[i].Texture = enemyWk[i].g_pD3DTextureEnemy;

		MakeVertexEnemy(i);											// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].g_pD3DTextureEnemy != NULL)
		{	// �e�N�X�`���̊J��
			enemyWk[i].g_pD3DTextureEnemy->Release();
			enemyWk[i].g_pD3DTextureEnemy = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������
	BRICK  *brick = GetBrick();			// �u���b�N�̃|�C���^�[��������

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			enemyWk[i].CountAnim++;
			if ((enemyWk[i].CountAnim % ENEMY_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemyWk[i].PatternAnim = (enemyWk[i].PatternAnim + 1) % ENEMY_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemy(i, enemyWk[i].PatternAnim);
			}

			// ����]����
			if (enemyWk[i].rotflag == true)
			{
				enemyWk[i].rot.z += 0.05f;
				enemyWk[i].rot_cnt++;
				if (enemyWk[i].rot_cnt >= enemyWk[i].rot_cnt_max)	// �W�����v�I���H
				{														// Yes
					enemyWk[i].rotflag = false;	//�E��]��
					enemyWk[i].rot_cnt = 0;
				}
			}
			//�E��]����
			else if (enemyWk[i].rotflag == false)
			{
				enemyWk[i].rot.z += -0.05f;
				enemyWk[i].rot_cnt++;
				if (enemyWk[i].rot_cnt >= enemyWk[i].rot_cnt_max)	// �W�����v�I���H
				{														// Yes
					enemyWk[i].rotflag = true;	//����]��
					enemyWk[i].rot_cnt = 0;
				}
			}

				D3DXVECTOR3 oldpos = enemyWk[i].pos;
				bool b_hitcnt = false;		//�u���b�N�Ɠ���������
				enemyWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ������

				enemyWk[i].pos += enemyWk[i].move;

				//��������
				if (enemyWk[i].pos.x < SCREEN_WIDTH)
				{
					if (b_hitcnt == false)
					{
						enemyWk[i].fall.y += 1.5f;
						enemyWk[i].pos.y += enemyWk[i].fall.y;

						// �n�ʐݒ�
						if ((enemyWk[i].pos.y + ENEMY_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
						{
							enemyWk[i].pos.y = SCREEN_HEIGHT - ENEMY_TEXTURE_SIZE_Y;
						}
					}
				}

				// �G�l�~�[�ƃu���b�N(BB)
				for (int j = 0; j < BRICK_MAX; j++)
				{
					if (brick[j].use == false) continue;

					if ((enemyWk[i].pos.x + ENEMY_TEXTURE_SIZE_X / 2 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
						(enemyWk[i].pos.x - ENEMY_TEXTURE_SIZE_X / 2 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
						(enemyWk[i].pos.y + ENEMY_TEXTURE_SIZE_Y / 2 > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
						(enemyWk[i].pos.y - ENEMY_TEXTURE_SIZE_Y / 2 < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
					{
						enemyWk[i].pos.y = oldpos.y;
						b_hitcnt = true;
					}
					else
					{
						b_hitcnt = false;
					}
				}

				// ��ʊO�܂Ői�񂾁H
				if (enemyWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ENEMY_TEXTURE_SIZE_X)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
				{
					enemyWk[i].use = false;
				}

				SetVertexEnemy(i);						// �ړ���̍��W�Œ��_��ݒ�
			}
		}

	}

	//=============================================================================
	// �`�揈��
	//=============================================================================
	void DrawEnemy(void)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemyWk[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemyWk[i].Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemyWk[i].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}

	//=============================================================================
	// ���_�̍쐬
	//=============================================================================
	HRESULT MakeVertexEnemy(int i)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_���W�̐ݒ�
		SetVertexEnemy(i);

		// rhw�̐ݒ�
		enemyWk[i].vertexWk[0].rhw =
			enemyWk[i].vertexWk[1].rhw =
			enemyWk[i].vertexWk[2].rhw =
			enemyWk[i].vertexWk[3].rhw = 1.0f;

		enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);

		// ���ˌ��̐ݒ�
		/*if (i & 1)
		{
			enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
		}*/

		// �e�N�X�`�����W�̐ݒ�
		enemyWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		enemyWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		enemyWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y);
		enemyWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X, 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y);

		//enemyWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//enemyWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//enemyWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//enemyWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		return S_OK;
	}

	//=============================================================================
	// �e�N�X�`�����W�̐ݒ�
	//=============================================================================
	void SetTextureEnemy(int i, int cntPattern)
	{
		// �e�N�X�`�����W�̐ݒ�
		int x = cntPattern % ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		int y = cntPattern / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y;

		enemyWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemyWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}

	//=============================================================================
	// ���_���W�̐ݒ�
	//=============================================================================
	void SetVertexEnemy(int i)
	{
		// ���_���W�̐ݒ�
		enemyWk[i].vertexWk[0].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[0].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[0].vtx.z = 0.0f;

		enemyWk[i].vertexWk[1].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[1].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[1].vtx.z = 0.0f;

		enemyWk[i].vertexWk[2].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[2].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[2].vtx.z = 0.0f;

		enemyWk[i].vertexWk[3].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[3].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[3].vtx.z = 0.0f;
	}

	//=============================================================================
	// �G�l�~�[�擾�֐�
	//=============================================================================
	ENEMY *GetEnemy(void)
	{
		return(&enemyWk[0]);
	}


