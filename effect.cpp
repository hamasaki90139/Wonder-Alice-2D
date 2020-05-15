//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define EMISSION 1
#define EMISSION_FULL 0
#define EMISSION_RATE 1

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(int i);
void SetTextureEffect(int i, int n, int cntPattern);
void SetVertexEffect(int i, int n);
void ResetParticle(int i, int n);
void StartEffect(int i);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// テクスチャへのポリゴン

static EFFECT					effectWk[EFFECT_NUM_EFFECTS];	// エフェクト構造体

static int g_isActive = 1;
static int g_effectCount;
static int g_emitCounter = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			EFFECT_TEXTURE,										// ファイルの名前
			&g_pD3DTextureEffect);								// 読み込むメモリのポインタ
	}

	// 初期化処理
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		effectWk[i].use = false;
		effectWk[i].elapsed = 0;

		for (int n = 0; n < EFFECT_NUM_PARTS; n++) {

			effectWk[i].pParticle[n].Texture = g_pD3DTextureEffect;

			MakeVertexEffect(i);										// 頂点情報の作成

			ResetParticle(i, n);
		}
	}

	return S_OK;
}

void ResetParticle(int i, int n) {

	effectWk[i].pParticle[n].pos = D3DXVECTOR3(effectWk[i].pos.x + rand() % 30 - 15, effectWk[i].pos.y + rand() % 30 - 15, 0.0f);	// 座標データを初期化
	effectWk[i].pParticle[n].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動量

	effectWk[i].pParticle[n].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
	effectWk[i].pParticle[n].CountAnim = 0;										// アニメカウントを初期化
	effectWk[i].pParticle[n].liveTime = 30;
	effectWk[i].pParticle[n].isFinish = 0;
}

void StartEffect(int i)
{
	for (int n = 0; n < EFFECT_NUM_PARTS; n++)
	{
		ResetParticle(i, n);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if (g_pD3DTextureEffect != NULL)
	{	// テクスチャの開放
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++) {

		if (effectWk[i].use)
		{
			if (effectWk[i].isEnding) {
				effectWk[i].use = FALSE;
				continue;
			}

			//エミットが有効であればエフェクト作成処理を行う
			if (effectWk[i].isRemoveOnFinish == FALSE) {

				//エフェクト作成レートの増加処理
				if (effectWk[i].effectCount < EFFECT_NUM_PARTS) {
					effectWk[i].emitCounter++;
				}

				//バッファに空きがあり、追加タイミングが来ていれば新たなエフェクトを追加する
				while ((effectWk[i].effectCount < EFFECT_NUM_PARTS) && (effectWk[i].emitCounter > EMISSION_RATE)) {
					//全体追加フラグがONであれば空き領域全てに新たなエフェクトを追加する
					if (EMISSION_FULL)
						effectWk[i].effectCount = EFFECT_NUM_PARTS;
					else {
						effectWk[i].effectCount++;
					}

					//エフェクト作成レートの初期化
					effectWk[i].emitCounter = 0;
				}

				effectWk[i].elapsed++;

				//時間超過
				if ((effectWk[i].duration != -1) && (effectWk[i].duration < effectWk[i].elapsed)) {
					effectWk[i].isRemoveOnFinish = TRUE;
				}
			}

			int effectIndex = 0;

			//エフェクトの更新処理
			while (effectIndex < effectWk[i].effectCount)
			{
				if (effectWk[i].pParticle[effectIndex].liveTime > 0) {

					//生存フレーム減少
					effectWk[i].pParticle[effectIndex].liveTime--;

					//アニメパターン進行
					if (++effectWk[i].pParticle[effectIndex].CountAnim > EFFECT_TIME_ANIMATION) {
						//アニメパターンが最大値に達した場合でも終了
						if (++effectWk[i].pParticle[effectIndex].PatternAnim >= EFFECT_ANIM_PATTERN_NUM) {
							effectWk[i].pParticle[effectIndex].PatternAnim = EFFECT_ANIM_PATTERN_NUM - 1;
							effectWk[i].pParticle[effectIndex].liveTime = 0;
						}

						effectWk[i].pParticle[effectIndex].CountAnim = 0;
					}

					SetTextureEffect(i, effectIndex, effectWk[i].pParticle[effectIndex].PatternAnim);
					SetVertexEffect(i, effectIndex);						// 移動後の座標で頂点を設定
					effectIndex++;
				}
				else {
					if (effectWk[i].isRemoveOnFinish) {
						if (effectWk[i].pParticle[effectIndex].isFinish == 0) {
							effectWk[i].pParticle[effectIndex].isFinish = 1;
							effectWk[i].numFinish++;
						}
						//終了処理
						if (effectWk[i].numFinish == effectWk[i].effectCount) {
							effectWk[i].isEnding = TRUE;

							// 反射光の初期化
							effectWk[i].pParticle[effectIndex].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
							effectWk[i].pParticle[effectIndex].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

							break;
						}
						effectIndex++;
					}
					else {
						//バッファを初期化する
						ResetParticle(i, effectIndex);

						//末尾でなければインデックスを詰める
						if (effectIndex != (g_effectCount - 1)) {
							effectWk[i].pParticle[effectIndex] = effectWk[i].pParticle[effectWk[i].effectCount - 1];
							ResetParticle(i, (effectWk[i].effectCount - 1));
						}
						effectWk[i].effectCount--;
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		if (effectWk[i].use) {

			for (int n = 0; n < effectWk[i].effectCount; n++) {
				// テクスチャの設定
				pDevice->SetTexture(0, effectWk[i].pParticle[n].Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, effectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < EFFECT_NUM_PARTS; n++) {

		// 頂点座標の設定
		SetVertexEffect(i, n);
		// 頂点座標の設定
		SetTextureEffect(i, n, 0);

		// rhwの設定
		effectWk[i].pParticle[n].vertexWk[0].rhw =
			effectWk[i].pParticle[n].vertexWk[1].rhw =
			effectWk[i].pParticle[n].vertexWk[2].rhw =
			effectWk[i].pParticle[n].vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEffect(int i, int n, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / EFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / EFFECT_TEXTURE_PATTERN_DIVIDE_Y;

	effectWk[i].pParticle[n].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effectWk[i].pParticle[n].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effectWk[i].pParticle[n].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effectWk[i].pParticle[n].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect(int i, int n)
{
	// 頂点座標の設定
	effectWk[i].pParticle[n].vertexWk[0].vtx.x = effectWk[i].pParticle[n].pos.x - EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[0].vtx.y = effectWk[i].pParticle[n].pos.y - EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[0].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[1].vtx.x = effectWk[i].pParticle[n].pos.x + EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[1].vtx.y = effectWk[i].pParticle[n].pos.y - EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[1].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[2].vtx.x = effectWk[i].pParticle[n].pos.x - EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[2].vtx.y = effectWk[i].pParticle[n].pos.y + EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[2].vtx.z = 0.0f;

	effectWk[i].pParticle[n].vertexWk[3].vtx.x = effectWk[i].pParticle[n].pos.x + EFFECT_TEXTURE_SIZE_X;
	effectWk[i].pParticle[n].vertexWk[3].vtx.y = effectWk[i].pParticle[n].pos.y + EFFECT_TEXTURE_SIZE_Y;
	effectWk[i].pParticle[n].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトのセット
//=============================================================================
void SetEffect(float x, float y, int duration, int type)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化

	// もし未使用のエフェクトが無かったら実行しない( =これ以上表示できないって事 )
	for (int i = 0; i < EFFECT_NUM_EFFECTS; i++)
	{
		if (effectWk[i].use == false)		// 未使用状態のエフェクトを見つける
		{
			effectWk[i].use = true;
			effectWk[i].isEnding = false;
			effectWk[i].isRemoveOnFinish = FALSE;

			effectWk[i].duration = duration;
			effectWk[i].pos.x = x;			// 座標をセット
			effectWk[i].pos.y = y;			// 座標をセット

			effectWk[i].effectCount = 0;
			effectWk[i].elapsed = 0;
			effectWk[i].emitCounter = 0;
			effectWk[i].numFinish = 0;

			for (int n = 0; n < EFFECT_NUM_PARTS; n++)
			{
				// 反射光の設定
				switch (type)
				{
				case EFFECT_TYPE_PLAYER:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;

				case EFFECT_TYPE_ENEMY:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(100, 0, 255, 255);
					break;

				case EFFECT_TYPE_ITEM:
					effectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					effectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
					break;
				}
			}
			StartEffect(i);

			return;							// 1個セットしたので終了する
		}
	}
}