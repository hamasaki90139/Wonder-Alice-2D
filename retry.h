//=============================================================================
//
// ���g���C��ʏ��� [retry.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	TEXTURE_TITLE_NEWGAME	_T("data/TEXTURE/��newgame_001.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_TITLE_EXIT		_T("data/TEXTURE/��exit_001.png")		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	RETRY_POS_X			(190)								// ���g���C�̕\���ʒu
#define	RETRY_POS_Y			(250)								// ���g���C�̕\���ʒu
#define	RETRYMENU_SIZE_X	(250)							// �^�C�g���̕�
#define	RETRYMENU_SIZE_Y	(60)							// �^�C�g���̍���
#define	RETURN_POS_X		(190)							// �^�C�g���̕\���ʒu
#define RETURN_POS_Y		(350)							// �^�C�g���̕\���ʒu
//#define	TITLE02_SIZE_X			(550)							// �^�C�g���̕�
//#define	TITLE02_SIZE_Y			(550)							// �^�C�g���̍���
//
//#define	TITLELOGO_POS_X			(15)							// �^�C�g�����S�̕\���ʒu
//#define	TITLELOGO_POS_Y			(80)							// �^�C�g�����S�̕\���ʒu
//#define	TITLELOGO_SIZE_X		(400)							// �^�C�g�����S�̕�
//#define	TITLELOGO_SIZE_Y		(80)							// �^�C�g�����S�̍���
//#define	TITLE_NEWGAME_POS_X		(190)							// �^�C�g�����S�̕\���ʒu
//#define	TITLE_NEWGAME_POS_Y		(250)							// �^�C�g�����S�̕\���ʒu
//#define	TITLE_EXIT_POS_X		(190)							// �^�C�g�����S�̕\���ʒu
//#define	TITLE_EXIT_POS_Y		(350)							// �^�C�g�����S�̕\���ʒu
//#define	TITLE_MENU_SIZE_X		(250)							// �^�C�g�����S�̕�
//#define	TITLE_MENU_SIZE_Y		(60)							// �^�C�g�����S�̍���
//
//#define MENU_MAX				(2)								//���j���[��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRetry(int type);
void UninitRetry(void);
void UpdateRetry(void);
void DrawRetry(void);

