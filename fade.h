//=============================================================================
//
// フェード処理 [fade.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once


//*************************************
// フェードの状態
//*************************************
enum FADE
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_MUSIC_STOP,
	FADE_OUT,			// フェードアウト処理
	FADE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(int type);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, E_SCENE next, int sno);
FADE GetFade(void);
int GetSceneold(void);
int SetSceneold(void);
