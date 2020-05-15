//=============================================================================
//
// 敵処理 [enemy.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once


// マクロ定義
#define ENEMY_TEXTURE01			_T("data/TEXTURE/★heart02m.png")	// 画像
#define ENEMY_TEXTURE02			_T("data/TEXTURE/★heart03m.png")	// 画像
#define ENEMY_TEXTURE03			_T("data/TEXTURE/★heart04m.png")	// 画像
#define ENEMY_TEXTURE04			_T("data/TEXTURE/★heart05m.png")	// 画像
#define ENEMY_TEXTURE05			_T("data/TEXTURE/★heart06m.png")	// 画像
#define ENEMY_TEXTURE06			_T("data/TEXTURE/★heart07m.png")	// 画像
#define ENEMY_TEXTURE07			_T("data/TEXTURE/★heart08m.png")	// 画像
#define ENEMY_TEXTURE08			_T("data/TEXTURE/★heart09m.png")	// 画像
#define ENEMY_TEXTURE09			_T("data/TEXTURE/★heart10m.png")	// 画像
#define ENEMY_TEXTURE10			_T("data/TEXTURE/★dia02m.png")		// 画像
#define ENEMY_TEXTURE11			_T("data/TEXTURE/★dia03m.png")		// 画像
#define ENEMY_TEXTURE12			_T("data/TEXTURE/★dia04m.png")		// 画像
#define ENEMY_TEXTURE13			_T("data/TEXTURE/★dia05m.png")		// 画像
#define ENEMY_TEXTURE14			_T("data/TEXTURE/★dia06m.png")		// 画像
#define ENEMY_TEXTURE15			_T("data/TEXTURE/★dia07m.png")		// 画像
#define ENEMY_TEXTURE16			_T("data/TEXTURE/★dia08m.png")		// 画像
#define ENEMY_TEXTURE17			_T("data/TEXTURE/★dia09m.png")		// 画像
#define ENEMY_TEXTURE18			_T("data/TEXTURE/★dia10m.png")		// 画像
#define ENEMY_TEXTURE19			_T("data/TEXTURE/★club02m.png")	// 画像
#define ENEMY_TEXTURE20			_T("data/TEXTURE/★club03m.png")	// 画像
#define ENEMY_TEXTURE21			_T("data/TEXTURE/★club04m.png")	// 画像
#define ENEMY_TEXTURE22			_T("data/TEXTURE/★club05m.png")	// 画像
#define ENEMY_TEXTURE23			_T("data/TEXTURE/★club06m.png")	// 画像
#define ENEMY_TEXTURE24			_T("data/TEXTURE/★club07m.png")	// 画像
#define ENEMY_TEXTURE25			_T("data/TEXTURE/★club08m.png")	// 画像
#define ENEMY_TEXTURE26			_T("data/TEXTURE/★club09m.png")	// 画像
#define ENEMY_TEXTURE27			_T("data/TEXTURE/★club10m.png")	// 画像
#define ENEMY_TEXTURE28			_T("data/TEXTURE/★spade02m.png")	// 画像
#define ENEMY_TEXTURE29			_T("data/TEXTURE/★spade03m.png")	// 画像
#define ENEMY_TEXTURE30			_T("data/TEXTURE/★spade04m.png")	// 画像
#define ENEMY_TEXTURE31			_T("data/TEXTURE/★spade05m.png")	// 画像
#define ENEMY_TEXTURE32			_T("data/TEXTURE/★spade06m.png")	// 画像
#define ENEMY_TEXTURE33			_T("data/TEXTURE/★spade07m.png")	// 画像
#define ENEMY_TEXTURE34			_T("data/TEXTURE/★spade08m.png")	// 画像
#define ENEMY_TEXTURE35			_T("data/TEXTURE/★spade09m.png")	// 画像
#define ENEMY_TEXTURE36			_T("data/TEXTURE/★spade10m.png")	// 画像
#define ENEMY_TEXTURE_SIZE_X	(100/2)		// テクスチャサイズ
#define ENEMY_TEXTURE_SIZE_Y	(100/2)		// 同上

#define ENEMY_TEXTURE_PATTERN_DIVIDE_X	(2)			// アニメパターンのテクスチャ内分割数（X)
#define ENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define ENEMY_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define ENEMY_TIME_ANIMATION			(10)		// アニメーションの切り替わるカウント

#define ENEMY_MAX						(36)		// 敵の最大数
#define ENEMY_Y_MAX						(400)		//エネミーのY座標最大値
#define	ENEMY_ROT_CNT_MAX				(30)		// 30フレームの回転


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	D3DXVECTOR3		fall;						// 落下量
	bool			rotflag;					// 回転フラグ　	true:左　false:右
	int				rot_cnt;					// 何フレーム回転しているか
	int				rot_cnt_max;				// 何フレーム回転しているか
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度
} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);


