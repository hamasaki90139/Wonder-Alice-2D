//=============================================================================
//
// リトライ画面処理 [retry.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "retry.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRetry(void);
void SetVertexLogo(void);
void SetVertexLogoColor(void);
void SetRetryMenuDiffuse(int menu);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRetrybg = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRetry = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureReturn = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkRetrybg[NUM_VERTEX];					// 頂点情報格納ワークVERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];				// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkRetry[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkReturn[NUM_VERTEX];					// 頂点情報格納ワーク

static D3DXCOLOR		g_color;

static int menu; 						//メニュー用変数
static int scene;



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRetry(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		/*テクスチャの読み込み*/
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE01,				// ファイルの名前
			&g_pD3DTextureRetrybg);		// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_NEWGAME,			// ファイルの名前
			&g_pD3DTextureRetry);	// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_EXIT,			// ファイルの名前
			&g_pD3DTextureReturn);	// 読み込むメモリー
	}

	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	menu = 0;	//メニュー初期化

	// 頂点情報の作成
	MakeVertexRetry();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRetry(void)
{
	if (g_pD3DTextureRetrybg != NULL)
	{// テクスチャの開放
		g_pD3DTextureRetrybg->Release();
		g_pD3DTextureRetrybg = NULL;
	}

	if (g_pD3DTextureRetry != NULL)
	{// テクスチャの開放
		g_pD3DTextureRetry->Release();
		g_pD3DTextureRetry = NULL;
	}

	if (g_pD3DTextureReturn != NULL)
	{// テクスチャの開放
		g_pD3DTextureReturn->Release();
		g_pD3DTextureReturn = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRetry(void)
{
	 //int *scene=GetScene();				// スコアのポインターを初期化
	scene = GetSceneold();	//1つ前のシーンのセット

	//menu選択
	if (GetKeyboardRepeat(DIK_UP)|| GetKeyboardRepeat(DIK_DOWN)|| 
		(IsButtonTriggered(0, BUTTON_UP)) || (IsButtonTriggered(0, BUTTON_DOWN)))
	{
		menu = (menu + 1) % MENU_MAX;
	}

	switch (menu)
	{
	case 0:
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_TITLE, SOUND_LABEL_BGM_TITLE);
		}
		break;
	case 1:		//キャンセル
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			if (scene== SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if(scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			if (scene == SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if (scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			if (scene == SCENE_GAME1)
			{
				SetFade(FADE_OUT, SCENE_GAME1, SOUND_LABEL_BGM_GAME);
			}
			else if (scene == SCENE_GAME2)
			{
				SetFade(FADE_OUT, SCENE_GAME2, SOUND_LABEL_BGM_GAME);
			}
		}
		break;
	}

	SetVertexLogo();

	SetVertexLogoColor();

	SetRetryMenuDiffuse(menu);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRetrybg);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRetrybg, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRetry);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRetry, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureReturn);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkReturn, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRetry(void)
{
	// 頂点座標の設定
	g_vertexWkRetrybg[0].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkRetrybg[1].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkRetrybg[2].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);
	g_vertexWkRetrybg[3].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkRetrybg[0].rhw =
	g_vertexWkRetrybg[1].rhw =
	g_vertexWkRetrybg[2].rhw =
	g_vertexWkRetrybg[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRetrybg[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_vertexWkRetrybg[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

	// テクスチャ座標の設定
	g_vertexWkRetrybg[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRetrybg[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRetrybg[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRetrybg[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkRetry[0].vtx = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y, 0.0f);
	g_vertexWkRetry[1].vtx = D3DXVECTOR3(RETRY_POS_X + RETRYMENU_SIZE_X, RETRY_POS_Y, 0.0f);
	g_vertexWkRetry[2].vtx = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y + RETRYMENU_SIZE_Y, 0.0f);
	g_vertexWkRetry[3].vtx = D3DXVECTOR3(RETRY_POS_X + RETRYMENU_SIZE_X, RETRY_POS_Y + RETRYMENU_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkRetry[0].rhw =
	g_vertexWkRetry[1].rhw =
	g_vertexWkRetry[2].rhw =
	g_vertexWkRetry[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkRetry[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRetry[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRetry[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRetry[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkReturn[0].vtx = D3DXVECTOR3(RETURN_POS_X, RETURN_POS_Y, 0.0f);
	g_vertexWkReturn[1].vtx = D3DXVECTOR3(RETURN_POS_X + RETRYMENU_SIZE_X, RETURN_POS_Y, 0.0f);
	g_vertexWkReturn[2].vtx = D3DXVECTOR3(RETURN_POS_X, RETURN_POS_Y + RETRYMENU_SIZE_Y, 0.0f);
	g_vertexWkReturn[3].vtx = D3DXVECTOR3(RETURN_POS_X + RETRYMENU_SIZE_X, RETURN_POS_Y + RETRYMENU_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkReturn[0].rhw =
	g_vertexWkReturn[1].rhw =
	g_vertexWkReturn[2].rhw =
	g_vertexWkReturn[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkReturn[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkReturn[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkReturn[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkReturn[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// メニュー色の設定
//=============================================================================
void SetRetryMenuDiffuse(int menu)
{
	switch (menu)
	{
	case 0:
		g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		break;
	case 1:
		g_vertexWkRetry[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkRetry[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

		g_vertexWkReturn[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkReturn[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		break;
	}
}

