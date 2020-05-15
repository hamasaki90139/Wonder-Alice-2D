//=============================================================================
//
// オブジェクト処理 [obstacle.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "obstacle.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexThorn(int no);
HRESULT MakeVertexBrick(int no);
HRESULT MakeVertexCake(int no);
HRESULT MakeVertexTea(int no);
HRESULT MakeVertexCookie(int no);
HRESULT MakeVertexGoal(int i);
void SetTextureThorn(int no, int cntPattern);
void SetTextureBrick(int no, int cntPattern);
void SetTextureCake(int no, int cntPattern);
void SetTextureTea(int no, int cntPattern);
void SetTextureCookie(int no, int cntPattern);
void SetTextureGoal(int i, int cntPattern);
void SetVertexThorn(int no);
void SetVertexBrick(int no);
void SetVertexCake(int no);
void SetVertexTea(int no);
void SetVertexCookie(int no);
void SetVertexGoal(int i);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static THORN				thornWk[THORN_MAX];				// いばら構造体
static BRICK				brickWk[BRICK_MAX];				// ブロック構造体
static CAKE					cakeWk[CAKE_MAX];				// ケーキ構造体
static TEA					teaWk[TEA_MAX];					// 紅茶構造体
static COOKIE				cookieWk[COOKIE_MAX];			// クッキー構造体
static GOAL					goalWk[GOAL_MAX];				// ゴール構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitObstacle(int type)
{
	srand((unsigned)time(NULL));	//ランダム初期値の初期化
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// いばらの初期化処理
	for (int i = 0; i < THORN_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				THORN_TEXTURE01,										// ファイルの名前
				&thornWk[i].g_pD3DTextureObstacle);								// 読み込むメモリのポインタ

		}

		thornWk[i].use = true;										// 使用
		thornWk[i].s_cnt = true;										// 未カウント
		thornWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 1650.0f, 440.0f, 0.0f);	// 座標データを初期化
		thornWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);			// 移動量
		thornWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		thornWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		thornWk[i].CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(THORN_TEXTURE_SIZE_X, THORN_TEXTURE_SIZE_Y);
		thornWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		thornWk[i].BaseAngle = atan2f(THORN_TEXTURE_SIZE_Y, THORN_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		thornWk[i].Texture = thornWk[i].g_pD3DTextureObstacle;

		MakeVertexThorn(i);											// 頂点情報の作成
	}

	// ブロックの初期化処理
	for (int i = 0; i < BRICK_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				BRICK_TEXTURE01,										// ファイルの名前
				&brickWk[i].g_pD3DTextureObstacle);								// 読み込むメモリのポインタ

		}

		brickWk[i].use = true;										// 使用
		brickWk[i].h_cnt = true;									//未カウント
		brickWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 1750.0f, ((rand() % (2 + 1) + 2)*100.0f), 0.0f);	// 座標データを初期化
		brickWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);			// 移動量
		brickWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		brickWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		brickWk[i].CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(BRICK_TEXTURE_SIZE_X, BRICK_TEXTURE_SIZE_Y);
		brickWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		brickWk[i].BaseAngle = atan2f(BRICK_TEXTURE_SIZE_Y, BRICK_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		brickWk[i].Texture = brickWk[i].g_pD3DTextureObstacle;

		MakeVertexBrick(i);											// 頂点情報の作成
	}

	// ケーキの初期化処理
	for (int i = 0; i < CAKE_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				CAKE_TEXTURE01,										// ファイルの名前
				&cakeWk[i].g_pD3DTextureObstacle);					// 読み込むメモリのポインタ

		}

		cakeWk[i].use = true;										// 使用
		cakeWk[i].b_hitcnt = true;									//未カウント
		cakeWk[i].s_cnt = true;										//未カウント
		cakeWk[i].scale_plus = true;								//拡大中
		cakeWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 500) + 2500.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// 座標データを初期化
		cakeWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);			// 移動量
		cakeWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量
		cakeWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		cakeWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		cakeWk[i].CountAnim = 0;									// アニメカウントを初期化
		cakeWk[i].scale_cnt = 0;									// 拡大縮小カウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		cakeWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		cakeWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		cakeWk[i].Texture = cakeWk[i].g_pD3DTextureObstacle;

		MakeVertexCake(i);											// 頂点情報の作成
	}

	// 紅茶の初期化処理
	for (int i = 0; i < TEA_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				TEA_TEXTURE01,										// ファイルの名前
				&teaWk[i].g_pD3DTextureObstacle);					// 読み込むメモリのポインタ

		}

		teaWk[i].use = true;										// 使用
		teaWk[i].b_hitcnt = true;									//未カウント
		teaWk[i].s_cnt = true;										//未カウント
		teaWk[i].scale_plus = true;									//拡大中
		teaWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 400) + 1500.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// 座標データを初期化
		teaWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);				// 移動量
		teaWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量
		teaWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		teaWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		teaWk[i].CountAnim = 0;										// アニメカウントを初期化
		teaWk[i].scale_cnt = 0;										// 拡大縮小カウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		teaWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		teaWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		teaWk[i].Texture = teaWk[i].g_pD3DTextureObstacle;

		MakeVertexTea(i);											// 頂点情報の作成
	}

	// クッキーの初期化処理
	for (int i = 0; i < COOKIE_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				COOKIE_TEXTURE01,									// ファイルの名前
				&cookieWk[i].g_pD3DTextureObstacle);				// 読み込むメモリのポインタ

		}

		cookieWk[i].use = true;										// 使用
		cookieWk[i].b_hitcnt = true;								//未カウント
		cookieWk[i].h_cnt = true;									//未カウント
		cookieWk[i].scale_plus = true;								//拡大中
		cookieWk[i].pos = D3DXVECTOR3(i* (rand() % (500 + 1) + 300) + 2000.0f, ((rand() % (2 + 1) + 1)*100.0f), 0.0f);	// 座標データを初期化
		cookieWk[i].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);			// 移動量
		cookieWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 落下量
		cookieWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転データを初期化
		cookieWk[i].PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		cookieWk[i].CountAnim = 0;									// アニメカウントを初期化
		cookieWk[i].scale_cnt = 0;									// 拡大縮小カウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(ITEM_TEXTURE_SIZE_X, ITEM_TEXTURE_SIZE_Y);
		cookieWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		cookieWk[i].BaseAngle = atan2f(ITEM_TEXTURE_SIZE_Y, ITEM_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		cookieWk[i].Texture = cookieWk[i].g_pD3DTextureObstacle;

		MakeVertexCookie(i);											// 頂点情報の作成
	}

	// ゴールの初期化処理
	for (int i = 0; i < GOAL_MAX; i++)
	{
		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				GOAL_TEXTURE01,										// ファイルの名前
				&goalWk[i].g_pD3DTextureObstacle);					// 読み込むメモリのポインタ
		}

		goalWk[i].use = false;										// 未使用
		goalWk[i].pos = D3DXVECTOR3(1000.0f, 270.0f, 0.0f);			// 座標データを初期化
		goalWk[i].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
		goalWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		goalWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		goalWk[i].CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(GOAL_TEXTURE_SIZE_X, GOAL_TEXTURE_SIZE_Y);
		goalWk[i].Radius = D3DXVec2Length(&temp);					// オブジェクトの半径を初期化
		goalWk[i].BaseAngle = atan2f(GOAL_TEXTURE_SIZE_Y, GOAL_TEXTURE_SIZE_X);	// オブジェクトの角度を初期化
		goalWk[i].Texture = goalWk[i].g_pD3DTextureObstacle;

		MakeVertexGoal(i);											// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObstacle(void)
{
	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			thornWk[i].g_pD3DTextureObstacle->Release();
			thornWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			brickWk[i].g_pD3DTextureObstacle->Release();
			brickWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			cakeWk[i].g_pD3DTextureObstacle->Release();
			cakeWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			teaWk[i].g_pD3DTextureObstacle->Release();
			teaWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			cookieWk[i].g_pD3DTextureObstacle->Release();
			cookieWk[i].g_pD3DTextureObstacle = NULL;
		}
	}

	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].g_pD3DTextureObstacle != NULL)
		{	// テクスチャの開放
			goalWk[i].g_pD3DTextureObstacle->Release();
			goalWk[i].g_pD3DTextureObstacle = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObstacle(void)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化

	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			thornWk[i].CountAnim++;
			if ((thornWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				thornWk[i].PatternAnim = (thornWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureThorn(i, thornWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			thornWk[i].pos += thornWk[i].move;

			// 画面外まで進んだ？
			if (thornWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - THORN_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
			{
				thornWk[i].use = false;
			}

			SetVertexThorn(i);						// 移動後の座標で頂点を設定
		}
	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			brickWk[i].CountAnim++;
			if ((brickWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				brickWk[i].PatternAnim = (brickWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureBrick(i, brickWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			brickWk[i].pos += brickWk[i].move;

			// 画面外まで進んだ？
			if (brickWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - BRICK_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
			{
				brickWk[i].use = false;
			}

			SetVertexBrick(i);						// 移動後の座標で頂点を設定
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			cakeWk[i].CountAnim++;
			if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				cakeWk[i].PatternAnim = (cakeWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureCake(i, cakeWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			cakeWk[i].pos += cakeWk[i].move;

			D3DXVECTOR3 oldpos = cakeWk[i].pos;
			cakeWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量

			cakeWk[i].pos += cakeWk[i].move;

			//落下処理
			if (cakeWk[i].pos.x < SCREEN_WIDTH)
			{
				if (cakeWk[i].b_hitcnt == false)
				{
					cakeWk[i].fall.y += 0.5f;
					cakeWk[i].rot.z += 0.05f;
					cakeWk[i].pos.y += cakeWk[i].fall.y;

					// 地面設定
					if ((cakeWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						cakeWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// ケーキとブロック(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((cakeWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(cakeWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(cakeWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(cakeWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					cakeWk[i].pos.y = oldpos.y;
					cakeWk[i].b_hitcnt = true;
				}
				else
				{
					cakeWk[i].b_hitcnt = false;
				}
			}

			// 画面外まで進んだ？
			if (cakeWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
			{
				cakeWk[i].use = false;
			}

			SetVertexCake(i);						// 移動後の座標で頂点を設定
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			teaWk[i].CountAnim++;
			if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				teaWk[i].PatternAnim = (teaWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureTea(i, teaWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			teaWk[i].pos += teaWk[i].move;

			D3DXVECTOR3 oldpos = teaWk[i].pos;
			teaWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量

			teaWk[i].pos += teaWk[i].move;

			//落下処理
			if (teaWk[i].pos.x < SCREEN_WIDTH)
			{
				if (teaWk[i].b_hitcnt == false)
				{
					teaWk[i].fall.y += 0.5f;
					teaWk[i].rot.z += 0.05f;
					teaWk[i].pos.y += teaWk[i].fall.y;

					// 地面設定
					if ((teaWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						teaWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// 紅茶とブロック(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((teaWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(teaWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(teaWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(teaWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					teaWk[i].pos.y = oldpos.y;
					teaWk[i].b_hitcnt = true;
				}
				else
				{
					teaWk[i].b_hitcnt = false;
				}
			}

			// 画面外まで進んだ？
			if (teaWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
			{
				teaWk[i].use = false;
			}

			SetVertexTea(i);						// 移動後の座標で頂点を設定
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			cookieWk[i].CountAnim++;
			if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				cookieWk[i].PatternAnim = (cookieWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureCookie(i, cookieWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			cookieWk[i].pos += cookieWk[i].move;

			D3DXVECTOR3 oldpos = cookieWk[i].pos;
			cookieWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量

			cookieWk[i].pos += cookieWk[i].move;

			//落下処理
			if (cookieWk[i].pos.x < SCREEN_WIDTH)
			{
				if (cookieWk[i].b_hitcnt == false)
				{
					cookieWk[i].fall.y += 0.5f;
					cookieWk[i].rot.z += 0.05f;
					cookieWk[i].pos.y += cookieWk[i].fall.y;

					// 地面設定
					if ((cookieWk[i].pos.y + ITEM_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
					{
						cookieWk[i].pos.y = SCREEN_HEIGHT - ITEM_TEXTURE_SIZE_Y;
					}
				}
			}

			// ケーキとブロック(BB)
			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (brickWk[j].use == false) continue;

				if ((cookieWk[i].pos.x + ITEM_TEXTURE_SIZE_X / 2 > brickWk[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(cookieWk[i].pos.x - ITEM_TEXTURE_SIZE_X / 2 < brickWk[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(cookieWk[i].pos.y + ITEM_TEXTURE_SIZE_Y / 2 > brickWk[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(cookieWk[i].pos.y - ITEM_TEXTURE_SIZE_Y / 2 < brickWk[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					cookieWk[i].pos.y = oldpos.y;
					cookieWk[i].b_hitcnt = true;
				}
				else
				{
					cookieWk[i].b_hitcnt = false;
				}
			}

			// 画面外まで進んだ？
			if (cookieWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ITEM_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
			{
				cookieWk[i].use = false;
			}

			SetVertexCookie(i);						// 移動後の座標で頂点を設定
		}
	}


	//ゴール処理
	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			goalWk[i].CountAnim++;
			if ((goalWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				goalWk[i].PatternAnim = (goalWk[i].PatternAnim + 1) % OBSTACLE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureGoal(i, goalWk[i].PatternAnim);
			}

			// 毎フレーム実行する処理
			goalWk[i].pos += goalWk[i].move;

			// 敵全部倒してたら門を通ってゲームクリア
			if (player[i].pos.x>goalWk[i].pos.x)
			{
				// SetStage(STAGE_GAME_CLEAR);
				SetFade(FADE_OUT, SCENE_RESULT, SOUND_LABEL_BGM_GAMECLEAR);
			}
			SetVertexGoal(i);						// 移動後の座標で頂点を設定
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < THORN_MAX; i++)
	{
		if (thornWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, thornWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, thornWk[i].vertexWk, sizeof(VERTEX_2D));
		}

	}

	for (int i = 0; i < BRICK_MAX; i++)
	{
		if (brickWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, brickWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, brickWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < CAKE_MAX; i++)
	{
		if (cakeWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, cakeWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, cakeWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < TEA_MAX; i++)
	{
		if (teaWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, teaWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, teaWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < COOKIE_MAX; i++)
	{
		if (cookieWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, cookieWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, cookieWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (goalWk[i].use == true)					// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, goalWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, goalWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成(いばら)
//=============================================================================
HRESULT MakeVertexThorn(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexThorn(i);

	// rhwの設定
	thornWk[i].vertexWk[0].rhw =
		thornWk[i].vertexWk[1].rhw =
		thornWk[i].vertexWk[2].rhw =
		thornWk[i].vertexWk[3].rhw = 1.0f;

	thornWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	thornWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	thornWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	thornWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	thornWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	thornWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// 頂点の作成(ブロック)
//=============================================================================
HRESULT MakeVertexBrick(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexBrick(i);

	// rhwの設定
	brickWk[i].vertexWk[0].rhw =
		brickWk[i].vertexWk[1].rhw =
		brickWk[i].vertexWk[2].rhw =
		brickWk[i].vertexWk[3].rhw = 1.0f;

	brickWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	brickWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	brickWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	brickWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	brickWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	brickWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// 頂点の作成(ケーキ)
//=============================================================================
HRESULT MakeVertexCake(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexCake(i);

	// rhwの設定
	cakeWk[i].vertexWk[0].rhw =
		cakeWk[i].vertexWk[1].rhw =
		cakeWk[i].vertexWk[2].rhw =
		cakeWk[i].vertexWk[3].rhw = 1.0f;

	cakeWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cakeWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	cakeWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	cakeWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	cakeWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	cakeWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// 頂点の作成(紅茶)
//=============================================================================
HRESULT MakeVertexTea(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexTea(i);

	// rhwの設定
	teaWk[i].vertexWk[0].rhw =
		teaWk[i].vertexWk[1].rhw =
		teaWk[i].vertexWk[2].rhw =
		teaWk[i].vertexWk[3].rhw = 1.0f;

	teaWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	teaWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	teaWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	teaWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	teaWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	teaWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// 頂点の作成(クッキー)
//=============================================================================
HRESULT MakeVertexCookie(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexCookie(i);

	// rhwの設定
	cookieWk[i].vertexWk[0].rhw =
		cookieWk[i].vertexWk[1].rhw =
		cookieWk[i].vertexWk[2].rhw =
		cookieWk[i].vertexWk[3].rhw = 1.0f;

	cookieWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cookieWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	cookieWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	cookieWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	cookieWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	cookieWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// 頂点の作成(ゴール)
//=============================================================================
HRESULT MakeVertexGoal(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexGoal(i);

	// rhwの設定
	goalWk[i].vertexWk[0].rhw =
		goalWk[i].vertexWk[1].rhw =
		goalWk[i].vertexWk[2].rhw =
		goalWk[i].vertexWk[3].rhw = 1.0f;

	goalWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	goalWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	goalWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	goalWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	goalWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);
	goalWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定(いばら)
//=============================================================================
void SetTextureThorn(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	thornWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	thornWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	thornWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	thornWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// テクスチャ座標の設定(ブロック)
//=============================================================================
void SetTextureBrick(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	brickWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	brickWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	brickWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	brickWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// テクスチャ座標の設定(ケーキ)
//=============================================================================
void SetTextureCake(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	cakeWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	cakeWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	cakeWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	cakeWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// テクスチャ座標の設定(紅茶)
//=============================================================================
void SetTextureTea(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	teaWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	teaWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	teaWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	teaWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// テクスチャ座標の設定(クッキー)
//=============================================================================
void SetTextureCookie(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	cookieWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	cookieWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	cookieWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	cookieWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// テクスチャ座標の設定(ゴール)
//=============================================================================
void SetTextureGoal(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / OBSTACLE_TEXTURE_PATTERN_DIVIDE_Y;

	goalWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	goalWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	goalWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	goalWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexThorn(int i)
{
	// 頂点座標の設定
	thornWk[i].vertexWk[0].vtx.x = thornWk[i].pos.x - cosf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[0].vtx.y = thornWk[i].pos.y - sinf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[0].vtx.z = 0.0f;

	thornWk[i].vertexWk[1].vtx.x = thornWk[i].pos.x + cosf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[1].vtx.y = thornWk[i].pos.y - sinf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[1].vtx.z = 0.0f;

	thornWk[i].vertexWk[2].vtx.x = thornWk[i].pos.x - cosf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[2].vtx.y = thornWk[i].pos.y + sinf(thornWk[i].BaseAngle - thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[2].vtx.z = 0.0f;

	thornWk[i].vertexWk[3].vtx.x = thornWk[i].pos.x + cosf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[3].vtx.y = thornWk[i].pos.y + sinf(thornWk[i].BaseAngle + thornWk[i].rot.z) * thornWk[i].Radius;
	thornWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBrick(int i)
{
	// 頂点座標の設定
	brickWk[i].vertexWk[0].vtx.x = brickWk[i].pos.x - cosf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[0].vtx.y = brickWk[i].pos.y - sinf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[0].vtx.z = 0.0f;

	brickWk[i].vertexWk[1].vtx.x = brickWk[i].pos.x + cosf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[1].vtx.y = brickWk[i].pos.y - sinf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[1].vtx.z = 0.0f;

	brickWk[i].vertexWk[2].vtx.x = brickWk[i].pos.x - cosf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[2].vtx.y = brickWk[i].pos.y + sinf(brickWk[i].BaseAngle - brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[2].vtx.z = 0.0f;

	brickWk[i].vertexWk[3].vtx.x = brickWk[i].pos.x + cosf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[3].vtx.y = brickWk[i].pos.y + sinf(brickWk[i].BaseAngle + brickWk[i].rot.z) * brickWk[i].Radius;
	brickWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// 頂点座標の設定(ケーキ)
//=============================================================================
void SetVertexCake(int i)
{
	if (cakeWk[i].scale_plus == true)
	{
		float len = (cakeWk[i].Radius + (cakeWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// 頂点座標の設定
		cakeWk[i].vertexWk[0].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.z = 0.0f;

		cakeWk[i].vertexWk[1].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.z = 0.0f;

		cakeWk[i].vertexWk[2].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.z = 0.0f;

		cakeWk[i].vertexWk[3].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 拡大終了？
		{														// Yes
			cakeWk[i].scale_plus = false;
		}
	}
	else if (cakeWk[i].scale_plus == false)
	{
		float len = (cakeWk[i].Radius + (cakeWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// 頂点座標の設定
		cakeWk[i].vertexWk[0].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[0].vtx.z = 0.0f;

		cakeWk[i].vertexWk[1].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.y = cakeWk[i].pos.y - sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[1].vtx.z = 0.0f;

		cakeWk[i].vertexWk[2].vtx.x = cakeWk[i].pos.x - cosf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle - cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[2].vtx.z = 0.0f;

		cakeWk[i].vertexWk[3].vtx.x = cakeWk[i].pos.x + cosf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.y = cakeWk[i].pos.y + sinf(cakeWk[i].BaseAngle + cakeWk[i].rot.z) * len;
		cakeWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cakeWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 縮小終了？
		{														// Yes
			cakeWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// 頂点座標の設定(紅茶)
//=============================================================================
void SetVertexTea(int i)
{
	if (teaWk[i].scale_plus == true)
	{
		float len = (teaWk[i].Radius + (teaWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// 頂点座標の設定
		teaWk[i].vertexWk[0].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.z = 0.0f;

		teaWk[i].vertexWk[1].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.z = 0.0f;

		teaWk[i].vertexWk[2].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.z = 0.0f;

		teaWk[i].vertexWk[3].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 拡大終了？
		{														// Yes
			teaWk[i].scale_plus = false;
		}
	}
	else if (teaWk[i].scale_plus == false)
	{
		float len = (teaWk[i].Radius + (teaWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// 頂点座標の設定
		teaWk[i].vertexWk[0].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[0].vtx.z = 0.0f;

		teaWk[i].vertexWk[1].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.y = teaWk[i].pos.y - sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[1].vtx.z = 0.0f;

		teaWk[i].vertexWk[2].vtx.x = teaWk[i].pos.x - cosf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle - teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[2].vtx.z = 0.0f;

		teaWk[i].vertexWk[3].vtx.x = teaWk[i].pos.x + cosf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.y = teaWk[i].pos.y + sinf(teaWk[i].BaseAngle + teaWk[i].rot.z) * len;
		teaWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((teaWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 縮小終了？
		{														// Yes
			teaWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// 頂点座標の設定(クッキー)
//=============================================================================
void SetVertexCookie(int i)
{
	if (cookieWk[i].scale_plus == true)
	{
		float len = (cookieWk[i].Radius + (cookieWk[i].CountAnim %OBSTACLE_TIME_ANIMATION));

		// 頂点座標の設定
		cookieWk[i].vertexWk[0].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.z = 0.0f;

		cookieWk[i].vertexWk[1].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.z = 0.0f;

		cookieWk[i].vertexWk[2].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.z = 0.0f;

		cookieWk[i].vertexWk[3].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 拡大終了？
		{														// Yes
			cookieWk[i].scale_plus = false;
		}
	}
	else if (cookieWk[i].scale_plus == false)
	{
		float len = (cookieWk[i].Radius + (cookieWk[i].CountAnim %OBSTACLE_TIME_ANIMATION) * -1);

		// 頂点座標の設定
		cookieWk[i].vertexWk[0].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[0].vtx.z = 0.0f;

		cookieWk[i].vertexWk[1].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.y = cookieWk[i].pos.y - sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[1].vtx.z = 0.0f;

		cookieWk[i].vertexWk[2].vtx.x = cookieWk[i].pos.x - cosf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle - cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[2].vtx.z = 0.0f;

		cookieWk[i].vertexWk[3].vtx.x = cookieWk[i].pos.x + cosf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.y = cookieWk[i].pos.y + sinf(cookieWk[i].BaseAngle + cookieWk[i].rot.z) * len;
		cookieWk[i].vertexWk[3].vtx.z = 0.0f;

		if ((cookieWk[i].CountAnim % OBSTACLE_TIME_ANIMATION) == 0)	// 縮小終了？
		{														// Yes
			cookieWk[i].scale_plus = true;
		}
	}
}

//=============================================================================
// 頂点座標の設定(ゴール)
//=============================================================================
void SetVertexGoal(int i)
{
	//// 頂点座標の設定
	//if (goalWk[i].use == true)
	//{
		// 頂点座標の設定
	goalWk[i].vertexWk[0].vtx.x = goalWk[i].pos.x - cosf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[0].vtx.y = goalWk[i].pos.y - sinf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[0].vtx.z = 0.0f;

	goalWk[i].vertexWk[1].vtx.x = goalWk[i].pos.x + cosf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[1].vtx.y = goalWk[i].pos.y - sinf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[1].vtx.z = 0.0f;

	goalWk[i].vertexWk[2].vtx.x = goalWk[i].pos.x - cosf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[2].vtx.y = goalWk[i].pos.y + sinf(goalWk[i].BaseAngle - goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[2].vtx.z = 0.0f;

	goalWk[i].vertexWk[3].vtx.x = goalWk[i].pos.x + cosf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[3].vtx.y = goalWk[i].pos.y + sinf(goalWk[i].BaseAngle + goalWk[i].rot.z) * goalWk[i].Radius;
	goalWk[i].vertexWk[3].vtx.z = 0.0f;
	/*}*/
}
//=============================================================================
// いばら取得関数
//=============================================================================
THORN *GetThorn(void)
{
	return(&thornWk[0]);
}

//=============================================================================
// ブロック取得関数
//=============================================================================
BRICK *GetBrick(void)
{
	return(&brickWk[0]);
}

//=============================================================================
// ケーキ取得関数
//=============================================================================
CAKE *GetCake(void)
{
	return(&cakeWk[0]);
}

//=============================================================================
// 紅茶取得関数
//=============================================================================
TEA *GetTea(void)
{
	return(&teaWk[0]);
}

//=============================================================================
// クッキー取得関数
//=============================================================================
COOKIE *GetCookie(void)
{
	return(&cookieWk[0]);
}

//=============================================================================
// ゴール取得関数
//=============================================================================
GOAL *GetGoal(void)
{
	return(&goalWk[0]);
}