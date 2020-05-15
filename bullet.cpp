//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "enemy.h"
#include "hp.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetTextureBullet(int no, int cntPattern);
void SetVertexBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static BULLET					bulletWk[BULLET_MAX];			// �o���b�g�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			BULLET_TEXTURE01,						// �t�@�C���̖��O
			&bulletWk[0].g_pD3DTextureBullet);		// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			BULLET_TEXTURE02,						// �t�@�C���̖��O
			&bulletWk[1].g_pD3DTextureBullet);		// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			BULLET_TEXTURE03,						// �t�@�C���̖��O
			&bulletWk[2].g_pD3DTextureBullet);		// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			BULLET_TEXTURE04,						// �t�@�C���̖��O
			&bulletWk[3].g_pD3DTextureBullet);		// �ǂݍ��ރ������̃|�C���^
	}

	// �o���b�g�̏���������
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bulletWk[i].use = false;										// ���g�p�i���˂���Ă��Ȃ��e�j
		bulletWk[i].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				// ���W�f�[�^��������
		bulletWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		bulletWk[i].move = D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f);		// �ړ��ʂ�������
		bulletWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		bulletWk[i].CountAnim = 0;										// �A�j���J�E���g��������
		bulletWk[i].Texture = bulletWk[i%4].g_pD3DTextureBullet;		//�e�N�X�`����ݒ�

		D3DXVECTOR2 temp = D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y);
		bulletWk[i].Radius = D3DXVec2Length(&temp);						// �o���b�g�̔��a��������
		bulletWk[i].BaseAngle = atan2f(BULLET_TEXTURE_SIZE_Y, BULLET_TEXTURE_SIZE_X);	// �o���b�g�̊p�x��������

		MakeVertexBullet(i);											// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].g_pD3DTextureBullet != NULL)
		{	// �e�N�X�`���̊J��
			bulletWk[i].g_pD3DTextureBullet->Release();
			bulletWk[i].g_pD3DTextureBullet = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == true)		// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			bulletWk[i].pos += bulletWk[i].move;

			// �o���b�g�̉�]����
			bulletWk[i].rot.z += 0.05f;

			// ��ʊO�܂Ői�񂾁H�����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			if ((bulletWk[i].pos.x >= SCREEN_WIDTH - BULLET_TEXTURE_SIZE_X) ||
				(bulletWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - BULLET_TEXTURE_SIZE_X) ||
				(bulletWk[i].pos.y >= SCREEN_HEIGHT - BULLET_TEXTURE_SIZE_Y) ||
				(bulletWk[i].pos.y <= (SCREEN_HEIGHT - SCREEN_HEIGHT) - BULLET_TEXTURE_SIZE_Y))
			{
				bulletWk[i].use = false;
			}

			SetVertexBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bulletWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bulletWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexBullet(i);

	// rhw�̐ݒ�
	bulletWk[i].vertexWk[0].rhw =
	bulletWk[i].vertexWk[1].rhw =
	bulletWk[i].vertexWk[2].rhw =
	bulletWk[i].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bulletWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bulletWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bulletWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	bulletWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y);
	bulletWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X, 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % BULLET_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / BULLET_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y;

	bulletWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bulletWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bulletWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bulletWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(int i)
{
	// ���_���W�̐ݒ�
	bulletWk[i].vertexWk[0].vtx.x = bulletWk[i].pos.x - cosf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[0].vtx.y = bulletWk[i].pos.y - sinf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[0].vtx.z = 0.0f;

	bulletWk[i].vertexWk[1].vtx.x = bulletWk[i].pos.x + cosf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[1].vtx.y = bulletWk[i].pos.y - sinf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[1].vtx.z = 0.0f;

	bulletWk[i].vertexWk[2].vtx.x = bulletWk[i].pos.x - cosf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[2].vtx.y = bulletWk[i].pos.y + sinf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[2].vtx.z = 0.0f;

	bulletWk[i].vertexWk[3].vtx.x = bulletWk[i].pos.x + cosf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[3].vtx.y = bulletWk[i].pos.y + sinf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, int type)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			bulletWk[i].use = true;			// �g�p��Ԃ֕ύX����
			bulletWk[i].pos = pos;			// ���W���Z�b�g
			bulletWk[i].type = type;		// �e�̎�ނ��Z�b�g

			// �e�̎�ނɉ����Ĕ�΂�������ς��Ă݂鏈��
			switch (type)
			{
			case 0:	//�E��1
			default:
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, -BULLET_SPEED, 0.0f);		// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// �E�΂߂S�T�x����
				break;

			case 1:	//�E��2
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, -BULLET_SPEED / 2, 0.0f);	// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// �E�΂߂S�T�x����
				break;

			case 2:	//�E��
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f);				// �ړ��ʂ�������
				bulletWk[i].rot.z = 0.0f;												// ���ʌ���
				break;

			case 3:	//�E��1
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, BULLET_SPEED / 2, 0.0f);	// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// �E�΂߂S�T�x����
				break;

			case 4:	//�E��2
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, BULLET_SPEED, 0.0f);		// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// �E�΂߂S�T�x����
				break;

			case 5:	//����1
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, -BULLET_SPEED, 0.0f);		// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// ���΂߂S�T�x����
				break;

			case 6:	//����2
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, -BULLET_SPEED / 2, 0.0f);	// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// ���΂߂S�T�x����
				break;

			case 7:	//����
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, 0.0f, 0.0f);				// �ړ��ʂ�������
				bulletWk[i].rot.z = 0.0f;												// ���ʌ���
				break;

			case 8:	//����1
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, BULLET_SPEED / 2, 0.0f);	// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// ���΂߂S�T�x����
				break;

			case 9:	//����2
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, BULLET_SPEED, 0.0f);		// �ړ��ʂ�������
				bulletWk[i].rot.z = -D3DX_PI / 4;										// ���΂߂S�T�x����
				break;

			}

			// SE�Đ�
			PlaySound(SOUND_LABEL_SE_BULLET);
			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�擾�֐�
//=============================================================================
BULLET *GetBullet(void)
{
	return(&bulletWk[0]);
}

