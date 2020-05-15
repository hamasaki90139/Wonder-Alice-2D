//=============================================================================
//
// Main処理 [main.cpp]
// Author : GP11B292 29 濱崎小春
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "obstacle.h"
#include "bullet.h"
#include "score.h"
#include "bg.h"
#include "Hp.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "effect.h"
#include "retry.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")				// ウインドウのクラス名
#define WINDOW_NAME			_T("Wonder Alice")			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void CheckHit(void);
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// フォントへのポインタ
int						g_nCountFPS;				// FPSカウンタ
#endif

int						g_nScene = SCENE_TITLE;		// シーン番号
int						score_mag = SCORE_MAG_MIN;		//スコア倍率の初期化

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	bool mode;
	int id = MessageBox(NULL, "Windowモードでプレイしますか？", "起動モード", MB_YESNOCANCEL | MB_ICONQUESTION);

	switch (id)
	{
	case IDYES:		// YesならWindowモードで起動
		mode = true;
		break;
	case IDNO:		// Noならフルスクリーンモードで起動
		mode = false;
		break;
	case IDCANCEL:	// CANCELなら終了
	default:
		return -1;
		break;
	}

	if (FAILED(Init(hWnd, mode)))
	{
		return -1;
	}

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPSを測定
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定

	if (bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	//// レンダリングステートパラメータの設定
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	//g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	//// サンプラーステートパラメータの設定
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定



	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージ加算合成処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数



#ifdef _DEBUG
																			// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// サウンド処理の初期化 
	InitSound(hWnd);

	// プレイヤーの初期化処理
	InitPlayer(0);

	// エネミーの初期化処理
	InitEnemy(0);

	// オブジェクトの初期化処理
	InitObstacle(0);

	//// バレットの初期化処理
	InitBullet(0);

	// スコアの初期化処理
	InitScore(0);

	// BGの初期化処理
	InitBG(0);

	// HPの初期化処理
	InitHp(0);

	// タイトル初期化
	InitTitle(0);

	// チュートリアル初期化
	InitTutorial(0);

	// リザルト初期化
	InitResult(0);

	// フェード処理の初期化
	InitFade(0);

	// エフェクト処理の初期化
	InitEffect(0);

	// リトライの初期化
	InitRetry(0);

	// BGM再生
	PlaySound(SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 入力処理の終了処理
	UninitInput();

	// プレイヤーの終了処理
	UninitPlayer();

	// エネミーの終了処理
	UninitEnemy();

	// オブジェクトの終了処理
	UninitObstacle();

	// バレットの終了処理
	UninitBullet();

	// スコアの終了処理
	UninitScore();

	// BGの終了処理
	UninitBG();

	// HPの終了処理
	UninitHp();

	// タイトル終了処理
	UninitTitle();

	// チュートリアル終了処理
	UninitTutorial();

	// リザルト終了処理
	UninitResult();

	// フェード処理の初期化
	UninitFade();

	// フェード終了処理
	UninitFade();

	// サウンド終了処理
	UninitSound();

	// エフェクト終了処理
	UninitEffect();

	// リトライ終了処理
	UninitRetry();

	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	// 画面遷移
	switch (g_nScene)
	{
	case SCENE_TITLE:
		// タイトルの更新処理
		UpdateTitle();
		break;

	case SCENE_TUTORIAL:
		// チュートリアルの更新処理
		UpdateTutorial();
		break;

	case SCENE_GAME1:
		// プレイヤーの更新処理
		UpdatePlayer();

		// エネミーの更新処理
		UpdateEnemy();

		// オブジェクトの更新処理
		UpdateObstacle();

		// バレットの更新処理
		UpdateBullet();

		// BGの更新処理
		UpdateBG();

		// HPの更新処理
		UpdateHp();

		// スコアの更新処理
		UpdateScore();

		// エフェクトの更新処理
		UpdateEffect();

		// 当たり判定
		CheckHit();
		break;

	case SCENE_GAME2:

		// プレイヤーの更新処理
		UpdatePlayer();

		// バレットの更新処理
		UpdateBullet();

		// BGの更新処理
		UpdateBG();

		// HPの更新処理
		UpdateHp();

		// スコアの更新処理
		UpdateScore();

		// エフェクトの更新処理
		UpdateEffect();

		// 当たり判定
		CheckHit();
		break;

	case SCENE_RETRY:
		// リトライの更新処理
		UpdateRetry();
		break;

	case SCENE_RESULT:
		// リザルトの更新処理
		UpdateResult();
		break;
	}

	// フェード処理
	UpdateFade();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// 画面遷移
		switch (g_nScene)
		{
		case SCENE_TITLE:
			// タイトルの描画処理
			DrawTitle();
			break;

		case SCENE_TUTORIAL:
			// チュートリアルの描画処理
			DrawTutorial();
			break;

		case SCENE_GAME1:
			// BGの描画処理
			DrawBG();

			// オブジェクトの描画処理
			DrawObstacle();

			// エネミーの描画処理
			DrawEnemy();

			// プレイヤーの描画処理
			DrawPlayer();

			// バレットの描画処理
			DrawBullet();

			// エフェクト描画処理
			DrawEffect();

			// HPの描画処理
			DrawHp();

			// スコアの描画処理
			DrawScore();
			break;

		case SCENE_GAME2:
			// BGの描画処理
			DrawBG();

			// プレイヤーの描画処理
			DrawPlayer();

			// バレットの描画処理
			DrawBullet();

			// エフェクト描画処理
			DrawEffect();

			// HPの描画処理
			DrawHp();

			// スコアの描画処理
			DrawScore();
			break;

		case SCENE_RETRY:
			// リトライの描画処理
			DrawRetry();
			break;

		case SCENE_RESULT:
			// リザルトの描画処理
			DrawResult();
			break;
		}

		// フェード描画
		DrawFade();

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// FPS表示処理
//=============================================================================
void DrawFPS(void)
{
	char str[256];
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化
	ENEMY *enemy = GetEnemy();				// エネミーのポインターを初期化
	BULLET *bullet = GetBullet();			// バレットのポインターを初期化
	SCORE *score = GetScore();				// スコアのポインターを初期化
	COOKIE *cookie = GetCookie();			// クッキーのポインターを初期化


	{	// FPS描画
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		sprintf(str, _T("FPS:%d"), g_nCountFPS);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	{	// プレイヤーの座標
		RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
		sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[0]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[1]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[2]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[3]);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//{	// バレットの座標
	//	RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	//	sprintf(str, "PX:%f  PY:%f　use:%d ", bullet->pos.x, bullet->pos.y, bullet->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	//}

	//{	// プレイヤーの座標
	//	RECT rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
	//	sprintf(str, " ←　↑　→　↓");
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0x00));
	//}

}
#endif

//=============================================================================
// Scene遷移
//=============================================================================
void SetScene(int Scene)
{

	switch (Scene)
	{
	case SCENE_TITLE:
		InitGame();
		break;
	case SCENE_RETRY:
		InitRetry(1);
		break;
	case SCENE_GAME2:
		if (GetSceneold() != SCENE_GAME2)
		{
			InitGame();
		}
		break;
	}
	g_nScene = Scene;
}


//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	if ((pos1.x + size1.x > pos2.x - size2.x) && (pos1.x - size1.x < pos2.x + size2.x) &&
		(pos1.y + size1.y > pos2.y - size2.y) && (pos1.y - size1.y < pos2.y + size2.y))
	{
		return true;
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	float len = (size1 + size2) * (size1 + size2);	// 半径を2乗した物
	D3DXVECTOR3 temp = pos1 - pos2;
	float fLengthSq = D3DXVec3LengthSq(&temp);		// 2点間の距離（2乗した物）

	if (len > fLengthSq)
	{
		return true;
	}

	return false;
}


//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化
	ENEMY  *enemy = GetEnemy();				// エネミーのポインターを初期化
	BULLET *bullet = GetBullet();			// バレットのポインターを初期化
	THORN  *thorn = GetThorn();				// いばらのポインターを初期化
	BRICK  *brick = GetBrick();				// れんがのポインターを初期化
	CAKE	*cake = GetCake();				// ケーキのポインターを初期化
	TEA		*tea = GetTea();				// 紅茶のポインターを初期化
	COOKIE *cookie = GetCookie();			// クッキーのポインターを初期化
	GOAL	*goal = GetGoal();				// 紅茶のポインターを初期化
	SCORE *score = GetScore();				// スコアのポインターを初期化

	// プレイヤーとケーキ
	if (player->use == true)
	{
		for (int i = 0; i < CAKE_MAX; i++)
		{
			if (cake[i].use == false)	continue;
			if (cake[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, cake[i].pos, GetPlayer()->Radius / 2, cake[i].Radius / 2))
			{
				// アイテム消滅
				cake[i].use = false;

				// エフェクト発生
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE再生
				PlaySound(SOUND_LABEL_SE_SCOREUP);

				// スコア倍率計算
				GetScore()->score_mag *= CAKE_SCORE;		//スコア倍
				cake[i].s_cnt = false;						//スコアカウント済
			}
		}
	}

	// プレイヤーと紅茶
	if (player->use == true)
	{
		for (int i = 0; i < TEA_MAX; i++)
		{
			if (tea[i].use == false)	continue;
			if (tea[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, tea[i].pos, GetPlayer()->Radius / 2, tea[i].Radius / 2))
			{
				// アイテム消滅
				tea[i].use = false;

				// エフェクト発生
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE再生
				PlaySound(SOUND_LABEL_SE_SCOREUP);

				// スコア倍率計算
				GetScore()->score_mag *= TEA_SCORE;			//スコア倍
				tea[i].s_cnt = false;						//スコアカウント済
			}
		}
	}

	// プレイヤーとクッキー
	if (player->use == true)
	{
		for (int i = 0; i < COOKIE_MAX; i++)
		{
			if (cookie[i].use == false)	continue;
			if (cookie[i].h_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, cookie[i].pos, GetPlayer()->Radius / 2, cookie[i].Radius / 2))
			{
				// アイテム消滅
				cookie[i].use = false;

				// エフェクト発生
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE再生
				PlaySound(SOUND_LABEL_SE_HPUP);

				// HP計算
				AddHp(1);
				cookie[i].h_cnt = false;	//スコアカウント済
			}
		}
	}

	// プレイヤーとエネミー
	if (player->use == true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].use == false)	continue;

			if (CheckHitBC(GetPlayer()->pos, enemy[i].pos, GetPlayer()->Radius / 3, enemy[i].Radius / 3))
			{
				// 敵キャラクターは倒される
				enemy[i].use = false;

				// HP減少処理
				AddHp(-1);
				GetPlayer()->dmgflag = true;	//ダメージ色の適用
				GetPlayer()->dmg = false;	//エフェクトダメージ色の適用

				// エフェクト発生
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ENEMY);

				// SE再生
				PlaySound(SOUND_LABEL_SE_DAMAGE);

				// スコア計算
				AddScore(-100, GetScore()->score_mag);
			}
		}
	}

	// 弾とエネミー(BB)
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false) continue;	//バレット未使用なら抜ける

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if (enemy[j].use == false) continue;	//エネミー死亡なら抜ける

			if (CheckHitBB(bullet[i].pos, enemy[j].pos, D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y), D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y)))
			{
				bullet[i].use = false;		// 弾の消滅処理
				enemy[j].use = false;		// エネミーの消滅処理
				AddMp(1);

				GetPlayer()->dmg = true;	//ダメージ色の適用

				// エフェクト発生
				SetEffect(bullet[i].pos.x, bullet[i].pos.y, 30, EFFECT_TYPE_PLAYER);

				// SE再生
				PlaySound(SOUND_LABEL_SE_HIT);

				// スコア計算
				AddScore(1, GetScore()->score_mag);
				break;
			}
		}
	}

	//プレイヤーといばら
	if (player->use == true)
	{
		for (int i = 0; i < THORN_MAX; i++)
		{
			if (thorn[i].use == false)	continue;
			if (thorn[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, thorn[i].pos, GetPlayer()->Radius / 3, thorn[i].Radius))
			{
				// HP減少処理
				AddHp(-1);
				GetPlayer()->dmgflag = true;	//ダメージ色の適用
				GetPlayer()->dmg = false;	//ダメージ色の適用

				// エフェクト発生
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ENEMY);

				// SE再生
				PlaySound(SOUND_LABEL_SE_DAMAGE);

				// スコア計算
				AddScore(-10, GetScore()->score_mag);
				thorn[i].s_cnt = false;					//スコアカウント済
			}
		}
	}

	// 弾といばら(BB)
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false) continue;

		for (int j = 0; j < THORN_MAX; j++)
		{
			if (thorn[j].use == false) continue;

			if (CheckHitBB(bullet[i].pos, thorn[j].pos, D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y), D3DXVECTOR2(THORN_TEXTURE_SIZE_X, THORN_TEXTURE_SIZE_Y)))
			{
				bullet[i].use = false;		// 弾の消滅処理を行い
				thorn[j].use = false;		// いばらは倒される

				GetPlayer()->dmg = true;	//ダメージ色の適用

				// エフェクト発生
				SetEffect(bullet[i].pos.x, bullet[i].pos.y, 30, EFFECT_TYPE_PLAYER);

				// SE再生
				PlaySound(SOUND_LABEL_SE_HIT);

				// スコア計算
				AddScore(1, GetScore()->score_mag);

				break;
			}
		}
	}

	// 死亡したら画面遷移
	if (player->use == false)
	{
		// SetStage(STAGE_GAME_OVER);
		SetFade(FADE_OUT, SCENE_RESULT, SOUND_LABEL_BGM_GAMEOVER);
	}

	// 敵が全滅したら画面遷移
	int	cnt = 0;						//エネミーの生存カウント
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].use == true)
		{
			cnt++;
		}
	}

	// 数えた結果敵が全滅？
	if (cnt == 0)
	{
		goal->use = true;	//ゴール出現
	}
}

//=============================================================================
// ゲームの再初期化処理処理
// 戻り値：無し
//=============================================================================
void InitGame(void)
{
	InitTutorial(1);	// チュートリアルの再初期化
	InitPlayer(1);		// プレイヤーの再初期化
	InitEnemy(1);		// エネミーの再初期化
	InitBullet(1);		// バレットの再初期化
	InitObstacle(1);	// バレットの再初期化
	InitScore(1);		// スコアの再初期化
	InitHp(1);			// HPの再初期化
	InitBG(1);			// BGの再初期化
	InitEffect(1);		// エフェクトの再初期化
	InitResult(1);		// リザルトの再初期化
	InitRetry(1);		// リトライの再初期化
}
//=============================================================================
// BG取得関数
//=============================================================================
int *GetScene(void)
{
	return(&g_nScene);
}

