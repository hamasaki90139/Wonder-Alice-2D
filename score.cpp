//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#include "main.h"
#include "score.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// �e�N�X�`���ւ̃|���S��
static VERTEX_2D				g_vertexWk[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

static SCORE					scoreWk;				// �X�R�A�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			SCORE_TEXTURE,						// �t�@�C���̖��O
			&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^
	}

	scoreWk.posScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	scoreWk.score = 0;
	scoreWk.score_mag = SCORE_MAG_MIN;		//�X�R�A�{��������

	// ���_���̍쐬
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if( g_pD3DTexture != NULL )
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	// ���t���[�����s����鏈�����L�q����
	SetTextureScore();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, g_pD3DTexture );

	// �X�R�A
	for( int i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWk[i][0], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float habaX = SCORE_SIZE_W;	// �����̉���
	
	// ��������������
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_���W�̐ݒ�
		g_vertexWk[i][0].vtx.x = -habaX * i + scoreWk.posScore.x;
		g_vertexWk[i][0].vtx.y = scoreWk.posScore.y;
		g_vertexWk[i][0].vtx.z = 0.0f;
		g_vertexWk[i][1].vtx.x = -habaX * i + scoreWk.posScore.x + SCORE_SIZE_W;
		g_vertexWk[i][1].vtx.y = scoreWk.posScore.y;
		g_vertexWk[i][1].vtx.z = 0.0f;
		g_vertexWk[i][2].vtx.x = -habaX * i + scoreWk.posScore.x;
		g_vertexWk[i][2].vtx.y = scoreWk.posScore.y + SCORE_SIZE_H;
		g_vertexWk[i][2].vtx.z = 0.0f;
		g_vertexWk[i][3].vtx.x = -habaX * i + scoreWk.posScore.x + SCORE_SIZE_W;
		g_vertexWk[i][3].vtx.y = scoreWk.posScore.y + SCORE_SIZE_H;
		g_vertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		g_vertexWk[i][0].rhw =
		g_vertexWk[i][1].rhw =
		g_vertexWk[i][2].rhw =
		g_vertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_vertexWk[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		g_vertexWk[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		g_vertexWk[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		g_vertexWk[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	int i;
	int number = scoreWk.score;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWk[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		g_vertexWk[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		g_vertexWk[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		g_vertexWk[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddScore( int add ,int mag)
{
 	if (add <= 0)		//�}�C�i�X�����̎��͔{���ݒ肵�Ȃ�
	{
		scoreWk.score += add;
	}
	else if (mag == SCORE_MAG_MIN)	//1�{�Ȃ炻�̂܂܃X�R�A���Z
	{
		scoreWk.score += add;
	}
	else
	{
		scoreWk.score += add*mag;	//2�{�ȏ�Ȃ�X�R�A�~�{��
	}

	if (scoreWk.score > SCORE_MAX)	//MAX�l����
	{
		scoreWk.score = SCORE_MAX;
	}
	if (scoreWk.score < SCORE_MIN)	//MIN�l����
	{
		scoreWk.score = SCORE_MIN;
	}
}

//=============================================================================
// �X�R�A�擾�֐�
//=============================================================================
SCORE *GetScore(void)
{
	return(&scoreWk);
}