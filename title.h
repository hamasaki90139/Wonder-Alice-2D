//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE01			_T("data/TEXTURE/★titlebg_002.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE02			_T("data/TEXTURE/★titlealice_001.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO		_T("data/TEXTURE/★title_001.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_NEWGAME	_T("data/TEXTURE/★newgame_001.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_EXIT		_T("data/TEXTURE/★exit_001.png")		// 読み込むテクスチャファイル名

#define	TITLE01_POS_X			(0)								// タイトルの表示位置
#define	TITLE01_POS_Y			(0)								// タイトルの表示位置
#define	TITLE01_SIZE_X			(640)							// タイトルの幅
#define	TITLE01_SIZE_Y			(480)							// タイトルの高さ
#define	TITLE02_POS_X			(80)							// タイトルの表示位置
#define	TITLE02_POS_Y			(-30)							// タイトルの表示位置
#define	TITLE02_SIZE_X			(550)							// タイトルの幅
#define	TITLE02_SIZE_Y			(550)							// タイトルの高さ

#define	TITLELOGO_POS_X			(15)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y			(80)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X		(400)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y		(80)							// タイトルロゴの高さ
#define	TITLE_NEWGAME_POS_X		(190)							// タイトルロゴの表示位置
#define	TITLE_NEWGAME_POS_Y		(250)							// タイトルロゴの表示位置
#define	TITLE_EXIT_POS_X		(190)							// タイトルロゴの表示位置
#define	TITLE_EXIT_POS_Y		(350)							// タイトルロゴの表示位置
#define	TITLE_MENU_SIZE_X		(250)							// タイトルロゴの幅
#define	TITLE_MENU_SIZE_Y		(60)							// タイトルロゴの高さ

#define MENU_MAX				(2)								//メニュー数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

