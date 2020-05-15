//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

// マクロ定義
#define EFFECT_TEXTURE			_T("data/TEXTURE/★effect_001.png")	// 画像
#define EFFECT_TEXTURE_SIZE_X	(64/2)		// テクスチャサイズ
#define EFFECT_TEXTURE_SIZE_Y	(64/2)		// 同上

#define EFFECT_TEXTURE_PATTERN_DIVIDE_X	(4)	// アニメパターンのテクスチャ内分割数（X)
#define EFFECT_TEXTURE_PATTERN_DIVIDE_Y	(4)	// アニメパターンのテクスチャ内分割数（Y)
#define EFFECT_ANIM_PATTERN_NUM			(EFFECT_TEXTURE_PATTERN_DIVIDE_X*EFFECT_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define EFFECT_TIME_ANIMATION			(1)	// アニメーションの切り替わるカウント


#define EFFECT_NUM_PARTS 16
#define EFFECT_NUM_EFFECTS 10

enum {
	EFFECT_TYPE_PLAYER,
	EFFECT_TYPE_ENEMY,
	EFFECT_TYPE_ITEM,

};


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エフェクト構造体
{
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	int				liveTime;

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	bool			isFinish;
}PARTICLE;

typedef struct	// エフェクト構造体
{
	int				use;
	int				isEnding;
	bool			isRemoveOnFinish;

	D3DXVECTOR3		pos;						// ポリゴンの移動量

	int				duration;
	int				elapsed;
	int				numFinish;

	int				effectCount;
	int				emitCounter;

	PARTICLE		pParticle[EFFECT_NUM_PARTS];

}EFFECT;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(float x, float y, int duration, int type);