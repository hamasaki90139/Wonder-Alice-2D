//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT01				_T("data/TEXTURE/��titlebg_003.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT02				_T("data/TEXTURE/��queen_001.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT03				_T("data/TEXTURE/��overalice_001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMECLEAR		_T("data/TEXTURE/��gameclear_001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMEOVER			_T("data/TEXTURE/��gameover_001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT01_POS_X			(0)							// ���U���g�̕\���ʒu
#define	RESULT01_POS_Y			(0)							// ���U���g�̕\���ʒu
#define	RESULT01_SIZE_X			(800)						// ���U���g�̕�
#define	RESULT01_SIZE_Y			(600)						// ���U���g�̍���
#define	RESULT02_POS_X			(390)						// ���U���g�̕\���ʒu
#define	RESULT02_POS_Y			(220)						// ���U���g�̕\���ʒu
#define	RESULT02_SIZE_X			(256)						// ���U���g�̕�
#define	RESULT02_SIZE_Y			(256)						// ���U���g�̍���
#define	RESULT03_POS_X			(360)						// ���U���g�̕\���ʒu
#define	RESULT03_POS_Y			(200)						// ���U���g�̕\���ʒu
#define	RESULT03_SIZE_X			(256)						// ���U���g�̕�
#define	RESULT03_SIZE_Y			(256)						// ���U���g�̍���

#define	RESULTLOGO_POS_X		(80)						// ���U���g���S�̕\���ʒu
#define	RESULTLOGO_POS_Y		(50)						// ���U���g���S�̕\���ʒu
#define	RESULTLOGO_SIZE_X		(480)						// ���U���g���S�̕�
#define	RESULTLOGO_SIZE_Y		(80)						// ���U���g���S�̍���

#define RESULTSCORE_SIZE_W		(64)						// �e�N�X�`���T�C�Y
#define RESULTSCORE_SIZE_H		(128)						// ����
#define	RESULTSCORE_POS_X		(410)															// �X�R�A�̕�
#define	RESULTSCORE_POS_Y		((SCREEN_HEIGHT/2)-(RESULTSCORE_SIZE_H/2))						// �X�R�A�̍���
#define RESULT_MENU_MAX			(2)							//���U���g�����j���[

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
