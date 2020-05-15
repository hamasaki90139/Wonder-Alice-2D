//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIAL01		_T("data/TEXTURE/��tutorial_001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIAL02		_T("data/TEXTURE/��tutorial_003.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TUTORIAL_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_SIZE_X		(640)							// �^�C�g���̕�
#define	TUTORIAL_SIZE_Y		(480)							// �^�C�g���̍���

// ��ʑJ�ڒ萔
enum E_TUTORIAL
{
	TUTORIAL01,
	TUTORIAL02,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

