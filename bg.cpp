//=============================================================================
//
// BG���� [bg.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetVertexBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture[NUM_BG] = { NULL };	// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D				g_vertexWk[NUM_BG][NUM_VERTEX];	// ���_���i�[���[�N

static D3DXVECTOR3				g_pos;					// �w�i�̈ʒu
float							interval[NUM_BG];


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			BG_TEXTURE,				// �t�@�C���̖��O
			&g_pD3DTexture[0]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			BG_TEXTURE,				// �t�@�C���̖��O
			&g_pD3DTexture[1]);		// �ǂݍ��ރ������[
	}

	for (int i = 0; i < NUM_BG; i++)
	{
		interval[i] = i * BG_SIZE_W;
	}
	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexBG();
	SetVertexBG();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		if (g_pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		// ���t���[�����s���鏈��
		g_pos.x -= 1.0f;

		// �X�N���[������
		/*g_pos.x = -GetPlayer()->pos.x;*/

		if (interval[i] + BG_SIZE_W + g_pos.x < 0)	//���[�v����
		{
			interval[i] += NUM_BG * BG_SIZE_W;
		}

		// �ړ���̍��W�Œ��_��ݒ�
		SetVertexBG();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < NUM_BG; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexture[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// ���_���W�̐ݒ�
	SetVertexBG();

	for (int i = 0; i < NUM_BG; i++)
	{
		// rhw�̐ݒ�
		g_vertexWk[i][0].rhw =
			g_vertexWk[i][1].rhw =
			g_vertexWk[i][2].rhw =
			g_vertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);

		// �e�N�X�`�����W�̐ݒ�
		g_vertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWk[i][0].vtx = D3DXVECTOR3(BG_POS_X + interval[i], BG_POS_Y, 0.0f) + g_pos;
		g_vertexWk[i][1].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W + interval[i], BG_POS_Y, 0.0f) + g_pos;
		g_vertexWk[i][2].vtx = D3DXVECTOR3(BG_POS_X + interval[i], BG_POS_Y + BG_SIZE_H, 0.0f) + g_pos;
		g_vertexWk[i][3].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W + interval[i], BG_POS_Y + BG_SIZE_H, 0.0f) + g_pos;
	}
}

//=============================================================================
// BG�擾�֐�
//=============================================================================
void *GetBG(void)
{
	return(&g_pos);
}
