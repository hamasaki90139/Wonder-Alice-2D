//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTutorial(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial01 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial02 = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTutorial01[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTutorial02[NUM_VERTEX];					// ���_���i�[���[�N

static int				g_pagecnt;		//�y�[�W���J�E���g

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorial(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		 /*�e�N�X�`���̓ǂݍ���*/
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TUTORIAL01,				// �t�@�C���̖��O
			&g_pD3DTextureTutorial01);		// �ǂݍ��ރ������[

		 /*�e�N�X�`���̓ǂݍ���*/
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TUTORIAL02,				// �t�@�C���̖��O
			&g_pD3DTextureTutorial02);		// �ǂݍ��ރ������[
	}

	g_pagecnt = TUTORIAL01;		//�`���[�g���A����ʂ̏�����

	// ���_���̍쐬
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	if (g_pD3DTextureTutorial01 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTutorial01->Release();
		g_pD3DTextureTutorial01 = NULL;
	}
	if (g_pD3DTextureTutorial02 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTutorial02->Release();
		g_pD3DTextureTutorial02 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	if (g_pagecnt == TUTORIAL01)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			g_pagecnt++;
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			g_pagecnt++;
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			g_pagecnt++;
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	if (g_pagecnt == TUTORIAL01)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureTutorial01);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial01, sizeof(VERTEX_2D));
	}
	else if (g_pagecnt == TUTORIAL02)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureTutorial02);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial02, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTutorial(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkTutorial01[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial01[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial01[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial01[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTutorial01[0].rhw =
	g_vertexWkTutorial01[1].rhw =
	g_vertexWkTutorial01[2].rhw =
	g_vertexWkTutorial01[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTutorial01[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTutorial01[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial01[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial01[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial01[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkTutorial02[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial02[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial02[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial02[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTutorial02[0].rhw =
	g_vertexWkTutorial02[1].rhw =
	g_vertexWkTutorial02[2].rhw =
	g_vertexWkTutorial02[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTutorial02[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTutorial02[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial02[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial02[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial02[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
