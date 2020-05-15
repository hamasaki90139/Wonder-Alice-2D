//=============================================================================
//
// HP処理 [hp.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "hp.h"
#include "player.h"
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexHp(void);
void SetTextureHp(int hpPattern);
void SetTextureMp(int mpPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureHp = NULL;			// テクスチャへのポリゴン
static LPDIRECT3DTEXTURE9		g_pD3DTextureMp = NULL;			// テクスチャへのポリゴン

static VERTEX_2D				g_vertexWkHp[NUM_VERTEX];	// 頂点情報格納ワーク
static VERTEX_2D				g_vertexWkMp[NUM_VERTEX];	// 頂点情報格納ワーク

static D3DXVECTOR3				g_posHp;						// ポリゴンの移動量
static D3DXVECTOR3				g_posMp;						// ポリゴンの移動量

static int						g_Hp;						// HP
static MP						mpWk;						// MP構造体

static int						g_PatternHp;				// アニメーションパターンナンバー
static int						g_PatternMp;				// アニメーションパターンナンバー

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			HP_TEXTURE,						// ファイルの名前
			&g_pD3DTextureHp);					// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			MP_TEXTURE,						// ファイルの名前
			&g_pD3DTextureMp);					// 読み込むメモリのポインタ

	}

	g_posHp = D3DXVECTOR3((float)HP_POS_X, (float)HP_POS_Y, 0.0f);
	g_Hp = HP_5;						//HPを満タンにする
	g_PatternHp = g_Hp;					//アニメーションパターンとHPを同期させる

	g_posMp = D3DXVECTOR3((float)MP_POS_X, (float)MP_POS_Y, 0.0f);
	mpWk.mp = MP_0;						////MPを初期化する
	g_PatternMp = mpWk.mp;				//アニメーションパターンとHPを同期させる

	// 頂点情報の作成
	MakeVertexHp();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHp(void)
{
	if (g_pD3DTextureHp != NULL)
	{	// テクスチャの開放
		g_pD3DTextureHp->Release();
		g_pD3DTextureHp = NULL;
	}

	if (g_pD3DTextureMp != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMp->Release();
		g_pD3DTextureMp = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHp(void)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化

	// 毎フレーム実行される処理を記述する

	SetTextureHp(g_Hp);

	//HP画像のパターン
	switch (g_Hp)
	{
	case 0:
		g_PatternHp = HP_0;
		player->use = false;
		break;
	case 1:
		g_PatternHp = HP_1;
		break;
	case 2:
		g_PatternHp = HP_2;
		break;
	case 3:
		g_PatternHp = HP_3;
		break;
	case 4:
		g_PatternHp = HP_4;
		break;
	case 5:
		g_PatternHp = HP_5;
		break;

	}

	//MP画像のパターン
	switch (mpWk.mp)
	{
	case 0:
		g_PatternMp = MP_0;
		break;
	case 1:
		g_PatternMp = MP_1;
		break;
	case 2:
		g_PatternMp = MP_2;
		break;
	case 3:
		g_PatternMp = MP_3;
		break;
	case 4:
		g_PatternMp = MP_4;
		break;
	case 5:
		g_PatternMp = MP_5;
		break;
	case 6:
		g_PatternMp = MP_6;
		break;
	}

	SetTextureHp(g_Hp);
	SetTextureMp(mpWk.mp);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHp(void)
{
	//HP
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureHp);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWkHp, sizeof(VERTEX_2D));

	//MP
	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureMp);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWkMp, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexHp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	g_vertexWkHp[0].vtx = D3DXVECTOR3(g_posHp.x, g_posHp.y, 0.0f);
	g_vertexWkHp[1].vtx = D3DXVECTOR3(g_posHp.x + HP_SIZE_W, g_posHp.y, 0.0f);
	g_vertexWkHp[2].vtx = D3DXVECTOR3(g_posHp.x, g_posHp.y + HP_SIZE_H, 0.0f);
	g_vertexWkHp[3].vtx = D3DXVECTOR3(g_posHp.x + HP_SIZE_W, g_posHp.y + HP_SIZE_H, 0.0f);

	// rhwの設定
	g_vertexWkHp[0].rhw =
	g_vertexWkHp[1].rhw =
	g_vertexWkHp[2].rhw =
	g_vertexWkHp[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkHp[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkHp[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkHp[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkHp[1].tex = D3DXVECTOR2(1.0f / HP_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	g_vertexWkHp[2].tex = D3DXVECTOR2(0.0f, 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y);
	g_vertexWkHp[3].tex = D3DXVECTOR2(1.0f / HP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y);

	// 頂点座標の設定
	g_vertexWkMp[0].vtx = D3DXVECTOR3(g_posMp.x, g_posMp.y, 0.0f);
	g_vertexWkMp[1].vtx = D3DXVECTOR3(g_posMp.x + MP_SIZE_W, g_posMp.y, 0.0f);
	g_vertexWkMp[2].vtx = D3DXVECTOR3(g_posMp.x, g_posMp.y + MP_SIZE_H, 0.0f);
	g_vertexWkMp[3].vtx = D3DXVECTOR3(g_posMp.x + MP_SIZE_W, g_posMp.y + MP_SIZE_H, 0.0f);

	// rhwの設定
	g_vertexWkMp[0].rhw =
	g_vertexWkMp[1].rhw =
	g_vertexWkMp[2].rhw =
	g_vertexWkMp[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkMp[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkMp[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkMp[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkMp[1].tex = D3DXVECTOR2(1.0f / MP_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	g_vertexWkMp[2].tex = D3DXVECTOR2(0.0f, 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y);
	g_vertexWkMp[3].tex = D3DXVECTOR2(1.0f / MP_TEXTURE_PATTERN_DIVIDE_X, 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y);
	
	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureHp(int hpPattern)
{
	// テクスチャ座標の設定
	int x = hpPattern % HP_TEXTURE_PATTERN_DIVIDE_X;
	int y = hpPattern / HP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / HP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / HP_TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWkHp[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWkHp[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWkHp[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWkHp[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureMp(int mpPattern)
{
	// テクスチャ座標の設定
	int x = mpPattern % MP_TEXTURE_PATTERN_DIVIDE_X;
	int y = mpPattern / MP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / MP_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / MP_TEXTURE_PATTERN_DIVIDE_Y;

	g_vertexWkMp[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWkMp[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWkMp[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWkMp[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void AddHp(int add)
{
	g_Hp += add;

	if (g_Hp >= HP_MAX)
	{
		g_Hp = HP_MAX;
	}
}

//=============================================================================
// MPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void AddMp(int add)
{
	mpWk.mp += add;

	if (mpWk.mp >= MP_MAX)
	{
		mpWk.mp = MP_MAX;
	}
	if (mpWk.mp < 0)
	{
		mpWk.mp = 0;
	}
}

//=============================================================================
// HP取得関数
//=============================================================================
MP *GetMp(void)
{
	return(&mpWk);
}
