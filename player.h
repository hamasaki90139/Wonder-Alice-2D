//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once


// マクロ定義
#define PLAYER_TEXTURE					_T("data/TEXTURE/★alice_009.png")	// 画像
#define PLAYER_TEXTURE_SIZE_X			(200/2)		// テクスチャサイズ
#define PLAYER_TEXTURE_SIZE_Y			(200/2)		// 同上

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(4)			// アニメパターンのテクスチャ内分割数（X)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(2)			// アニメパターンのテクスチャ内分割数（Y)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define PLAYER_TIME_ANIMATION			(10)			// アニメーションの切り替わるカウント

#define PLAYER_MAX						(1)			// プレイヤーの最大数

#define	PLAYER_JUMP_Y					(-15.0f)	// ジャンプの高さ
#define	PLAYER_JUMP_CNT_MAX				(40)		// 40フレームのジャンプ処理
#define	PLAYER_DMG_CNT_MAX				(60)		// 40フレームのダメージ色表示
#define	PLAYER_DMG_COLOR_MAX			(2)			//ダメージカラー色数
#define	PLAYER_JUMPMAX					(2)			// ジャンプ回数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	bool			dmg;						//true:ダメージを与えた　false:ダメージを与えられた
	bool			dmgflag;					//ダメージ時の処理　true:赤　false:通常
	bool			direction;					//向き　true:右　false:未使用

	D3DXVECTOR3		pos;						// ポリゴンの座標
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	
	bool			jump;						// ジャンプ中フラグ
	float			jump_y;						// ジャンプの高さ
	int				jump_cnt;					// 何フレームジャンプしているか
	int				jump_cnt_max;				// 何フレームでジャンプをするか
	int				jumppoint;					// ジャンプ回数
	D3DXVECTOR3		ofs;						// posに対するオフセット座標

	int				dmg_cnt;					//プレイヤーのダメージカウント
	float			Radius;						// プレイヤーの半径

} PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);


