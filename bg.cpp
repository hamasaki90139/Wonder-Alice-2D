//=============================================================================
//
// BG処理 [bg.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetVertexBG(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture[NUM_BG] = { NULL };	// テクスチャへのポインタ
static VERTEX_2D				g_vertexWk[NUM_BG][NUM_VERTEX];	// 頂点情報格納ワーク

static D3DXVECTOR3				g_pos;					// 背景の位置
float							interval[NUM_BG];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			BG_TEXTURE,				// ファイルの名前
			&g_pD3DTexture[0]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			BG_TEXTURE,				// ファイルの名前
			&g_pD3DTexture[1]);		// 読み込むメモリー
	}

	for (int i = 0; i < NUM_BG; i++)
	{
		interval[i] = i * BG_SIZE_W;
	}
	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexBG();
	SetVertexBG();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		if (g_pD3DTexture != NULL)
		{	// テクスチャの開放
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		// 毎フレーム実行する処理
		g_pos.x -= 1.0f;

		// スクロール処理
		/*g_pos.x = -GetPlayer()->pos.x;*/

		if (interval[i] + BG_SIZE_W + g_pos.x < 0)	//ループ処理
		{
			interval[i] += NUM_BG * BG_SIZE_W;
		}

		// 移動後の座標で頂点を設定
		SetVertexBG();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < NUM_BG; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexture[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWk[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// 頂点座標の設定
	SetVertexBG();

	for (int i = 0; i < NUM_BG; i++)
	{
		// rhwの設定
		g_vertexWk[i][0].rhw =
			g_vertexWk[i][1].rhw =
			g_vertexWk[i][2].rhw =
			g_vertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);

		// テクスチャ座標の設定
		g_vertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBG(void)
{
	for (int i = 0; i < NUM_BG; i++)
	{
		// 頂点座標の設定
		g_vertexWk[i][0].vtx = D3DXVECTOR3(BG_POS_X + interval[i], BG_POS_Y, 0.0f) + g_pos;
		g_vertexWk[i][1].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W + interval[i], BG_POS_Y, 0.0f) + g_pos;
		g_vertexWk[i][2].vtx = D3DXVECTOR3(BG_POS_X + interval[i], BG_POS_Y + BG_SIZE_H, 0.0f) + g_pos;
		g_vertexWk[i][3].vtx = D3DXVECTOR3(BG_POS_X + BG_SIZE_W + interval[i], BG_POS_Y + BG_SIZE_H, 0.0f) + g_pos;
	}
}

//=============================================================================
// BG取得関数
//=============================================================================
void *GetBG(void)
{
	return(&g_pos);
}
