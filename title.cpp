//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexLogo(void);
void SetVertexLogoColor(void);
void SetMenuDiffuse(int menu);


#define	LOGO_HIGHT			(80)							// ロゴの高さ
#define LOGO_W				(480)							// 幅
#define	PI					( D3DX_PI )						// 円周率
#define	DEG2RAD( kakudo )	( ((kakudo)*PI)/180 )			// 360度をラジアンに変換する

#define	MOZAIKU_SPEED		(0.5f)							// モザイクの移動速度
#define	MOZAIKU_BAIRITU		(3)								// モザイクの大きさ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle1 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleNewgame = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleExit = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTitle1[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitle2[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];				// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleNewgame[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleExit[NUM_VERTEX];					// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo2[LOGO_HIGHT][NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo3[LOGO_W][NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo4[LOGO_HIGHT][LOGO_W][NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo5[LOGO_HIGHT][LOGO_W][NUM_VERTEX];	// 頂点情報格納ワーク

static D3DXCOLOR		g_color;

float	sinbuf[LOGO_HIGHT];		// sin
float	sinbuf3[LOGO_W];		// sin
float	sinsize = 0;			// 200.0f;		// 半径

float	mx, my;					// モザイクの起点
float	mb;						// モザイクの倍率

static int menu; 						//メニュー用変数


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		/*テクスチャの読み込み*/
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE01,				// ファイルの名前
			&g_pD3DTextureTitle1);		// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE02,				// ファイルの名前
			&g_pD3DTextureTitle2);		// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_LOGO,			// ファイルの名前
			&g_pD3DTextureTitleLogo);	// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_NEWGAME,			// ファイルの名前
			&g_pD3DTextureTitleNewgame);	// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_EXIT,			// ファイルの名前
			&g_pD3DTextureTitleExit);	// 読み込むメモリー
	}

	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	menu = 0;	//メニュー初期化

	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if (g_pD3DTextureTitle1 != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle1->Release();
		g_pD3DTextureTitle1 = NULL;
	}

	if (g_pD3DTextureTitle2 != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle2->Release();
		g_pD3DTextureTitle2 = NULL;
	}

	if (g_pD3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DTextureTitleNewgame != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleNewgame->Release();
		g_pD3DTextureTitleNewgame = NULL;
	}

	if (g_pD3DTextureTitleExit != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleExit->Release();
		g_pD3DTextureTitleExit = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
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
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
	case 1:
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			exit(-1);		//ゲーム終了
		}
		// ゲームパッドで移動処理
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			exit(-1);		//ゲーム終了
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			exit(-1);		//ゲーム終了
		}
		break;
	}

	SetVertexLogo();

	SetVertexLogoColor();

	SetMenuDiffuse(menu);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle1);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle1, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle2);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle2, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleNewgame);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleNewgame, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleExit);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleExit, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	// 頂点座標の設定
	g_vertexWkTitle1[0].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkTitle1[1].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y, 0.0f);
	g_vertexWkTitle1[2].vtx = D3DXVECTOR3(TITLE01_POS_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);
	g_vertexWkTitle1[3].vtx = D3DXVECTOR3(TITLE01_POS_X + TITLE01_SIZE_X, TITLE01_POS_Y + TITLE01_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitle1[0].rhw =
		g_vertexWkTitle1[1].rhw =
		g_vertexWkTitle1[2].rhw =
		g_vertexWkTitle1[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitle1[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle1[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitle1[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle1[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle1[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle1[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	g_vertexWkTitle2[0].vtx = D3DXVECTOR3(TITLE02_POS_X, TITLE02_POS_Y, 0.0f);
	g_vertexWkTitle2[1].vtx = D3DXVECTOR3(TITLE02_POS_X + TITLE02_SIZE_X, TITLE02_POS_Y, 0.0f);
	g_vertexWkTitle2[2].vtx = D3DXVECTOR3(TITLE02_POS_X, TITLE02_POS_Y + TITLE02_SIZE_Y, 0.0f);
	g_vertexWkTitle2[3].vtx = D3DXVECTOR3(TITLE02_POS_X + TITLE02_SIZE_X, TITLE02_POS_Y + TITLE02_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitle2[0].rhw =
		g_vertexWkTitle2[1].rhw =
		g_vertexWkTitle2[2].rhw =
		g_vertexWkTitle2[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitle2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitle2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点座標の設定
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleLogo[0].rhw =
		g_vertexWkTitleLogo[1].rhw =
		g_vertexWkTitleLogo[2].rhw =
		g_vertexWkTitleLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//NEWGAME
	// 頂点座標の設定
	g_vertexWkTitleNewgame[0].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X, TITLE_NEWGAME_POS_Y, 0.0f);
	g_vertexWkTitleNewgame[1].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X + TITLE_MENU_SIZE_X, TITLE_NEWGAME_POS_Y, 0.0f);
	g_vertexWkTitleNewgame[2].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X, TITLE_NEWGAME_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);
	g_vertexWkTitleNewgame[3].vtx = D3DXVECTOR3(TITLE_NEWGAME_POS_X + TITLE_MENU_SIZE_X, TITLE_NEWGAME_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleNewgame[0].rhw =
		g_vertexWkTitleNewgame[1].rhw =
		g_vertexWkTitleNewgame[2].rhw =
		g_vertexWkTitleNewgame[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

	// テクスチャ座標の設定
	g_vertexWkTitleNewgame[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleNewgame[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleNewgame[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleNewgame[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//EXIT
	// 頂点座標の設定
	g_vertexWkTitleExit[0].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X, TITLE_EXIT_POS_Y, 0.0f);
	g_vertexWkTitleExit[1].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X + TITLE_MENU_SIZE_X, TITLE_EXIT_POS_Y, 0.0f);
	g_vertexWkTitleExit[2].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X, TITLE_EXIT_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);
	g_vertexWkTitleExit[3].vtx = D3DXVECTOR3(TITLE_EXIT_POS_X + TITLE_MENU_SIZE_X, TITLE_EXIT_POS_Y + TITLE_MENU_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleExit[0].rhw =
		g_vertexWkTitleExit[1].rhw =
		g_vertexWkTitleExit[2].rhw =
		g_vertexWkTitleExit[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

	// テクスチャ座標の設定
	g_vertexWkTitleExit[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleExit[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleExit[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleExit[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点の設定
//=============================================================================
void SetVertexLogo(void)
{
	float	tw = 1.0f;
	float	th = 1.0f / LOGO_HIGHT;
	float	w = 480.0f;
	float	h = 1.0f;
	float	x = 40.0f;
	float	y = 50.0f;

	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		float offset = sinbuf[i] * sinsize;

		// 頂点座標の設定
		g_vertexWkTitleLogo2[i][0].vtx = D3DXVECTOR3(x + offset, y + i * h, 0.0f);
		g_vertexWkTitleLogo2[i][1].vtx = D3DXVECTOR3(x + w + offset, y + i * h, 0.0f);
		g_vertexWkTitleLogo2[i][2].vtx = D3DXVECTOR3(x + offset, y + (i + 1)*h, 0.0f);
		g_vertexWkTitleLogo2[i][3].vtx = D3DXVECTOR3(x + w + offset, y + (i + 1)*h, 0.0f);

	}


	{	// 縦ラス
		float	tw = 1.0f / LOGO_W;
		float	th = 1.0f;
		float	w = 1.0f;		// 480.0f;
		float	h = LOGO_HIGHT;
		float	x = 40.0f;
		float	y = 150.0f;

		for (int i = 0; i < LOGO_W; i++)
		{
			float offset = sinbuf3[i] * sinsize;

			// 頂点座標の設定
			g_vertexWkTitleLogo3[i][0].vtx = D3DXVECTOR3(x + i * w, y + offset, 0.0f);
			g_vertexWkTitleLogo3[i][1].vtx = D3DXVECTOR3(x + (i + 1) * w, y + offset, 0.0f);
			g_vertexWkTitleLogo3[i][2].vtx = D3DXVECTOR3(x + i * w, y + h + offset, 0.0f);
			g_vertexWkTitleLogo3[i][3].vtx = D3DXVECTOR3(x + (i + 1) * w, y + h + offset, 0.0f);

		}
	}

	{	// 縦横ラス
		float	tw = 1.0f / LOGO_W;
		float	th = 1.0f / LOGO_HIGHT;
		float	w = 1.0f;		// 480.0f;
		float	h = 1.0f;
		float	x = 40.0f;
		float	y = 250.0f;

		for (int i = 0; i < LOGO_HIGHT; i++)
		{
			float offset = sinbuf[i] * sinsize;		// 横ラス

			for (int j = 0; j < LOGO_W; j++)
			{
				float offset3 = sinbuf3[j] * sinsize;	// 縦ラス

				// 頂点座標の設定
				g_vertexWkTitleLogo4[i][j][0].vtx = D3DXVECTOR3(x + j * w + offset, y + i * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][1].vtx = D3DXVECTOR3(x + (j + 1) * w + offset, y + i * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][2].vtx = D3DXVECTOR3(x + j * w + offset, y + (i + 1) * h + offset3, 0.0f);
				g_vertexWkTitleLogo4[i][j][3].vtx = D3DXVECTOR3(x + (j + 1) * w + offset, y + (i + 1) * h + offset3, 0.0f);
			}
		}
	}


	{	// モザイク
		float	tw = 1.0f / LOGO_W * mb;
		float	th = 1.0f / LOGO_HIGHT * mb;

		// １度元に戻す
		for (int i = 0; i < LOGO_HIGHT; i++)
		{
			for (int j = 0; j < LOGO_W; j++)
			{
				// 頂点データの設定
				g_vertexWkTitleLogo5[i][j][0].tex = g_vertexWkTitleLogo4[i][j][0].tex;
				g_vertexWkTitleLogo5[i][j][1].tex = g_vertexWkTitleLogo4[i][j][1].tex;
				g_vertexWkTitleLogo5[i][j][2].tex = g_vertexWkTitleLogo4[i][j][2].tex;
				g_vertexWkTitleLogo5[i][j][3].tex = g_vertexWkTitleLogo4[i][j][3].tex;

			}
		}

		// モザイク処理を施す
		for (int i = (int)my; i < (my + 40); i++)
		{
			// 起点が画像外の時は処理をしない
			if (i < 0) continue;
			if (i >= LOGO_HIGHT) continue;

			for (int j = (int)mx; j < (mx + 40); j++)
			{
				// 起点が画像外の時は処理をしない
				if (j < 0) continue;
				if (j >= LOGO_W) continue;

				// 頂点データの設定
				for (int k = 0; k < 4; k++)
				{
					switch (rand() % 5)
					{
					case 0:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x - tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y - th;
						break;

					case 1:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x + tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y - th;
						break;

					case 2:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x + tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y + th;
						break;

					case 3:
						g_vertexWkTitleLogo5[i][j][k].tex.x = g_vertexWkTitleLogo5[i][j][k].tex.x - tw;
						g_vertexWkTitleLogo5[i][j][k].tex.y = g_vertexWkTitleLogo5[i][j][k].tex.y + th;
						break;

					case 4:
						break;

					}

				}

			}
		}

	}

}

//=============================================================================
// 頂点色の設定
//=============================================================================
void SetVertexLogoColor(void)
{
	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		// 反射光の設定
		g_vertexWkTitleLogo2[i][0].diffuse = g_color;
		g_vertexWkTitleLogo2[i][1].diffuse = g_color;
		g_vertexWkTitleLogo2[i][2].diffuse = g_color;
		g_vertexWkTitleLogo2[i][3].diffuse = g_color;
	}

	for (int i = 0; i < LOGO_W; i++)
	{
		// 反射光の設定
		g_vertexWkTitleLogo3[i][0].diffuse = g_color;
		g_vertexWkTitleLogo3[i][1].diffuse = g_color;
		g_vertexWkTitleLogo3[i][2].diffuse = g_color;
		g_vertexWkTitleLogo3[i][3].diffuse = g_color;
	}

	for (int i = 0; i < LOGO_HIGHT; i++)
	{
		for (int j = 0; j < LOGO_W; j++)
		{
			// 反射光の設定
			g_vertexWkTitleLogo4[i][j][0].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][1].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][2].diffuse = g_color;
			g_vertexWkTitleLogo4[i][j][3].diffuse = g_color;
		}
	}
}

//=============================================================================
// メニュー色の設定
//=============================================================================
void SetMenuDiffuse(int menu)
{
	switch (menu)
	{
	case 0:
		g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		break;
	case 1:
		g_vertexWkTitleNewgame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);
		g_vertexWkTitleNewgame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 100);

		g_vertexWkTitleExit[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTitleExit[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		break;
	}
}

