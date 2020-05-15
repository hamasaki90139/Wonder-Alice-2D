//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "enemy.h"
#include "hp.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetTextureBullet(int no, int cntPattern);
void SetVertexBullet(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static BULLET					bulletWk[BULLET_MAX];			// バレット構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャの読み込み
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			BULLET_TEXTURE01,						// ファイルの名前
			&bulletWk[0].g_pD3DTextureBullet);		// 読み込むメモリのポインタ

		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			BULLET_TEXTURE02,						// ファイルの名前
			&bulletWk[1].g_pD3DTextureBullet);		// 読み込むメモリのポインタ

		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			BULLET_TEXTURE03,						// ファイルの名前
			&bulletWk[2].g_pD3DTextureBullet);		// 読み込むメモリのポインタ

		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			BULLET_TEXTURE04,						// ファイルの名前
			&bulletWk[3].g_pD3DTextureBullet);		// 読み込むメモリのポインタ
	}

	// バレットの初期化処理
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bulletWk[i].use = false;										// 未使用（発射されていない弾）
		bulletWk[i].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				// 座標データを初期化
		bulletWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		bulletWk[i].move = D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f);		// 移動量を初期化
		bulletWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		bulletWk[i].CountAnim = 0;										// アニメカウントを初期化
		bulletWk[i].Texture = bulletWk[i%4].g_pD3DTextureBullet;		//テクスチャを設定

		D3DXVECTOR2 temp = D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y);
		bulletWk[i].Radius = D3DXVec2Length(&temp);						// バレットの半径を初期化
		bulletWk[i].BaseAngle = atan2f(BULLET_TEXTURE_SIZE_Y, BULLET_TEXTURE_SIZE_X);	// バレットの角度を初期化

		MakeVertexBullet(i);											// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].g_pD3DTextureBullet != NULL)
		{	// テクスチャの開放
			bulletWk[i].g_pD3DTextureBullet->Release();
			bulletWk[i].g_pD3DTextureBullet = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == true)		// 使用している状態なら更新する
		{
			// バレットの移動処理
			bulletWk[i].pos += bulletWk[i].move;

			// バレットの回転処理
			bulletWk[i].rot.z += 0.05f;

			// 画面外まで進んだ？自分の大きさを考慮して画面外か判定している
			if ((bulletWk[i].pos.x >= SCREEN_WIDTH - BULLET_TEXTURE_SIZE_X) ||
				(bulletWk[i].pos.x <= (SCREEN_WIDTH - SCREEN_WIDTH) - BULLET_TEXTURE_SIZE_X) ||
				(bulletWk[i].pos.y >= SCREEN_HEIGHT - BULLET_TEXTURE_SIZE_Y) ||
				(bulletWk[i].pos.y <= (SCREEN_HEIGHT - SCREEN_HEIGHT) - BULLET_TEXTURE_SIZE_Y))
			{
				bulletWk[i].use = false;
			}

			SetVertexBullet(i);				// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == true)			// 使用している状態なら更新する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, bulletWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bulletWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBullet(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexBullet(i);

	// rhwの設定
	bulletWk[i].vertexWk[0].rhw =
	bulletWk[i].vertexWk[1].rhw =
	bulletWk[i].vertexWk[2].rhw =
	bulletWk[i].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	bulletWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bulletWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	bulletWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bulletWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	bulletWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y);
	bulletWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X, 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % BULLET_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / BULLET_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / BULLET_TEXTURE_PATTERN_DIVIDE_Y;

	bulletWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bulletWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bulletWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bulletWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet(int i)
{
	// 頂点座標の設定
	bulletWk[i].vertexWk[0].vtx.x = bulletWk[i].pos.x - cosf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[0].vtx.y = bulletWk[i].pos.y - sinf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[0].vtx.z = 0.0f;

	bulletWk[i].vertexWk[1].vtx.x = bulletWk[i].pos.x + cosf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[1].vtx.y = bulletWk[i].pos.y - sinf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[1].vtx.z = 0.0f;

	bulletWk[i].vertexWk[2].vtx.x = bulletWk[i].pos.x - cosf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[2].vtx.y = bulletWk[i].pos.y + sinf(bulletWk[i].BaseAngle - bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[2].vtx.z = 0.0f;

	bulletWk[i].vertexWk[3].vtx.x = bulletWk[i].pos.x + cosf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[3].vtx.y = bulletWk[i].pos.y + sinf(bulletWk[i].BaseAngle + bulletWk[i].rot.z) * bulletWk[i].Radius;
	bulletWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, int type)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletWk[i].use == false)		// 未使用状態のバレットを見つける
		{
			bulletWk[i].use = true;			// 使用状態へ変更する
			bulletWk[i].pos = pos;			// 座標をセット
			bulletWk[i].type = type;		// 弾の種類をセット

			// 弾の種類に応じて飛ばす方向を変えてみる処理
			switch (type)
			{
			case 0:	//右上1
			default:
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, -BULLET_SPEED, 0.0f);		// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 右斜め４５度向き
				break;

			case 1:	//右上2
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, -BULLET_SPEED / 2, 0.0f);	// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 右斜め４５度向き
				break;

			case 2:	//右中
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f);				// 移動量を初期化
				bulletWk[i].rot.z = 0.0f;												// 正面向き
				break;

			case 3:	//右下1
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, BULLET_SPEED / 2, 0.0f);	// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 右斜め４５度向き
				break;

			case 4:	//右下2
				bulletWk[i].move = D3DXVECTOR3(BULLET_SPEED, BULLET_SPEED, 0.0f);		// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 右斜め４５度向き
				break;

			case 5:	//左上1
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, -BULLET_SPEED, 0.0f);		// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 左斜め４５度向き
				break;

			case 6:	//左上2
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, -BULLET_SPEED / 2, 0.0f);	// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 左斜め４５度向き
				break;

			case 7:	//左中
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, 0.0f, 0.0f);				// 移動量を初期化
				bulletWk[i].rot.z = 0.0f;												// 正面向き
				break;

			case 8:	//左下1
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, BULLET_SPEED / 2, 0.0f);	// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 左斜め４５度向き
				break;

			case 9:	//左下2
				bulletWk[i].move = D3DXVECTOR3(-BULLET_SPEED, BULLET_SPEED, 0.0f);		// 移動量を初期化
				bulletWk[i].rot.z = -D3DX_PI / 4;										// 左斜め４５度向き
				break;

			}

			// SE再生
			PlaySound(SOUND_LABEL_SE_BULLET);
			return;							// 1発セットしたので終了する
		}
	}
}

//=============================================================================
// バレット取得関数
//=============================================================================
BULLET *GetBullet(void)
{
	return(&bulletWk[0]);
}

