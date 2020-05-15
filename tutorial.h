//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TUTORIAL01		_T("data/TEXTURE/★tutorial_001.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIAL02		_T("data/TEXTURE/★tutorial_003.png")			// 読み込むテクスチャファイル名
#define	TUTORIAL_POS_X			(0)								// タイトルの表示位置
#define	TUTORIAL_POS_Y			(0)								// タイトルの表示位置
#define	TUTORIAL_SIZE_X		(640)							// タイトルの幅
#define	TUTORIAL_SIZE_Y		(480)							// タイトルの高さ

// 画面遷移定数
enum E_TUTORIAL
{
	TUTORIAL01,
	TUTORIAL02,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

