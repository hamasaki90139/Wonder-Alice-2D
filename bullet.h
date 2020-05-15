//=============================================================================
//
// バレット処理 [bullet.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

// マクロ定義
#define BULLET_TEXTURE01			_T("data/TEXTURE/★heart_001.png")	// 画像
#define BULLET_TEXTURE02			_T("data/TEXTURE/★dia_001.png")	// 画像
#define BULLET_TEXTURE03			_T("data/TEXTURE/★club_001.png")	// 画像
#define BULLET_TEXTURE04			_T("data/TEXTURE/★spade_001.png")	// 画像
#define BULLET_TEXTURE_SIZE_X	(50/2)		// テクスチャサイズ
#define BULLET_TEXTURE_SIZE_Y	(50/2)		// 同上

#define BULLET_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define BULLET_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define BULLET_ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// アニメーションパターン数
#define BULLET_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント

#define BULLET_MAX						(100)	// バレットの最大数
#define BULLET_SPEED					(4.0f)		// バレットの移動スピード
#define BULLET_CNT						(4)		//一度に発射できるバレットの数
#define CHARGE_CNT						(3) //エネミー3体につきチャージ+1

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureBullet;// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	int				type;						// 弾の種類
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// 半径
	float			BaseAngle;					// 角度			

} BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, int type);
BULLET *GetBullet(void);


