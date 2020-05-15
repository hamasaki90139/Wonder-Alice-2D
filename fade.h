//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once


//*************************************
// �t�F�[�h�̏��
//*************************************
enum FADE
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_MUSIC_STOP,
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(int type);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, E_SCENE next, int sno);
FADE GetFade(void);
int GetSceneold(void);
int SetSceneold(void);
