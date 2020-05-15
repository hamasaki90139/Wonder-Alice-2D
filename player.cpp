//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "obstacle.h"
#include "sound.h"
#include "bg.h"
#include "hp.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(int no);
void SetTexturePlayer(int no, int cntPattern);
void SetVertexPlayer(int no);
void SetDiffusePlayer(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

static PLAYER					playerWk[PLAYER_MAX];			// �v���C���[�\����

//static LPDIRECTSOUNDBUFFER8		g_pSE;							// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			PLAYER_TEXTURE,					// �t�@�C���̖��O
			&g_pD3DTexturePlayer);			// �ǂݍ��ރ������̃|�C���^
	}

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		playerWk[i].use = true;											// �g�p
		playerWk[i].dmgflag = false;									// �_���[�W���薳�ŏ�����
		playerWk[i].dmg = true;											// �_���[�W��^�����ŏ�����
		playerWk[i].direction = true;									// �E�����ŏ�����
		playerWk[i].pos = D3DXVECTOR3(i*100.0f + 200.0f, 340.0f, 0.0f);	// ���W�f�[�^��������
		playerWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		playerWk[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
		playerWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		playerWk[i].CountAnim = 0;										// �A�j���J�E���g��������
		playerWk[i].Texture = g_pD3DTexturePlayer;

		playerWk[i].jump = false;										// �W�����v�����ᖳ��
		playerWk[i].jump_y = PLAYER_JUMP_Y;								// �W�����v���̍���
		playerWk[i].jump_cnt = 0;										//�W�����v�J�E���g�̏�����
		playerWk[i].jump_cnt_max = PLAYER_JUMP_CNT_MAX;					//�W�����v�J�E���g�ő�l�̐ݒ�
		playerWk[i].ofs = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �I�t�Z�b�g���W��������
		playerWk[i].jumppoint = 0;

		D3DXVECTOR2 temp = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
		playerWk[i].Radius = D3DXVec2Length(&temp);						// �v���C���[�̔��a��������

		MakeVertexPlayer(i);											// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	BRICK  *brick = GetBrick();			// �u���b�N�̃|�C���^�[��������
	MP *mp = GetMp();					// �X�R�A�̃|�C���^�[��������
	BULLET *bullet = GetBullet();			// �o���b�g�̃|�C���^�[��������


	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (playerWk[i].use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			D3DXVECTOR3 oldpos = playerWk[i].pos;
			D3DXVECTOR3 oldofs = playerWk[i].ofs;

			// �A�j���[�V����
			playerWk[i].CountAnim++;
			if ((playerWk[i].CountAnim % PLAYER_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				playerWk[i].PatternAnim = (playerWk[i].PatternAnim + 1) % 2;
			}

			//�ړ�����
			if (GetKeyboardPress(DIK_D) || (IsButtonPressed(0, BUTTON_RIGHT)))	//�E�ړ�
			{
				playerWk[i].move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
				playerWk[i].direction = true;
			}
			else if (GetKeyboardPress(DIK_A) || (IsButtonPressed(0, BUTTON_LEFT)))	//���ړ�
			{
				playerWk[i].move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
				playerWk[i].direction = false;
			}
			else
			{
				playerWk[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			//�E���������������ŃA�j���p�^�[����؂�ւ���
			if (playerWk[i].direction == false)
			{
				SetTexturePlayer(i, playerWk[i].PatternAnim + 2);
			}
			else
			{
				SetTexturePlayer(i, playerWk[i].PatternAnim);
			}

			// �W�����v����
			if (playerWk[i].jump == true)
			{
				float rag = D3DX_PI / playerWk[i].jump_cnt_max;
				float angle = rag * playerWk[i].jump_cnt;
				playerWk[i].move.y = sinf(angle) * playerWk[i].jump_y;
				playerWk[i].jump_cnt++;

				//�W�����v�A�j���p�^�[���̐؂�ւ�
				if (playerWk[i].direction == false)
				{
					SetTexturePlayer(i, playerWk[i].PatternAnim + 6);
				}
				else
				{
					SetTexturePlayer(i, playerWk[i].PatternAnim + 4);
				}

				if (playerWk[i].jump_cnt >= playerWk[i].jump_cnt_max)	// �W�����v�I���H
				{														// Yes
					playerWk[i].jump = false;
				}
			}

			// �d�͏���
			playerWk[i].move.y += 6.0f;

			playerWk[i].pos += playerWk[i].move;

			// ��ʊO�܂Ői�񂾁H
			if (playerWk[i].pos.x >= SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X / 2)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				playerWk[i].pos.x = SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X / 2;
			}
			else if (playerWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - PLAYER_TEXTURE_SIZE_X / 4)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				playerWk[i].pos.x = (SCREEN_WIDTH - SCREEN_WIDTH) - PLAYER_TEXTURE_SIZE_X / 4;
			}
			else if (playerWk[i].pos.y <= (SCREEN_HEIGHT - SCREEN_HEIGHT) - PLAYER_TEXTURE_SIZE_Y / 4)// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				playerWk[i].pos.y = (SCREEN_HEIGHT - SCREEN_HEIGHT) - PLAYER_TEXTURE_SIZE_Y / 4;
			}

			// �W�����v�H
			if (playerWk[i].jumppoint < PLAYER_JUMPMAX)
			{
				if (GetKeyboardTrigger(DIK_W) || (IsButtonTriggered(0, BUTTON_UP)))
				{
					if (playerWk[i].jump == false)	// ���̓W�����v���Ă��Ȃ��H
					{								// Yes
						playerWk[i].jump = true;
						playerWk[i].jump_cnt = 0;
						playerWk[i].jumppoint++;
					}
				}
			}

			// �v���C���[�ƃu���b�N(BB)
			D3DXVECTOR3 pos = playerWk[i].pos + playerWk[i].ofs;

			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (playerWk[i].use == false) continue;
				if (playerWk[i].jump == true) continue;
				if (brick[j].use == false)	  continue;

				//�v���C���[���n��Ńu���b�N�ɓ��������Ƃ�
				if ((playerWk[i].move.x != 0.0f) &&
					((playerWk[i].pos.y + PLAYER_TEXTURE_SIZE_Y) > SCREEN_HEIGHT) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move *= -1;									//�ړ��ʂ̔��]
					playerWk[i].pos += playerWk[i].move;					//�ړ��ʂ����W�փv���X
					playerWk[i].jump = false;								//�W�����v���Ă��Ȃ�
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;								//�u���b�N�ɉ������
				}
				// �v���C���[���󒆂Ńu���b�N�ɓ��������Ƃ�
				else if ((playerWk[i].move.x != 0.0f) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y-20 > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move.y *= -1;
					playerWk[i].pos += playerWk[i].move;
					playerWk[i].jump = false;
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;
				}
				//�L�[���삪�Ȃ����u���b�N�ɓ��������Ƃ�
				else if ((playerWk[i].move.x == 0.0f) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move.y *= -1;
					playerWk[i].pos += playerWk[i].move;
					playerWk[i].jump = false;
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;
				}
			}

			/*�e���ˁH*/
			int	cnt = 0;						//�G�l�~�[�̐����J�E���g
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (bullet[i].use == true)
				{
					cnt++;
				}
			}

			if (cnt < BULLET_CNT)
			{
				if (GetKeyboardTrigger(DIK_UP) || (IsButtonTriggered(0, BUTTON_B)))	//���������
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 0);		// �E��
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 5);		// ����
					}
				}

				if (GetKeyboardTrigger(DIK_DOWN) || (IsButtonTriggered(0, BUTTON_C)))	//����������
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 3);		// �E��
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 8);		// ����
					}
				}

				if (GetKeyboardTrigger(DIK_RIGHT) || (IsButtonTriggered(0, BUTTON_A)))	//��������
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 2);		// �E��
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 7);		// ����
					}
				}
			}

			if (GetKeyboardTrigger(DIK_LEFT) || (IsButtonTriggered(0, BUTTON_X)))	//�`���[�W����
			{
				if (mp->mp >= MP_UNIT)
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 0);		// �E��1
						SetBullet(pos, 1);		// �E��2
						SetBullet(pos, 3);		// �E��1
						SetBullet(pos, 4);		// �E��2

						AddMp(-MP_UNIT);			//MP�Q�[�W����
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 5);		// ����1
						SetBullet(pos, 6);		// ����2
						SetBullet(pos, 8);		// ����1
						SetBullet(pos, 9);		// ����2

						AddMp(-MP_UNIT);			//MP�Q�[�W����
					}
				}
			}
		}

		//���g���C
		if (GetKeyboardTrigger(DIK_SPACE) || ((IsButtonTriggered(0, BUTTON_R)&& (IsButtonTriggered(0, BUTTON_L)))))
		{
			SetSceneold();
			SetFade(FADE_OUT, SCENE_RETRY, SOUND_LABEL_BGM_GAME);
		}

		// �n�ʐݒ�
		if ((playerWk[i].pos.y + PLAYER_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
		{
			playerWk[i].pos.y = SCREEN_HEIGHT - PLAYER_TEXTURE_SIZE_Y;
			playerWk[i].jumppoint = 0;
		}

		SetVertexPlayer(i);	// �ړ���̍��W�Œ��_��ݒ�
		SetDiffusePlayer(i);	// ��_���[�W�F�̐ݒ�
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (playerWk[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, playerWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, playerWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	playerWk[i].vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	playerWk[i].vertexWk[1].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f, 0.0f);
	playerWk[i].vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);
	playerWk[i].vertexWk[3].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	playerWk[i].vertexWk[0].rhw =
	playerWk[i].vertexWk[1].rhw =
	playerWk[i].vertexWk[2].rhw =
	playerWk[i].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	playerWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	playerWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	playerWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y);
	playerWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X, 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	playerWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	playerWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	playerWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	playerWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int i)
{
	// ���_���W�̐ݒ�
	D3DXVECTOR3 pos = playerWk[i].pos + playerWk[i].ofs;

	playerWk[i].vertexWk[0].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[0].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[0].vtx.z = 0.0f;

	playerWk[i].vertexWk[1].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[1].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[1].vtx.z = 0.0f;

	playerWk[i].vertexWk[2].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[2].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[2].vtx.z = 0.0f;

	playerWk[i].vertexWk[3].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[3].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// HP�����F�̐ݒ�
//=============================================================================
void SetDiffusePlayer(int i)
{
	if (playerWk[i].dmgflag == true)	//�v���C���[���_���[�W����������
	{
		// ���ˌ��̐ݒ�
		playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);

		playerWk[i].dmg_cnt++;		//�_���[�W�F�\�����Ԃ̃J�E���g
		if (playerWk[i].dmg_cnt == PLAYER_DMG_CNT_MAX)
		{
			playerWk[i].dmgflag = false;	//�_���[�W�t���O�𖳂ɖ߂�
			playerWk[i].dmg_cnt = 0;	//�J�E���g��������
		}
	}
	else if (playerWk[i].dmgflag == false)	//�v���C���[���_���[�W�������Ă��Ȃ����
	{
		// ���ˌ��̐ݒ�
		playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}
//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(void)
{
	return(&playerWk[0]);
}