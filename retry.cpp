//=============================================================================
//
// ���g���C��ʏ��� [retry.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "retry.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRetry(void);
void SetVertexLogo(void);
void SetVertexLogoColor(void);
void SetRetryMenuDiffuse(int menu);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRetrybg = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRetry = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureReturn = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkRetrybg[NUM_VERTEX];					// ���_���i�[���[�NVERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];				// ���_���i�[���[�N
VERTEX_2D				g_vertexWkRetry[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkReturn[NUM_VERTEX];					// ���_���i�[���[�N

static D3DXCOLOR		g_color;

static int menu; 						//���j���[�p�ϐ�
static int scene;



//=============================================================================
// ����������
//=============================================================================
HRESULT InitRetry(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		/*�e�N�X�`���̓ǂݍ���*/
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE01,				// �t�@�C���̖��O
			&g_pD3DTextureRetrybg);		// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_NEWGAME,			// �t�@�C���̖��O
			&g_pD3DTextureRetry);	// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_EXIT,			// �t�@�C���̖��O
			&g_pD3DTextureReturn);	// �ǂݍ��ރ������[
	}

	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	menu = 0;	//���j���[������

	// ���_���̍쐬
	MakeVertexRetry();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRetry(void)
{
	if (g_pD3DTextureRetrybg != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRetrybg->Release();
		g_pD3DTextureRetrybg = NULL;
	}

	if (g_pD3DTextureRetry != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRetry->Release();
		g_pD3DTextureRetry = NULL;
	}

	if (g_pD3DTextureReturn != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureReturn->Release();
		g_pD3DTextureReturn = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRetry(void)
{
	 //int *scene=GetScene();				// �X�R�A�̃|�C���^�[��������
	scene = GetSceneold();	//1�O�̃V�[���̃Z�b�g

	//menu�I��
	if (GetKeyboardRepeat(DIK_UP)|| GetKeyboardRepeat(DIK_DOWN)|| 
		(IsButtonTriggered(0, BUTTON_UP)) || (IsButtonTriggered(0, BUTTON_DOWN)))
	{
		menu = (menu + 1) % MENU_MAX;
	}

	switch (menu)
	{
	case 0:
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		break;
	case 1:		//�L�����Z��
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			if (scene== SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if(scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			if (scene == SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if (scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			if (scene == SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if (scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		break;
	}

	SetVertexLogo();

	SetVertexLogoColor();

	SetRetryMenuDiffuse(menu);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRetrybg);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRetrybg, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRetry);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRetry, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureReturn);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkReturn, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRetry(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkRetrybg[0].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkRetrybg[1].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkRetrybg[2].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);
	g_vertexWkRetrybg[3].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRetrybg[0].rhw =
	g_vertexWkRetrybg[1].rhw =
	g_vertexWkRetrybg[2].rhw =
	g_vertexWkRetrybg[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRetrybg[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRetrybg[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRetrybg[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRetrybg[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRetrybg[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkRetry[0].vtx = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y, 0.0f);
	g_vertexWkRetry[1].vtx = D3DXVECTOR3(RETRY_POS_X + RETRYMENU_SIZE_X, RETRY_POS_Y, 0.0f);
	g_vertexWkRetry[2].vtx = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y + RETRYMENU_SIZE_Y, 0.0f);
	g_vertexWkRetry[3].vtx = D3DXVECTOR3(RETRY_POS_X + RETRYMENU_SIZE_X, RETRY_POS_Y + RETRYMENU_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRetry[0].rhw =
	g_vertexWkRetry[1].rhw =
	g_vertexWkRetry[2].rhw =
	g_vertexWkRetry[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRetry[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRetry[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRetry[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRetry[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkReturn[0].vtx = D3DXVECTOR3(RETURN_POS_X, RETURN_POS_Y, 0.0f);
	g_vertexWkReturn[1].vtx = D3DXVECTOR3(RETURN_POS_X + RETRYMENU_SIZE_X, RETURN_POS_Y, 0.0f);
	g_vertexWkReturn[2].vtx = D3DXVECTOR3(RETURN_POS_X, RETURN_POS_Y + RETRYMENU_SIZE_Y, 0.0f);
	g_vertexWkReturn[3].vtx = D3DXVECTOR3(RETURN_POS_X + RETRYMENU_SIZE_X, RETURN_POS_Y + RETRYMENU_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkReturn[0].rhw =
	g_vertexWkReturn[1].rhw =
	g_vertexWkReturn[2].rhw =
	g_vertexWkReturn[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkReturn[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkReturn[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkReturn[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkReturn[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���j���[�F�̐ݒ�
//=============================================================================
void SetRetryMenuDiffuse(int menu)
{
	switch (menu)
	{
	case 0:
		g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		break;
	case 1:
		g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

		g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		break;
	}
}

