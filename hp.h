//=============================================================================
//
// HP処理 [hp.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

// マクロ定義
#define HP_TEXTURE		_T("data/TEXTURE/★hp_001.png")	// サンプル用画像
#define MP_TEXTURE		_T("data/TEXTURE/★mp_001.png")	// サンプル用画像
#define HP_SIZE_W		(500)		// テクスチャサイズ
#define HP_SIZE_H		(60)		// 同上
#define MP_SIZE_W		(180)		// テクスチャサイズ
#define MP_SIZE_H		(20)		// 同上
#define HP_POS_X		(0)		// ポリゴンの初期位置X
#define HP_POS_Y		(0)		// 同上
#define MP_POS_X		(10)		// ポリゴンの初期位置X
#define MP_POS_Y		(60)		// 同上
#define HP_MAX			(5)		// スコアの最大値
#define MP_MAX			(6)		//チャージゲージの最大値
#define MP_UNIT			(6)		//チャージ攻撃１回に消費するMP量

#define HP_TEXTURE_PATTERN_DIVIDE_X	(1)			// アニメパターンのテクスチャ内分割数（X)
#define HP_TEXTURE_PATTERN_DIVIDE_Y	(6)			// アニメパターンのテクスチャ内分割数（Y)
#define HP_ANIM_PATTERN_NUM			(HP_TEXTURE_PATTERN_DIVIDE_X*HP_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define HP_TIME_ANIMATION			(4)			// アニメーションの切り替わるカウント

#define MP_TEXTURE_PATTERN_DIVIDE_X	(1)			// アニメパターンのテクスチャ内分割数（X)
#define MP_TEXTURE_PATTERN_DIVIDE_Y	(7)			// アニメパターンのテクスチャ内分割数（Y)
#define MP_ANIM_PATTERN_NUM			(HP_TEXTURE_PATTERN_DIVIDE_X*HP_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define MP_TIME_ANIMATION			(4)			// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
// アニメーション分類定数(HP)
enum HP_A
{
	HP_0,
	HP_1,
	HP_2,
	HP_3,
	HP_4,
	HP_5
};

// アニメーション分類定数(MP)
enum MP_A
{
	MP_0,
	MP_1,
	MP_2,
	MP_3,
	MP_4,
	MP_5,
	MP_6
};

typedef struct	// MP構造体
{
	int							mp;				// MP
}MP;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHp(int type);
void UninitHp(void);
void UpdateHp(void);
void DrawHp(void);
void AddHp(int add);
void AddMp(int add);
MP *GetMp(void);

