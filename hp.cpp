//=============================================================================
//
// HP���� [hp.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "hp.h"
#include "player.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHp(void);
void SetTextureHp(int hpPattern);
void SetTextureMp(int mpPattern);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureHp = NULL;			// �e�N�X�`���ւ̃|���S��
static LPDIRECT3DTEXTURE9		g_pD3DTextureMp = NULL;			// �e�N�X�`���ւ̃|���S��

static VERTEX_2D				g_vertexWkHp[NUM_VERTEX];	// ���_���i�[���[�N
static VERTEX_2D				g_vertexWkMp[NUM_VERTEX];	// ���_���i�[���[�N

static D3DXVECTOR3				g_posHp;						// �|���S���̈ړ���
static D3DXVECTOR3				g_posMp;						// �|���S���̈ړ���

static int						g_Hp;						// HP
static MP						mpWk;						// MP�\����

static int						g_PatternHp;				// �A�j���[�V�����p�^�[���i���o�[
static int						g_PatternMp;				// �A�j���[�V�����p�^�[���i���o�[

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			HP_TEXTURE,						// �t�@�C���̖��O
			&g_pD3DTextureHp);					// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			MP_TEXTURE,						// �t�@�C���̖��O
			&g_pD3DTextureMp);					// �ǂݍ��ރ������̃|�C���^

	}

	g_posHp = D3DXVECTOR3((float)HP_POS_X, (float)HP_POS_Y, 0.0f);
	g_Hp = HP_5;						//HP�𖞃^���ɂ���
	g_PatternHp = g_Hp;					//�A�j���[�V�����p�^�[����HP�𓯊�������

	g_posMp = D3DXVECTOR3((float)MP_POS_X, (float)MP_POS_Y, 0.0f);
	mpWk.mp = MP_0;						////MP������������
	g_PatternMp = mpWk.mp;				//�A�j���[�V�����p�^�[����HP�𓯊�������

	// ���_���̍쐬
	MakeVertexHp();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHp(void)
{
	if (g_pD3DTextureHp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureHp->Release();
		g_pD3DTextureHp = NULL;
	}

	if (g_pD3DTextureMp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMp->Release();
		g_pD3DTextureMp = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHp(void)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������

	// ���t���[�����s����鏈�����L�q����

	SetTextureHp(g_Hp);

	//HP�摜�̃p�^�[��
	switch (g_Hp)
	{
	case 0:
		g_PatternHp = HP_0;
		player->use = false;
		break;
	case 1:
		g_PatternHp = HP_1;
		break;
	case 2:
		g_PatternHp = HP_2;
		break;
	case 3:
		g_PatternHp = HP_3;
		break;
	case 4:
		g_PatternHp = HP_4;
		break;
	case 5:
		g_PatternHp = HP_5;
		break;

	}

	//MP�摜�̃p�^�[��
	switch (mpWk.mp)
	{
	case 0:
		g_PatternMp = MP_0;
		break;
	case 1:
		g_PatternMp = MP_1;
		break;
	case 2:
		g_PatternMp = MP_2;
		break;
	case 3:
		g_PatternMp = MP_3;
		break;
	case 4:
		g_PatternMp = MP_4;
		break;
	case 5:
		g_PatternMp = MP_5;
		break;
	case 6:
		g_PatternMp = MP_6;
		break;
	}

	SetTextureHp(g_Hp);
	SetTextureMp(mpWk.mp);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHp(void)
{
	//HP
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureHp);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWkHp, sizeof(VERTEX_2D));

	//MP
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureMp);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWkMp, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	g_vertexWkHp[0].vtx = D3DXVECTOR3(g_posHp.x, g_posHp.y, 0.0f);
	g_vertexWkHp[1].vtx = D3DXVECTOR3(g_posHp.x + HP_SIZE_W, g_posHp.y, 0.0f);
	g_vertexWkHp[2].vtx = D3DXVECTOR3(g_posHp.x, g_posHp.y + HP_SIZE_H, 0.0f);
	g_vertexWkHp[3].vtx = D3DXVECTOR3(g_posHp.x + HP_SIZE_W, g_posHp.y + HP_SIZE_H, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkHp[0].rhw =
	g_vertexWkHp[1].rhw =
	g_vertexWkHp[2].rhw =
	g_vertexWkHp[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkHp[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkHp[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkHp[1].tex = D3DXVECTOR2(1.0f / HP_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	g_vertexWkHp[2].tex = D3DXVECTOR2(0.0f, 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y);
	g_vertexWkHp[3].tex = D3DXVECTOR2(1.0f / HP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y);

	// ���_���W�̐ݒ�
	g_vertexWkMp[0].vtx = D3DXVECTOR3(g_posMp.x, g_posMp.y, 0.0f);
	g_vertexWkMp[1].vtx = D3DXVECTOR3(g_posMp.x + MP_SIZE_W, g_posMp.y, 0.0f);
	g_vertexWkMp[2].vtx = D3DXVECTOR3(g_posMp.x, g_posMp.y + MP_SIZE_H, 0.0f);
	g_vertexWkMp[3].vtx = D3DXVECTOR3(g_posMp.x + MP_SIZE_W, g_posMp.y + MP_SIZE_H, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkMp[0].rhw =
	g_vertexWkMp[1].rhw =
	g_vertexWkMp[2].rhw =
	g_vertexWkMp[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkMp[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkMp[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkMp[1].tex = D3DXVECTOR2(1.0f / MP_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	g_vertexWkMp[2].tex = D3DXVECTOR2(0.0f, 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y);
	g_vertexWkMp[3].tex = D3DXVECTOR2(1.0f / MP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y);
	
	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureHp(int hpPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = hpPattern % HP_TEXTURE_PATTERN_DIVIDE_X;
	int y = hpPattern / HP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / HP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWkHp[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWkHp[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWkHp[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWkHp[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureMp(int mpPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = mpPattern % MP_TEXTURE_PATTERN_DIVIDE_X;
	int y = mpPattern / MP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / MP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWkMp[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWkMp[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWkMp[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWkMp[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddHp(int add)
{
	g_Hp += add;

	if (g_Hp >= HP_MAX)
	{
		g_Hp = HP_MAX;
	}
}

//=============================================================================
// MP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddMp(int add)
{
	mpWk.mp += add;

	if (mpWk.mp >= MP_MAX)
	{
		mpWk.mp = MP_MAX;
	}
	if (mpWk.mp < 0)
	{
		mpWk.mp = 0;
	}
}

//=============================================================================
// HP�擾�֐�
//=============================================================================
MP *GetMp(void)
{
	return(&mpWk);
}
