//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#define SE_MAX	(1)		//���ʉ��J��Ԃ���

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_TITLE,		// BGM01
	SOUND_LABEL_BGM_TUTORIAL,	// BGM02
	SOUND_LABEL_BGM_GAME,		// BGM03
	SOUND_LABEL_BGM_GAMECLEAR,	// BGM04
	SOUND_LABEL_BGM_GAMEOVER,	// BGM05
	SOUND_LABEL_SE_BULLET,		// SE01
	SOUND_LABEL_SE_HIT,			// SE02
	SOUND_LABEL_SE_DAMAGE,		// SE03
	SOUND_LABEL_SE_SCOREUP,		// SE04
	SOUND_LABEL_SE_HPUP,		// SE05
	SOUND_LABEL_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

#endif
