//=============================================================================
//
// リトライ画面処理 [retry.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	TEXTURE_TITLE_NEWGAME	_T("data/TEXTURE/★newgame_001.png")		// 読み込むテクスチャファイル名
//#define	TEXTURE_TITLE_EXIT		_T("data/TEXTURE/★exit_001.png")		// 読み込むテクスチャファイル名

#define	RETRY_POS_X			(190)								// リトライの表示位置
#define	RETRY_POS_Y			(250)								// リトライの表示位置
#define	RETRYMENU_SIZE_X	(250)							// タイトルの幅
#define	RETRYMENU_SIZE_Y	(60)							// タイトルの高さ
#define	RETURN_POS_X		(190)							// タイトルの表示位置
#define RETURN_POS_Y		(350)							// タイトルの表示位置
//#define	TITLE02_SIZE_X			(550)							// タイトルの幅
//#define	TITLE02_SIZE_Y			(550)							// タイトルの高さ
//
//#define	TITLELOGO_POS_X			(15)							// タイトルロゴの表示位置
//#define	TITLELOGO_POS_Y			(80)							// タイトルロゴの表示位置
//#define	TITLELOGO_SIZE_X		(400)							// タイトルロゴの幅
//#define	TITLELOGO_SIZE_Y		(80)							// タイトルロゴの高さ
//#define	TITLE_NEWGAME_POS_X		(190)							// タイトルロゴの表示位置
//#define	TITLE_NEWGAME_POS_Y		(250)							// タイトルロゴの表示位置
//#define	TITLE_EXIT_POS_X		(190)							// タイトルロゴの表示位置
//#define	TITLE_EXIT_POS_Y		(350)							// タイトルロゴの表示位置
//#define	TITLE_MENU_SIZE_X		(250)							// タイトルロゴの幅
//#define	TITLE_MENU_SIZE_Y		(60)							// タイトルロゴの高さ
//
//#define MENU_MAX				(2)								//メニュー数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRetry(int type);
void UninitRetry(void);
void UpdateRetry(void);
void DrawRetry(void);

