//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EMISSION 1
#define EMISSION_FULL 0
#define EMISSION_RATE 1

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(int i);
void SetTextureEffect(int i, int n, int cntPattern);
void SetVertexEffect(int i, int n);
void ResetParticle(int i, int n);
void StartEffect(int i);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|���S��

static EFFECT					effectWk[EFFECT_NUM_EFFECTS];	// �G�t�F�N�g�\����

static int g_isActive = 1;
static int g_effectCount;
static int g_emitCounter = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
			EFFECT_TEXTURE,										// �t�@�C���̖��O
			&g_pD3DTextureEffect);								// �ǂݍ��ރ������̃|�C���^
	}

	// ����������
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		effectWk[i].use = false;
		effectWk[i].elapsed = 0;

		for (int n = 0; n < EFFECT_NUM_PARTS; n++) {

			effectWk[i].pParticle[n].Texture = g_pD3DTextureEffect;

			MakeVertexEffect(i);										// ���_���̍쐬

			ResetParticle(i, n);
		}
	}

	return S_OK;
}

void ResetParticle(int i, int n) {

	effectWk[i].pParticle[n].pos = D3DXVECTOR3(effectWk[i].pos.x + rand() % 30 - 15, effectWk[i].pos.y + rand() % 30 - 15, 0.0f);	// ���W�f�[�^��������
	effectWk[i].pParticle[n].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���

	effectWk[i].pParticle[n].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
	effectWk[i].pParticle[n].CountAnim = 0;										// �A�j���J�E���g��������
	effectWk[i].pParticle[n].liveTime = 30;
	effectWk[i].pParticle[n].isFinish = 0;
}

void StartEffect(int i)
{
	for (int n = 0; n < EFFECT_NUM_PARTS; n++)
	{
		ResetParticle(i, n);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if (g_pD3DTextureEffect != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++) {

		if (effectWk[i].use)
		{
			if (effectWk[i].isEnding) {
				effectWk[i].use = FALSE;
				continue;
			}

			//�G�~�b�g���L���ł���΃G�t�F�N�g�쐬�������s��
			if (effectWk[i].isRemoveOnFinish == FALSE) {

				//�G�t�F�N�g�쐬���[�g�̑�������
				if (effectWk[i].effectCount < EFFECT_NUM_PARTS) {
					effectWk[i].emitCounter++;
				}

				//�o�b�t�@�ɋ󂫂�����A�ǉ��^�C�~���O�����Ă���ΐV���ȃG�t�F�N�g��ǉ�����
				while ((effectWk[i].effectCount < EFFECT_NUM_PARTS) && (effectWk[i].emitCounter > EMISSION_RATE)) {
					//�S�̒ǉ��t���O��ON�ł���΋󂫗̈�S�ĂɐV���ȃG�t�F�N�g��ǉ�����
					if (EMISSION_FULL)
						effectWk[i].effectCount = EFFECT_NUM_PARTS;
					else {
						effectWk[i].effectCount++;
					}

					//�G�t�F�N�g�쐬���[�g�̏�����
					effectWk[i].emitCounter = 0;
				}

				effectWk[i].elapsed++;

				//���Ԓ���
				if ((effectWk[i].duration != -1) && (effectWk[i].duration < effectWk[i].elapsed)) {
					effectWk[i].isRemoveOnFinish = TRUE;
				}
			}

			int effectIndex = 0;

			//�G�t�F�N�g�̍X�V����
			while (effectIndex < effectWk[i].effectCount)
			{
				if (effectWk[i].pParticle[effectIndex].liveTime > 0) {

					//�����t���[������
					effectWk[i].pParticle[effectIndex].liveTime--;

					//�A�j���p�^�[���i�s
					if (++effectWk[i].pParticle[effectIndex].CountAnim > EFFECT_TIME_ANIMATION) {
						//�A�j���p�^�[�����ő�l�ɒB�����ꍇ�ł��I��
						if (++effectWk[i].pParticle[effectIndex].PatternAnim >= EFFECT_ANIM_PATTERN_NUM) {
							effectWk[i].pParticle[effectIndex].PatternAnim = EFFECT_ANIM_PATTERN_NUM - 1;
							effectWk[i].pParticle[effectIndex].liveTime = 0;
						}

						effectWk[i].pParticle[effectIndex].CountAnim = 0;
					}

					SetTextureEffect(i, effectIndex, effectWk[i].pParticle[effectIndex].PatternAnim);
					SetVertexEffect(i, effectIndex);						// �ړ���̍��W�Œ��_��ݒ�
					effectIndex++;
				}
				else {
					if (effectWk[i].isRemoveOnFinish) {
						if (effectWk[i].pParticle[effectIndex].isFinish == 0) {
							effectWk[i].pParticle[effectIndex].isFinish = 1;
							effectWk[i].numFinish++;
						}
						//�I������
						if (effectWk[i].numFinish == effectWk[i].effectCount) {
							effectWk[i].isEnding = TRUE;

							// ���ˌ��̏�����
							effectWk[i].pParticle[effectIndex].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

							break;
						}
						effectIndex++;
					}
					else {
						//�o�b�t�@������������
						ResetParticle(i, effectIndex);

						//�����łȂ���΃C���f�b�N�X���l�߂�
						if (effectIndex != (g_effectCount - 1)) {
							effectWk[i].pParticle[effectIndex] = effectWk[i].pParticle[effectWk[i].effectCount - 1];
							ResetParticle(i, (effectWk[i].effectCount - 1));
						}
						effectWk[i].effectCount--;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		if (effectWk[i].use) {

			for (int n = 0; n < effectWk[i].effectCount; n++) {
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, effectWk[i].pParticle[n].Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, effectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < EFFECT_NUM_PARTS; n++) {

		// ���_���W�̐ݒ�
		SetVertexEffect(i, n);
		// ���_���W�̐ݒ�
		SetTextureEffect(i, n, 0);

		// rhw�̐ݒ�
		effectWk[i].pParticle[n].vertexWk[0].rhw =
			effectWk[i].pParticle[n].vertexWk[1].rhw =
			effectWk[i].pParticle[n].vertexWk[2].rhw =
			effectWk[i].pParticle[n].vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect(int i, int n, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / EFFECT_TEXTURE_PATTERN_DIVIDE_Y;

	effectWk[i].pParticle[n].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effectWk[i].pParticle[n].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effectWk[i].pParticle[n].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effectWk[i].pParticle[n].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int i, int n)
{
	// ���_���W�̐ݒ�
	effectWk[i].pParticle[n].vertexWk[0].vtx.x = effectWk[i].pParticle[n].pos.x - EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[0].vtx.y = effectWk[i].pParticle[n].pos.y - EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[0].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[1].vtx.x = effectWk[i].pParticle[n].pos.x + EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[1].vtx.y = effectWk[i].pParticle[n].pos.y - EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[1].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[2].vtx.x = effectWk[i].pParticle[n].pos.x - EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[2].vtx.y = effectWk[i].pParticle[n].pos.y + EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[2].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[3].vtx.x = effectWk[i].pParticle[n].pos.x + EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[3].vtx.y = effectWk[i].pParticle[n].pos.y + EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�t�F�N�g�̃Z�b�g
//=============================================================================
void SetEffect(float x, float y, int duration, int type)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������

	// �������g�p�̃G�t�F�N�g��������������s���Ȃ�( =����ȏ�\���ł��Ȃ����Ď� )
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		if (effectWk[i].use == false)		// ���g�p��Ԃ̃G�t�F�N�g��������
		{
			effectWk[i].use = true;
			effectWk[i].isEnding = false;
			effectWk[i].isRemoveOnFinish = FALSE;

			effectWk[i].duration = duration;
			effectWk[i].pos.x = x;			// ���W���Z�b�g
			effectWk[i].pos.y = y;			// ���W���Z�b�g

			effectWk[i].effectCount = 0;
			effectWk[i].elapsed = 0;
			effectWk[i].emitCounter = 0;
			effectWk[i].numFinish = 0;

			for (int n = 0; n < EFFECT_NUM_PARTS; n++)
			{
				// ���ˌ��̐ݒ�
				switch (type)
				{
				case EFFECT_TYPE_PLAYER:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;

				case EFFECT_TYPE_ENEMY:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					break;

				case EFFECT_TYPE_ITEM:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					break;
				}
			}
			StartEffect(i);

			return;							// 1�Z�b�g�����̂ŏI������
		}
	}
}