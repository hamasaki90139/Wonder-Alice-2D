//=============================================================================
//
// サウンド処理 [sound.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#define SE_MAX	(1)		//効果音繰り返し回数

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
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
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

#endif
