//=============================================================================
//
// BG���� [bg.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

// �}�N����`
#define BG_TEXTURE			_T("data/TEXTURE/��bg_001.png")	// �T���v���p�摜
#define BG_SIZE_W			(640)	// �e�N�X�`���T�C�Y
#define BG_SIZE_H			(480)	// ����
#define BG_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BG_POS_Y			(0)		// ����
#define NUM_BG				(2)		//�w�i�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
void *GetBG(void);

