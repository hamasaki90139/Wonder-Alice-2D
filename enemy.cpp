//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "obstacle.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy(int no, int cntPattern);
void SetVertexEnemy(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ENEMY					enemyWk[ENEMY_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(int type)
{
	srand((unsigned)time(NULL));	//ランダム初期値の初期化
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE01,										// ファイルの名前
			&enemyWk[0].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE02,										// ファイルの名前
			&enemyWk[1].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE03,										// ファイルの名前
			&enemyWk[2].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE04,										// ファイルの名前
			&enemyWk[3].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE05,										// ファイルの名前
			&enemyWk[4].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE06,										// ファイルの名前
			&enemyWk[5].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE07,										// ファイルの名前
			&enemyWk[6].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE08,										// ファイルの名前
			&enemyWk[7].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE09,										// ファイルの名前
			&enemyWk[8].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE10,										// ファイルの名前
			&enemyWk[9].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE11,										// ファイルの名前
			&enemyWk[10].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE12,										// ファイルの名前
			&enemyWk[11].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE13,										// ファイルの名前
			&enemyWk[12].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE14,										// ファイルの名前
			&enemyWk[13].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE15,										// ファイルの名前
			&enemyWk[14].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE16,										// ファイルの名前
			&enemyWk[15].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE17,										// ファイルの名前
			&enemyWk[16].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE18,										// ファイルの名前
			&enemyWk[17].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE19,										// ファイルの名前
			&enemyWk[18].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE20,										// ファイルの名前
			&enemyWk[19].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE21,										// ファイルの名前
			&enemyWk[20].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE22,										// ファイルの名前
			&enemyWk[21].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE23,										// ファイルの名前
			&enemyWk[22].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE24,										// ファイルの名前
			&enemyWk[23].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE25,										// ファイルの名前
			&enemyWk[24].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE26,										// ファイルの名前
			&enemyWk[25].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE27,										// ファイルの名前
			&enemyWk[26].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE28,										// ファイルの名前
			&enemyWk[27].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE29,										// ファイルの名前
			&enemyWk[28].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE30,										// ファイルの名前
			&enemyWk[29].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE31,										// ファイルの名前
			&enemyWk[30].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE32,										// ファイルの名前
			&enemyWk[31].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE33,										// ファイルの名前
			&enemyWk[32].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE34,										// ファイルの名前
			&enemyWk[33].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE35,										// ファイルの名前
			&enemyWk[34].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			ENEMY_TEXTURE36,										// ファイルの名前
			&enemyWk[35].g_pD3DTextureEnemy);								// 読み込むメモリのポインタ

	}


	// エネミーの初期化処理
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemyWk[i].use = true;										// 使用
		enemyWk[i].pos = D3DXVECTOR3(i* (rand() % (200 + 1) + 100) + 1500.0f, rand() % (300 + 1) + 100.0f, 0.0f);	// 座標データを初期化
		enemyWk[i].move = D3DXVECTOR3(-(rand() % (2 + 1) + 3.0f), 0.0f, 0.0f);				// 移動量
		enemyWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量
		enemyWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化

		enemyWk[i].rotflag = true;		//左回転で初期化
		enemyWk[i].rot_cnt = 0;
		enemyWk[i].rot_cnt_max = ENEMY_ROT_CNT_MAX;
		enemyWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		enemyWk[i].CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y);
		enemyWk[i].Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		enemyWk[i].BaseAngle = atan2f(ENEMY_TEXTURE_SIZE_Y, ENEMY_TEXTURE_SIZE_X);	// エネミーの角度を初期化
		enemyWk[i].Texture = enemyWk[i].g_pD3DTextureEnemy;

		MakeVertexEnemy(i);											// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].g_pD3DTextureEnemy != NULL)
		{	// テクスチャの開放
			enemyWk[i].g_pD3DTextureEnemy->Release();
			enemyWk[i].g_pD3DTextureEnemy = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化
	BRICK  *brick = GetBrick();			// ブロックのポインターを初期化

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemyWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			enemyWk[i].CountAnim++;
			if ((enemyWk[i].CountAnim % ENEMY_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				enemyWk[i].PatternAnim = (enemyWk[i].PatternAnim + 1) % ENEMY_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureEnemy(i, enemyWk[i].PatternAnim);
			}

			// 左回転処理
			if (enemyWk[i].rotflag == true)
			{
				enemyWk[i].rot.z += 0.05f;
				enemyWk[i].rot_cnt++;
				if (enemyWk[i].rot_cnt >= enemyWk[i].rot_cnt_max)	// ジャンプ終了？
				{														// Yes
					enemyWk[i].rotflag = false;	//右回転へ
					enemyWk[i].rot_cnt = 0;
				}
			}
			//右回転処理
			else if (enemyWk[i].rotflag == false)
			{
				enemyWk[i].rot.z += -0.05f;
				enemyWk[i].rot_cnt++;
				if (enemyWk[i].rot_cnt >= enemyWk[i].rot_cnt_max)	// ジャンプ終了？
				{														// Yes
					enemyWk[i].rotflag = true;	//左回転へ
					enemyWk[i].rot_cnt = 0;
				}
			}

				D3DXVECTOR3 oldpos = enemyWk[i].pos;
				bool b_hitcnt = false;		//ブロックと当たったか
				enemyWk[i].fall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 落下量

				enemyWk[i].pos += enemyWk[i].move;

				//落下処理
				if (enemyWk[i].pos.x < SCREEN_WIDTH)
				{
					if (b_hitcnt == false)
					{
						enemyWk[i].fall.y += 1.5f;
						enemyWk[i].pos.y += enemyWk[i].fall.y;

						// 地面設定
						if ((enemyWk[i].pos.y + ENEMY_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
						{
							enemyWk[i].pos.y = SCREEN_HEIGHT - ENEMY_TEXTURE_SIZE_Y;
						}
					}
				}

				// エネミーとブロック(BB)
				for (int j = 0; j < BRICK_MAX; j++)
				{
					if (brick[j].use == false) continue;

					if ((enemyWk[i].pos.x + ENEMY_TEXTURE_SIZE_X / 2 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
						(enemyWk[i].pos.x - ENEMY_TEXTURE_SIZE_X / 2 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
						(enemyWk[i].pos.y + ENEMY_TEXTURE_SIZE_Y / 2 > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
						(enemyWk[i].pos.y - ENEMY_TEXTURE_SIZE_Y / 2 < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
					{
						enemyWk[i].pos.y = oldpos.y;
						b_hitcnt = true;
					}
					else
					{
						b_hitcnt = false;
					}
				}

				// 画面外まで進んだ？
				if (enemyWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - ENEMY_TEXTURE_SIZE_X)// 自分の大きさを考慮して画面外か判定している
				{
					enemyWk[i].use = false;
				}

				SetVertexEnemy(i);						// 移動後の座標で頂点を設定
			}
		}

	}

	//=============================================================================
	// 描画処理
	//=============================================================================
	void DrawEnemy(void)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemyWk[i].use == true)			// 使用している状態なら描画する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, enemyWk[i].Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, enemyWk[i].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}

	//=============================================================================
	// 頂点の作成
	//=============================================================================
	HRESULT MakeVertexEnemy(int i)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点座標の設定
		SetVertexEnemy(i);

		// rhwの設定
		enemyWk[i].vertexWk[0].rhw =
			enemyWk[i].vertexWk[1].rhw =
			enemyWk[i].vertexWk[2].rhw =
			enemyWk[i].vertexWk[3].rhw = 1.0f;

		enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);
		enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(150, 0, 100, 255);

		// 反射光の設定
		/*if (i & 1)
		{
			enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			enemyWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
			enemyWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(64, 255, 64, 255);
		}*/

		// テクスチャ座標の設定
		enemyWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		enemyWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		enemyWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y);
		enemyWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X, 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y);

		//enemyWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//enemyWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//enemyWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//enemyWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		return S_OK;
	}

	//=============================================================================
	// テクスチャ座標の設定
	//=============================================================================
	void SetTextureEnemy(int i, int cntPattern)
	{
		// テクスチャ座標の設定
		int x = cntPattern % ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		int y = cntPattern / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / ENEMY_TEXTURE_PATTERN_DIVIDE_Y;

		enemyWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemyWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemyWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}

	//=============================================================================
	// 頂点座標の設定
	//=============================================================================
	void SetVertexEnemy(int i)
	{
		// 頂点座標の設定
		enemyWk[i].vertexWk[0].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[0].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[0].vtx.z = 0.0f;

		enemyWk[i].vertexWk[1].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[1].vtx.y = enemyWk[i].pos.y - sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[1].vtx.z = 0.0f;

		enemyWk[i].vertexWk[2].vtx.x = enemyWk[i].pos.x - cosf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[2].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle - enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[2].vtx.z = 0.0f;

		enemyWk[i].vertexWk[3].vtx.x = enemyWk[i].pos.x + cosf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[3].vtx.y = enemyWk[i].pos.y + sinf(enemyWk[i].BaseAngle + enemyWk[i].rot.z) * enemyWk[i].Radius;
		enemyWk[i].vertexWk[3].vtx.z = 0.0f;
	}

	//=============================================================================
	// エネミー取得関数
	//=============================================================================
	ENEMY *GetEnemy(void)
	{
		return(&enemyWk[0]);
	}


