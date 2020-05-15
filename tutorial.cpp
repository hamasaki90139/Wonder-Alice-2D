//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTutorial(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial01 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial02 = NULL;		// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTutorial01[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTutorial02[NUM_VERTEX];					// 頂点情報格納ワーク

static int				g_pagecnt;		//ページ数カウント

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorial(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		 /*テクスチャの読み込み*/
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TUTORIAL01,				// ファイルの名前
			&g_pD3DTextureTutorial01);		// 読み込むメモリー

		 /*テクスチャの読み込み*/
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TUTORIAL02,				// ファイルの名前
			&g_pD3DTextureTutorial02);		// 読み込むメモリー
	}

	g_pagecnt = TUTORIAL01;		//チュートリアル画面の初期化

	// 頂点情報の作成
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	if (g_pD3DTextureTutorial01 != NULL)
	{// テクスチャの開放
		g_pD3DTextureTutorial01->Release();
		g_pD3DTextureTutorial01 = NULL;
	}
	if (g_pD3DTextureTutorial02 != NULL)
	{// テクスチャの開放
		g_pD3DTextureTutorial02->Release();
		g_pD3DTextureTutorial02 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	if (g_pagecnt == TUTORIAL01)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			g_pagecnt++;
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			g_pagecnt++;
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			g_pagecnt++;
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	if (g_pagecnt == TUTORIAL01)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureTutorial01);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial01, sizeof(VERTEX_2D));
	}
	else if (g_pagecnt == TUTORIAL02)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureTutorial02);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial02, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTutorial(void)
{

	// 頂点座標の設定
	g_vertexWkTutorial01[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial01[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial01[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial01[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTutorial01[0].rhw =
	g_vertexWkTutorial01[1].rhw =
	g_vertexWkTutorial01[2].rhw =
	g_vertexWkTutorial01[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTutorial01[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial01[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTutorial01[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial01[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial01[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial01[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkTutorial02[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial02[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial02[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial02[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTutorial02[0].rhw =
	g_vertexWkTutorial02[1].rhw =
	g_vertexWkTutorial02[2].rhw =
	g_vertexWkTutorial02[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTutorial02[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial02[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTutorial02[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial02[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial02[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial02[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

