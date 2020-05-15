//=============================================================================
//
// オブジェクト処理 [obstacle.h]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#pragma once

// マクロ定義
#define THORN_TEXTURE01			_T("data/TEXTURE/★thorn_001.png")	// 画像
#define BRICK_TEXTURE01			_T("data/TEXTURE/★brick_001.png")	// 画像
#define CAKE_TEXTURE01			_T("data/TEXTURE/★cake_001.png")	// 画像
#define TEA_TEXTURE01			_T("data/TEXTURE/★tea_001.png")	// 画像
#define COOKIE_TEXTURE01		_T("data/TEXTURE/★cookie_001.png")	// 画像
#define GOAL_TEXTURE01			_T("data/TEXTURE/★goal_001.png")	// 画像

#define THORN_TEXTURE_SIZE_X	(100/2)		// テクスチャサイズ
#define THORN_TEXTURE_SIZE_Y	(60/2)		// 同上
#define BRICK_TEXTURE_SIZE_X	(150/2)		// テクスチャサイズ
#define BRICK_TEXTURE_SIZE_Y	(30/2)		// 同上
#define ITEM_TEXTURE_SIZE_X	(50/2)		// テクスチャサイズ
#define ITEM_TEXTURE_SIZE_Y	(50/2)		// 同上
#define GOAL_TEXTURE_SIZE_X	(500/2)		// テクスチャサイズ
#define GOAL_TEXTURE_SIZE_Y	(500/2)		// 同上


#define OBSTACLE_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define OBSTACLE_ANIM_PATTERN_NUM			(ENEMY_TEXTURE_PATTERN_DIVIDE_X*ENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define OBSTACLE_TIME_ANIMATION			(40)	// アニメーションの切り替わるカウント

#define THORN_MAX						(10) // いばらの最大数
#define BRICK_MAX						(30) // ブロック（レンガ）の最大数
#define OBSTACLE_MAX					(20)//障害物の最大数
#define CAKE_MAX						(3) // ケーキの最大数
#define TEA_MAX							(5) // 紅茶の最大数
#define COOKIE_MAX						(5)//クッキーの最大数
#define GOAL_MAX						(1)//ゴールの最大数

#define CAKE_SCORE						(5) // ケーキのスコア倍率
#define TEA_SCORE						(2) // 紅茶のスコア倍率

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// いばら構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	bool			s_cnt;						//スコアカウント処理 true:未カウント　false:カウント済
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} THORN;

typedef struct	// ブロック構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	bool			h_cnt;						//ヒットカウント処理 true:未カウント　false:カウント済
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} BRICK;

typedef struct	// ケーキ構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	bool			b_hitcnt;					//ヒットカウント処理 true:未カウント　false:カウント済
	bool			s_cnt;						//スコアカウント処理 true:未カウント　false:カウント済
	bool			scale_plus;					//true:拡大中  false:縮小中

	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	D3DXVECTOR3		fall;						// 落下量

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				scale_cnt;					// 拡大縮小カウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} CAKE;

typedef struct	// 紅茶構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	bool			b_hitcnt;						//ヒットカウント処理 true:未カウント　false:カウント済
	bool			s_cnt;						//スコアカウント処理 true:未カウント　false:カウント済
	bool			scale_plus;					//true:拡大中  false:縮小中

	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	D3DXVECTOR3		fall;						// 落下量

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				scale_cnt;					// 拡大縮小カウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} TEA;

typedef struct	// クッキー構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	bool			b_hitcnt;						//ヒットカウント処理 true:未カウント　false:カウント済
	bool			h_cnt;						//スコアカウント処理 true:未カウント　false:カウント済
	bool			scale_plus;					//true:拡大中  false:縮小中

	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	D3DXVECTOR3		fall;						// 落下量

	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int				scale_cnt;					// 拡大縮小カウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} COOKIE;

typedef struct	// ゴール構造体
{
	LPDIRECT3DTEXTURE9		g_pD3DTextureObstacle;	// テクスチャへのポリゴン
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// オブジェクトの半径
	float			BaseAngle;					// オブジェクトの角度

} GOAL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitObstacle(int type);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);
THORN *GetThorn(void);
BRICK *GetBrick(void);
CAKE *GetCake(void);
TEA *GetTea(void);
COOKIE *GetCookie(void);
GOAL *GetGoal(void);


