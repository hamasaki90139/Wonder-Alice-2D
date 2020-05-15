//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "obstacle.h"
#include "sound.h"
#include "bg.h"
#include "hp.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(int no);
void SetTexturePlayer(int no, int cntPattern);
void SetVertexPlayer(int no);
void SetDiffusePlayer(int i);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// テクスチャへのポリゴン

static PLAYER					playerWk[PLAYER_MAX];			// プレイヤー構造体

//static LPDIRECTSOUNDBUFFER8		g_pSE;							// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャの読み込み
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			PLAYER_TEXTURE,					// ファイルの名前
			&g_pD3DTexturePlayer);			// 読み込むメモリのポインタ
	}

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		playerWk[i].use = true;											// 使用
		playerWk[i].dmgflag = false;									// ダメージ判定無で初期化
		playerWk[i].dmg = true;											// ダメージを与えたで初期化
		playerWk[i].direction = true;									// 右向きで初期化
		playerWk[i].pos = D3DXVECTOR3(i*100.0f + 200.0f, 340.0f, 0.0f);	// 座標データを初期化
		playerWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		playerWk[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動量
		playerWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		playerWk[i].CountAnim = 0;										// アニメカウントを初期化
		playerWk[i].Texture = g_pD3DTexturePlayer;

		playerWk[i].jump = false;										// ジャンプ中じゃ無い
		playerWk[i].jump_y = PLAYER_JUMP_Y;								// ジャンプ時の高さ
		playerWk[i].jump_cnt = 0;										//ジャンプカウントの初期化
		playerWk[i].jump_cnt_max = PLAYER_JUMP_CNT_MAX;					//ジャンプカウント最大値の設定
		playerWk[i].ofs = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// オフセット座標を初期化
		playerWk[i].jumppoint = 0;

		D3DXVECTOR2 temp = D3DXVECTOR2(PLAYER_TEXTURE_SIZE_X, PLAYER_TEXTURE_SIZE_Y);
		playerWk[i].Radius = D3DXVec2Length(&temp);						// プレイヤーの半径を初期化

		MakeVertexPlayer(i);											// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	BRICK  *brick = GetBrick();			// ブロックのポインターを初期化
	MP *mp = GetMp();					// スコアのポインターを初期化
	BULLET *bullet = GetBullet();			// バレットのポインターを初期化


	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (playerWk[i].use == true)			// 使用している状態なら更新する
		{
			D3DXVECTOR3 oldpos = playerWk[i].pos;
			D3DXVECTOR3 oldofs = playerWk[i].ofs;

			// アニメーション
			playerWk[i].CountAnim++;
			if ((playerWk[i].CountAnim % PLAYER_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				playerWk[i].PatternAnim = (playerWk[i].PatternAnim + 1) % 2;
			}

			//移動処理
			if (GetKeyboardPress(DIK_D) || (IsButtonPressed(0, BUTTON_RIGHT)))	//右移動
			{
				playerWk[i].move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
				playerWk[i].direction = true;
			}
			else if (GetKeyboardPress(DIK_A) || (IsButtonPressed(0, BUTTON_LEFT)))	//左移動
			{
				playerWk[i].move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
				playerWk[i].direction = false;
			}
			else
			{
				playerWk[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			//右向きか左向きかでアニメパターンを切り替える
			if (playerWk[i].direction == false)
			{
				SetTexturePlayer(i, playerWk[i].PatternAnim + 2);
			}
			else
			{
				SetTexturePlayer(i, playerWk[i].PatternAnim);
			}

			// ジャンプ処理
			if (playerWk[i].jump == true)
			{
				float rag = D3DX_PI / playerWk[i].jump_cnt_max;
				float angle = rag * playerWk[i].jump_cnt;
				playerWk[i].move.y = sinf(angle) * playerWk[i].jump_y;
				playerWk[i].jump_cnt++;

				//ジャンプアニメパターンの切り替え
				if (playerWk[i].direction == false)
				{
					SetTexturePlayer(i, playerWk[i].PatternAnim + 6);
				}
				else
				{
					SetTexturePlayer(i, playerWk[i].PatternAnim + 4);
				}

				if (playerWk[i].jump_cnt >= playerWk[i].jump_cnt_max)	// ジャンプ終了？
				{														// Yes
					playerWk[i].jump = false;
				}
			}

			// 重力処理
			playerWk[i].move.y += 6.0f;

			playerWk[i].pos += playerWk[i].move;

			// 画面外まで進んだ？
			if (playerWk[i].pos.x >= SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X / 2)// 自分の大きさを考慮して画面外か判定している
			{
				playerWk[i].pos.x = SCREEN_WIDTH - PLAYER_TEXTURE_SIZE_X / 2;
			}
			else if (playerWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - PLAYER_TEXTURE_SIZE_X / 4)// 自分の大きさを考慮して画面外か判定している
			{
				playerWk[i].pos.x = (SCREEN_WIDTH - SCREEN_WIDTH) - PLAYER_TEXTURE_SIZE_X / 4;
			}
			else if (playerWk[i].pos.y <= (SCREEN_HEIGHT - SCREEN_HEIGHT) - PLAYER_TEXTURE_SIZE_Y / 4)// 自分の大きさを考慮して画面外か判定している
			{
				playerWk[i].pos.y = (SCREEN_HEIGHT - SCREEN_HEIGHT) - PLAYER_TEXTURE_SIZE_Y / 4;
			}

			// ジャンプ？
			if (playerWk[i].jumppoint < PLAYER_JUMPMAX)
			{
				if (GetKeyboardTrigger(DIK_W) || (IsButtonTriggered(0, BUTTON_UP)))
				{
					if (playerWk[i].jump == false)	// 今はジャンプしていない？
					{								// Yes
						playerWk[i].jump = true;
						playerWk[i].jump_cnt = 0;
						playerWk[i].jumppoint++;
					}
				}
			}

			// プレイヤーとブロック(BB)
			D3DXVECTOR3 pos = playerWk[i].pos + playerWk[i].ofs;

			for (int j = 0; j < BRICK_MAX; j++)
			{
				if (playerWk[i].use == false) continue;
				if (playerWk[i].jump == true) continue;
				if (brick[j].use == false)	  continue;

				//プレイヤーが地上でブロックに当たったとき
				if ((playerWk[i].move.x != 0.0f) &&
					((playerWk[i].pos.y + PLAYER_TEXTURE_SIZE_Y) > SCREEN_HEIGHT) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move *= -1;									//移動量の反転
					playerWk[i].pos += playerWk[i].move;					//移動量を座標へプラス
					playerWk[i].jump = false;								//ジャンプしていない
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;								//ブロックに押される
				}
				// プレイヤーが空中でブロックに当たったとき
				else if ((playerWk[i].move.x != 0.0f) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y-20 > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move.y *= -1;
					playerWk[i].pos += playerWk[i].move;
					playerWk[i].jump = false;
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;
				}
				//キー操作がない＆ブロックに当たったとき
				else if ((playerWk[i].move.x == 0.0f) &&
					(pos.x + PLAYER_TEXTURE_SIZE_X / 4 > brick[j].pos.x - BRICK_TEXTURE_SIZE_X) &&
					(pos.x - PLAYER_TEXTURE_SIZE_X / 4 < brick[j].pos.x + BRICK_TEXTURE_SIZE_X) &&
					(pos.y + PLAYER_TEXTURE_SIZE_Y > brick[j].pos.y - BRICK_TEXTURE_SIZE_Y) &&
					(pos.y - PLAYER_TEXTURE_SIZE_Y < brick[j].pos.y + BRICK_TEXTURE_SIZE_Y))
				{
					playerWk[i].move.y *= -1;
					playerWk[i].pos += playerWk[i].move;
					playerWk[i].jump = false;
					playerWk[i].jumppoint = 0;
					playerWk[i].pos.x += -2.0f;
				}
			}

			/*弾発射？*/
			int	cnt = 0;						//エネミーの生存カウント
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (bullet[i].use == true)
				{
					cnt++;
				}
			}

			if (cnt < BULLET_CNT)
			{
				if (GetKeyboardTrigger(DIK_UP) || (IsButtonTriggered(0, BUTTON_B)))	//上向き処理
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 0);		// 右上
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 5);		// 左上
					}
				}

				if (GetKeyboardTrigger(DIK_DOWN) || (IsButtonTriggered(0, BUTTON_C)))	//下向き処理
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 3);		// 右下
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 8);		// 左下
					}
				}

				if (GetKeyboardTrigger(DIK_RIGHT) || (IsButtonTriggered(0, BUTTON_A)))	//中央処理
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 2);		// 右中
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 7);		// 左中
					}
				}
			}

			if (GetKeyboardTrigger(DIK_LEFT) || (IsButtonTriggered(0, BUTTON_X)))	//チャージ処理
			{
				if (mp->mp >= MP_UNIT)
				{
					D3DXVECTOR3 pos = playerWk[i].pos;
					pos.y -= PLAYER_TEXTURE_SIZE_Y / PLAYER_TEXTURE_SIZE_Y;

					if (playerWk[i].direction == true)
					{
						pos.x += PLAYER_TEXTURE_SIZE_X - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 0);		// 右上1
						SetBullet(pos, 1);		// 右上2
						SetBullet(pos, 3);		// 右下1
						SetBullet(pos, 4);		// 右下2

						AddMp(-MP_UNIT);			//MPゲージ消費
					}
					if (playerWk[i].direction == false)
					{
						pos.x += (PLAYER_TEXTURE_SIZE_X - PLAYER_TEXTURE_SIZE_X) - (PLAYER_TEXTURE_SIZE_X / 2);
						SetBullet(pos, 5);		// 左上1
						SetBullet(pos, 6);		// 左上2
						SetBullet(pos, 8);		// 左下1
						SetBullet(pos, 9);		// 左下2

						AddMp(-MP_UNIT);			//MPゲージ消費
					}
				}
			}
		}

		//リトライ
		if (GetKeyboardTrigger(DIK_SPACE) || ((IsButtonTriggered(0, BUTTON_R)&& (IsButtonTriggered(0, BUTTON_L)))))
		{
			SetSceneold();
			SetFade(FADE_OUT, SCENE_RETRY, SOUND_LABEL_BGM_GAME);
		}

		// 地面設定
		if ((playerWk[i].pos.y + PLAYER_TEXTURE_SIZE_Y) > SCREEN_HEIGHT)
		{
			playerWk[i].pos.y = SCREEN_HEIGHT - PLAYER_TEXTURE_SIZE_Y;
			playerWk[i].jumppoint = 0;
		}

		SetVertexPlayer(i);	// 移動後の座標で頂点を設定
		SetDiffusePlayer(i);	// 被ダメージ色の設定
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (playerWk[i].use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, playerWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, playerWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	playerWk[i].vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	playerWk[i].vertexWk[1].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f, 0.0f);
	playerWk[i].vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);
	playerWk[i].vertexWk[3].vtx = D3DXVECTOR3(100.0f + PLAYER_TEXTURE_SIZE_X, 100.0f + PLAYER_TEXTURE_SIZE_Y, 0.0f);

	// rhwの設定
	playerWk[i].vertexWk[0].rhw =
	playerWk[i].vertexWk[1].rhw =
	playerWk[i].vertexWk[2].rhw =
	playerWk[i].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	playerWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	playerWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	playerWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y);
	playerWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X, 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_Y;

	playerWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	playerWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	playerWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	playerWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(int i)
{
	// 頂点座標の設定
	D3DXVECTOR3 pos = playerWk[i].pos + playerWk[i].ofs;

	playerWk[i].vertexWk[0].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[0].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[0].vtx.z = 0.0f;

	playerWk[i].vertexWk[1].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[1].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[1].vtx.z = 0.0f;

	playerWk[i].vertexWk[2].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[2].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[2].vtx.z = 0.0f;

	playerWk[i].vertexWk[3].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	playerWk[i].vertexWk[3].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	playerWk[i].vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// HP減少色の設定
//=============================================================================
void SetDiffusePlayer(int i)
{
	if (playerWk[i].dmgflag == true)	//プレイヤーがダメージをうけたら
	{
		// 反射光の設定
		playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);

		playerWk[i].dmg_cnt++;		//ダメージ色表示時間のカウント
		if (playerWk[i].dmg_cnt == PLAYER_DMG_CNT_MAX)
		{
			playerWk[i].dmgflag = false;	//ダメージフラグを無に戻す
			playerWk[i].dmg_cnt = 0;	//カウントを初期化
		}
	}
	else if (playerWk[i].dmgflag == false)	//プレイヤーがダメージをうけていなければ
	{
		// 反射光の設定
		playerWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		playerWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}
//=============================================================================
// プレイヤー取得関数
//=============================================================================
PLAYER *GetPlayer(void)
{
	return(&playerWk[0]);
}