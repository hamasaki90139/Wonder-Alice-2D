//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexLogo(void);
void SetVertexLogoColor(void);
void SetMenuDiffuse(int menu);


#define	LOGO_HIGHT			(80)							// ���S�̍���
#define LOGO_W				(480)							// ��
#define	PI					( D3DX_PI )						// �~����
#define	DEG2RAD( kakudo )	( ((kakudo)*PI)/180 )			// 360�x�����W�A���ɕϊ�����

#define	MOZAIKU_SPEED		(0.5f)							// ���U�C�N�̈ړ����x
#define	MOZAIKU_BAIRITU		(3)								// ���U�C�N�̑傫��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle1 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle2 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleNewgame = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleExit = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTitle1[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitle2[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];				// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleNewgame[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleExit[NUM_VERTEX];					// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo2[LOGO_HIGHT][NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo3[LOGO_W][NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo4[LOGO_HIGHT][LOGO_W][NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo5[LOGO_HIGHT][LOGO_W][NUM_VERTEX];	// ���_���i�[���[�N

static D3DXCOLOR		g_color;

float	sinbuf[LOGO_HIGHT];		// sin
float	sinbuf3[LOGO_W];		// sin
float	sinsize = 0;			// 200.0f;		// ���a

float	mx, my;					// ���U�C�N�̋N�_
float	mb;						// ���U�C�N�̔{��

static int menu; 						//���j���[�p�ϐ�


//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		/*�e�N�X�`���̓ǂݍ���*/
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE01,				// �t�@�C���̖��O
			&g_pD3DTextureTitle1);		// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE02,				// �t�@�C���̖��O
			&g_pD3DTextureTitle2);		// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_LOGO,			// �t�@�C���̖��O
			&g_pD3DTextureTitleLogo);	// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_NEWGAME,			// �t�@�C���̖��O
			&g_pD3DTextureTitleNewgame);	// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_EXIT,			// �t�@�C���̖��O
			&g_pD3DTextureTitleExit);	// �ǂݍ��ރ������[
	}

	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	menu = 0;	//���j���[������

	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if (g_pD3DTextureTitle1 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitle1->Release();
		g_pD3DTextureTitle1 = NULL;
	}

	if (g_pD3DTextureTitle2 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitle2->Release();
		g_pD3DTextureTitle2 = NULL;
	}

	if (g_pD3DTextureTitleLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DTextureTitleNewgame != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleNewgame->Release();
		g_pD3DTextureTitleNewgame = NULL;
	}

	if (g_pD3DTextureTitleExit != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleExit->Release();
		g_pD3DTextureTitleExit = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
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
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
	case 1:
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			exit(-1);		//�Q�[���I��
		}
		// �Q�[���p�b�h�ňړ�����
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			exit(-1);		//�Q�[���I��
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			exit(-1);		//�Q�[���I��
		}
		break;
	}

	SetVertexLogo();

	SetVertexLogoColor();

	SetMenuDiffuse(menu);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitle1);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle1, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitle2);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle2, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleNewgame);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleNewgame, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleExit);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleExit, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkTitle1[0].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkTitle1[1].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkTitle1[2].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);
	g_vertexWkTitle1[3].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitle1[0].rhw =
		g_vertexWkTitle1[1].rhw =
		g_vertexWkTitle1[2].rhw =
		g_vertexWkTitle1[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitle1[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitle1[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle1[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle1[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle1[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	g_vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE02_POS_X, TITLE02_POS_Y, 0.0f);
	g_vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE02_POS_X + TITLE02_SIZE_X, TITLE02_POS_Y, 0.0f);
	g_vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE02_POS_X, TITLE02_POS_Y + TITLE02_SIZE_Y, 0.0f);
	g_vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE02_POS_X + TITLE02_SIZE_X, TITLE02_POS_Y + TITLE02_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitle2[0].rhw =
		g_vertexWkTitle2[1].rhw =
		g_vertexWkTitle2[2].rhw =
		g_vertexWkTitle2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitle2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitle2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_���W�̐ݒ�
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleLogo[0].rhw =
		g_vertexWkTitleLogo[1].rhw =
		g_vertexWkTitleLogo[2].rhw =
		g_vertexWkTitleLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//NEWGAME
	// ���_���W�̐ݒ�
	g_vertexWkTitleNewgame[0].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X, TITLE_NEWGAME_POS_Y, 0.0f);
	g_vertexWkTitleNewgame[1].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X + TITLE_MENU_SIZE_X, TITLE_NEWGAME_POS_Y, 0.0f);
	g_vertexWkTitleNewgame[2].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X, TITLE_NEWGAME_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);
	g_vertexWkTitleNewgame[3].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X + TITLE_MENU_SIZE_X, TITLE_NEWGAME_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleNewgame[0].rhw =
		g_vertexWkTitleNewgame[1].rhw =
		g_vertexWkTitleNewgame[2].rhw =
		g_vertexWkTitleNewgame[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleNewgame[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleNewgame[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleNewgame[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleNewgame[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//EXIT
	// ���_���W�̐ݒ�
	g_vertexWkTitleExit[0].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X, TITLE_EXIT_POS_Y, 0.0f);
	g_vertexWkTitleExit[1].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X + TITLE_MENU_SIZE_X, TITLE_EXIT_POS_Y, 0.0f);
	g_vertexWkTitleExit[2].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X, TITLE_EXIT_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);
	g_vertexWkTitleExit[3].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X + TITLE_MENU_SIZE_X, TITLE_EXIT_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleExit[0].rhw =
		g_vertexWkTitleExit[1].rhw =
		g_vertexWkTitleExit[2].rhw =
		g_vertexWkTitleExit[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleExit[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleExit[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleExit[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleExit[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexLogo(void)
{
	float	tw = 1.0f;
	float	th = 1.0f / LOGO_HIGHT;
	float	w = 480.0f;
	float	h = 1.0f;
	float	x = 40.0f;
	float	y = 50.0f;

	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		float offset = sinbuf[i] * sinsize;

		// ���_���W�̐ݒ�
		g_vertexWkTitleLogo2[i][0].vtx = D3DXVECTOR3(x + offset, y + i * h, 0.0f);
		g_vertexWkTitleLogo2[i][1].vtx = D3DXVECTOR3(x + w + offset, y + i * h, 0.0f);
		g_vertexWkTitleLogo2[i][2].vtx = D3DXVECTOR3(x + offset, y + (i + 1)*h, 0.0f);
		g_vertexWkTitleLogo2[i][3].vtx = D3DXVECTOR3(x + w + offset, y + (i + 1)*h, 0.0f);

	}


	{	// �c���X
		float	tw = 1.0f / LOGO_W;
		float	th = 1.0f;
		float	w = 1.0f;		// 480.0f;
		float	h = LOGO_HIGHT;
		float	x = 40.0f;
		float	y = 150.0f;

		for (int i = 0; i < LOGO_W; i++)
		{
			float offset = sinbuf3[i] * sinsize;

			// ���_���W�̐ݒ�
			g_vertexWkTitleLogo3[i][0].vtx = D3DXVECTOR3(x + i * w, y + offset, 0.0f);
			g_vertexWkTitleLogo3[i][1].vtx = D3DXVECTOR3(x + (i + 1) * w, y + offset, 0.0f);
			g_vertexWkTitleLogo3[i][2].vtx = D3DXVECTOR3(x + i * w, y + h + offset, 0.0f);
			g_vertexWkTitleLogo3[i][3].vtx = D3DXVECTOR3(x + (i + 1) * w, y + h + offset, 0.0f);

		}
	}

	{	// �c�����X
		float	tw = 1.0f / LOGO_W;
		float	th = 1.0f / LOGO_HIGHT;
		float	w = 1.0f;		// 480.0f;
		float	h = 1.0f;
		float	x = 40.0f;
		float	y = 250.0f;

		for (int i = 0; i < LOGO_HIGHT; i++)
		{
			float offset = sinbuf[i] * sinsize;		// �����X

			for (int j = 0; j < LOGO_W; j++)
			{
				float offset3 = sinbuf3[j] * sinsize;	// �c���X

				// ���_���W�̐ݒ�
				g_vertexWkTitleLogo4[i][j][0].vtx = D3DXVECTOR3(x + j * w + offset, y + i * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][1].vtx = D3DXVECTOR3(x + (j + 1) * w + offset, y + i * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][2].vtx = D3DXVECTOR3(x + j * w + offset, y + (i + 1) * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][3].vtx = D3DXVECTOR3(x + (j + 1) * w + offset, y + (i + 1) * h + offset3, 0.0f);
			}
		}
	}


	{	// ���U�C�N
		float	tw = 1.0f / LOGO_W * mb;
		float	th = 1.0f / LOGO_HIGHT * mb;

		// �P�x���ɖ߂�
		for (int i = 0; i < LOGO_HIGHT; i++)
		{
			for (int j = 0; j < LOGO_W; j++)
			{
				// ���_�f�[�^�̐ݒ�
				g_vertexWkTitleLogo5[i][j][0].tex = g_vertexWkTitleLogo4[i][j][0].tex;
				g_vertexWkTitleLogo5[i][j][1].tex = g_vertexWkTitleLogo4[i][j][1].tex;
				g_vertexWkTitleLogo5[i][j][2].tex = g_vertexWkTitleLogo4[i][j][2].tex;
				g_vertexWkTitleLogo5[i][j][3].tex = g_vertexWkTitleLogo4[i][j][3].tex;

			}
		}

		// ���U�C�N�������{��
		for (int i = (int)my; i < (my + 40); i++)
		{
			// �N�_���摜�O�̎��͏��������Ȃ�
			if (i < 0) continue;
			if (i >= LOGO_HIGHT) continue;

			for (int j = (int)mx; j < (mx + 40); j++)
			{
				// �N�_���摜�O�̎��͏��������Ȃ�
				if (j < 0) continue;
				if (j >= LOGO_W) continue;

				// ���_�f�[�^�̐ݒ�
				for (int k = 0; k < 4; k++)
				{
					switch (rand() % 5)
					{
					case 0:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x - tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y - th;
						break;

					case 1:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x + tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y - th;
						break;

					case 2:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x + tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y + th;
						break;

					case 3:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x - tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y + th;
						break;

					case 4:
						break;

					}

				}

			}
		}

	}

}

//=============================================================================
// ���_�F�̐ݒ�
//=============================================================================
void SetVertexLogoColor(void)
{
	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		// ���ˌ��̐ݒ�
		g_vertexWkTitleLogo2[i][0].diffuse = g_color;
		g_vertexWkTitleLogo2[i][1].diffuse = g_color;
		g_vertexWkTitleLogo2[i][2].diffuse = g_color;
		g_vertexWkTitleLogo2[i][3].diffuse = g_color;
	}

	for (int i = 0; i < LOGO_W; i++)
	{
		// ���ˌ��̐ݒ�
		g_vertexWkTitleLogo3[i][0].diffuse = g_color;
		g_vertexWkTitleLogo3[i][1].diffuse = g_color;
		g_vertexWkTitleLogo3[i][2].diffuse = g_color;
		g_vertexWkTitleLogo3[i][3].diffuse = g_color;
	}

	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		for (int j = 0; j < LOGO_W; j++)
		{
			// ���ˌ��̐ݒ�
			g_vertexWkTitleLogo4[i][j][0].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][1].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][2].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][3].diffuse = g_color;
		}
	}
}

//=============================================================================
// ���j���[�F�̐ݒ�
//=============================================================================
void SetMenuDiffuse(int menu)
{
	switch (menu)
	{
	case 0:
		g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		break;
	case 1:
		g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

		g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		break;
	}
}

