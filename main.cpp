//=============================================================================
//
// Main���� [main.cpp]
// Author : GP11B292 29 �_�菬�t
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("AppClass")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("Wonder Alice")			// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9				g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
int						g_nCountFPS;				// FPS�J�E���^
#endif

int						g_nScene = SCENE_TITLE;		// �V�[���ԍ�
int						score_mag = SCORE_MAG_MIN;		//�X�R�A�{���̏�����

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	bool mode;
	int id = MessageBox(NULL, "Window���[�h�Ńv���C���܂����H", "�N�����[�h", MB_YESNOCANCEL | MB_ICONQUESTION);

	switch (id)
	{
	case IDYES:		// Yes�Ȃ�Window���[�h�ŋN��
		mode = true;
		break;
	case IDNO:		// No�Ȃ�t���X�N���[�����[�h�ŋN��
		mode = false;
		break;
	case IDCANCEL:	// CANCEL�Ȃ�I��
	default:
		return -1;
		break;
	}

	if (FAILED(Init(hWnd, mode)))
	{
		return -1;
	}

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	// FPS�𑪒�
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,								// �f�B�X�v���C�^�C�v
		hWnd,										// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,										// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	//// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	//g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	//// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�



	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����



#ifdef _DEBUG
																			// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
#endif

	// �T�E���h�����̏����� 
	InitSound(hWnd);

	// �v���C���[�̏���������
	InitPlayer(0);

	// �G�l�~�[�̏���������
	InitEnemy(0);

	// �I�u�W�F�N�g�̏���������
	InitObstacle(0);

	//// �o���b�g�̏���������
	InitBullet(0);

	// �X�R�A�̏���������
	InitScore(0);

	// BG�̏���������
	InitBG(0);

	// HP�̏���������
	InitHp(0);

	// �^�C�g��������
	InitTitle(0);

	// �`���[�g���A��������
	InitTutorial(0);

	// ���U���g������
	InitResult(0);

	// �t�F�[�h�����̏�����
	InitFade(0);

	// �G�t�F�N�g�����̏�����
	InitEffect(0);

	// ���g���C�̏�����
	InitRetry(0);

	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// ���͏����̏I������
	UninitInput();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �I�u�W�F�N�g�̏I������
	UninitObstacle();

	// �o���b�g�̏I������
	UninitBullet();

	// �X�R�A�̏I������
	UninitScore();

	// BG�̏I������
	UninitBG();

	// HP�̏I������
	UninitHp();

	// �^�C�g���I������
	UninitTitle();

	// �`���[�g���A���I������
	UninitTutorial();

	// ���U���g�I������
	UninitResult();

	// �t�F�[�h�����̏�����
	UninitFade();

	// �t�F�[�h�I������
	UninitFade();

	// �T�E���h�I������
	UninitSound();

	// �G�t�F�N�g�I������
	UninitEffect();

	// ���g���C�I������
	UninitRetry();

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();

	// ��ʑJ��
	switch (g_nScene)
	{
	case SCENE_TITLE:
		// �^�C�g���̍X�V����
		UpdateTitle();
		break;

	case SCENE_TUTORIAL:
		// �`���[�g���A���̍X�V����
		UpdateTutorial();
		break;

	case SCENE_GAME1:
		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();

		// �I�u�W�F�N�g�̍X�V����
		UpdateObstacle();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// BG�̍X�V����
		UpdateBG();

		// HP�̍X�V����
		UpdateHp();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �����蔻��
		CheckHit();
		break;

	case SCENE_GAME2:

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// BG�̍X�V����
		UpdateBG();

		// HP�̍X�V����
		UpdateHp();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �����蔻��
		CheckHit();
		break;

	case SCENE_RETRY:
		// ���g���C�̍X�V����
		UpdateRetry();
		break;

	case SCENE_RESULT:
		// ���U���g�̍X�V����
		UpdateResult();
		break;
	}

	// �t�F�[�h����
	UpdateFade();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(128, 128, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ��ʑJ��
		switch (g_nScene)
		{
		case SCENE_TITLE:
			// �^�C�g���̕`�揈��
			DrawTitle();
			break;

		case SCENE_TUTORIAL:
			// �`���[�g���A���̕`�揈��
			DrawTutorial();
			break;

		case SCENE_GAME1:
			// BG�̕`�揈��
			DrawBG();

			// �I�u�W�F�N�g�̕`�揈��
			DrawObstacle();

			// �G�l�~�[�̕`�揈��
			DrawEnemy();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �G�t�F�N�g�`�揈��
			DrawEffect();

			// HP�̕`�揈��
			DrawHp();

			// �X�R�A�̕`�揈��
			DrawScore();
			break;

		case SCENE_GAME2:
			// BG�̕`�揈��
			DrawBG();

			// �v���C���[�̕`�揈��
			DrawPlayer();

			// �o���b�g�̕`�揈��
			DrawBullet();

			// �G�t�F�N�g�`�揈��
			DrawEffect();

			// HP�̕`�揈��
			DrawHp();

			// �X�R�A�̕`�揈��
			DrawScore();
			break;

		case SCENE_RETRY:
			// ���g���C�̕`�揈��
			DrawRetry();
			break;

		case SCENE_RESULT:
			// ���U���g�̕`�揈��
			DrawResult();
			break;
		}

		// �t�F�[�h�`��
		DrawFade();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�擾�֐�
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}


#ifdef _DEBUG
//=============================================================================
// FPS�\������
//=============================================================================
void DrawFPS(void)
{
	char str[256];
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy();				// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet();			// �o���b�g�̃|�C���^�[��������
	SCORE *score = GetScore();				// �X�R�A�̃|�C���^�[��������
	COOKIE *cookie = GetCookie();			// �N�b�L�[�̃|�C���^�[��������


	{	// FPS�`��
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		sprintf(str, _T("FPS:%d"), g_nCountFPS);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	{	// �v���C���[�̍��W
		RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
		sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[0]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[1]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[2]);
		sprintf(str,"g_vertexWkTimer %f,%f,%f\n", cookie->vertexWk[0].vtx[3]);
		g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//{	// �o���b�g�̍��W
	//	RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };
	//	sprintf(str, "PX:%f  PY:%f�@use:%d ", bullet->pos.x, bullet->pos.y, bullet->use);
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	//}

	//{	// �v���C���[�̍��W
	//	RECT rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
	//	sprintf(str, " ���@���@���@��");
	//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0x00));
	//}

}
#endif

//=============================================================================
// Scene�J��
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
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
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
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	float len = (size1 + size2) * (size1 + size2);	// ���a��2�悵����
	D3DXVECTOR3 temp = pos1 - pos2;
	float fLengthSq = D3DXVec3LengthSq(&temp);		// 2�_�Ԃ̋����i2�悵�����j

	if (len > fLengthSq)
	{
		return true;
	}

	return false;
}


//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������
	ENEMY  *enemy = GetEnemy();				// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet();			// �o���b�g�̃|�C���^�[��������
	THORN  *thorn = GetThorn();				// ���΂�̃|�C���^�[��������
	BRICK  *brick = GetBrick();				// ��񂪂̃|�C���^�[��������
	CAKE	*cake = GetCake();				// �P�[�L�̃|�C���^�[��������
	TEA		*tea = GetTea();				// �g���̃|�C���^�[��������
	COOKIE *cookie = GetCookie();			// �N�b�L�[�̃|�C���^�[��������
	GOAL	*goal = GetGoal();				// �g���̃|�C���^�[��������
	SCORE *score = GetScore();				// �X�R�A�̃|�C���^�[��������

	// �v���C���[�ƃP�[�L
	if (player->use == true)
	{
		for (int i = 0; i < CAKE_MAX; i++)
		{
			if (cake[i].use == false)	continue;
			if (cake[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, cake[i].pos, GetPlayer()->Radius / 2, cake[i].Radius / 2))
			{
				// �A�C�e������
				cake[i].use = false;

				// �G�t�F�N�g����
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_SCOREUP);

				// �X�R�A�{���v�Z
				GetScore()->score_mag *= CAKE_SCORE;		//�X�R�A�{
				cake[i].s_cnt = false;						//�X�R�A�J�E���g��
			}
		}
	}

	// �v���C���[�ƍg��
	if (player->use == true)
	{
		for (int i = 0; i < TEA_MAX; i++)
		{
			if (tea[i].use == false)	continue;
			if (tea[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, tea[i].pos, GetPlayer()->Radius / 2, tea[i].Radius / 2))
			{
				// �A�C�e������
				tea[i].use = false;

				// �G�t�F�N�g����
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_SCOREUP);

				// �X�R�A�{���v�Z
				GetScore()->score_mag *= TEA_SCORE;			//�X�R�A�{
				tea[i].s_cnt = false;						//�X�R�A�J�E���g��
			}
		}
	}

	// �v���C���[�ƃN�b�L�[
	if (player->use == true)
	{
		for (int i = 0; i < COOKIE_MAX; i++)
		{
			if (cookie[i].use == false)	continue;
			if (cookie[i].h_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, cookie[i].pos, GetPlayer()->Radius / 2, cookie[i].Radius / 2))
			{
				// �A�C�e������
				cookie[i].use = false;

				// �G�t�F�N�g����
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ITEM);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_HPUP);

				// HP�v�Z
				AddHp(1);
				cookie[i].h_cnt = false;	//�X�R�A�J�E���g��
			}
		}
	}

	// �v���C���[�ƃG�l�~�[
	if (player->use == true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].use == false)	continue;

			if (CheckHitBC(GetPlayer()->pos, enemy[i].pos, GetPlayer()->Radius / 3, enemy[i].Radius / 3))
			{
				// �G�L�����N�^�[�͓|�����
				enemy[i].use = false;

				// HP��������
				AddHp(-1);
				GetPlayer()->dmgflag = true;	//�_���[�W�F�̓K�p
				GetPlayer()->dmg = false;	//�G�t�F�N�g�_���[�W�F�̓K�p

				// �G�t�F�N�g����
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ENEMY);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_DAMAGE);

				// �X�R�A�v�Z
				AddScore(-100, GetScore()->score_mag);
			}
		}
	}

	// �e�ƃG�l�~�[(BB)
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false) continue;	//�o���b�g���g�p�Ȃ甲����

		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if (enemy[j].use == false) continue;	//�G�l�~�[���S�Ȃ甲����

			if (CheckHitBB(bullet[i].pos, enemy[j].pos, D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y), D3DXVECTOR2(ENEMY_TEXTURE_SIZE_X, ENEMY_TEXTURE_SIZE_Y)))
			{
				bullet[i].use = false;		// �e�̏��ŏ���
				enemy[j].use = false;		// �G�l�~�[�̏��ŏ���
				AddMp(1);

				GetPlayer()->dmg = true;	//�_���[�W�F�̓K�p

				// �G�t�F�N�g����
				SetEffect(bullet[i].pos.x, bullet[i].pos.y, 30, EFFECT_TYPE_PLAYER);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_HIT);

				// �X�R�A�v�Z
				AddScore(1, GetScore()->score_mag);
				break;
			}
		}
	}

	//�v���C���[�Ƃ��΂�
	if (player->use == true)
	{
		for (int i = 0; i < THORN_MAX; i++)
		{
			if (thorn[i].use == false)	continue;
			if (thorn[i].s_cnt == false) continue;

			if (CheckHitBC(GetPlayer()->pos, thorn[i].pos, GetPlayer()->Radius / 3, thorn[i].Radius))
			{
				// HP��������
				AddHp(-1);
				GetPlayer()->dmgflag = true;	//�_���[�W�F�̓K�p
				GetPlayer()->dmg = false;	//�_���[�W�F�̓K�p

				// �G�t�F�N�g����
				SetEffect(GetPlayer()->pos.x, GetPlayer()->pos.y, 30, EFFECT_TYPE_ENEMY);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_DAMAGE);

				// �X�R�A�v�Z
				AddScore(-10, GetScore()->score_mag);
				thorn[i].s_cnt = false;					//�X�R�A�J�E���g��
			}
		}
	}

	// �e�Ƃ��΂�(BB)
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false) continue;

		for (int j = 0; j < THORN_MAX; j++)
		{
			if (thorn[j].use == false) continue;

			if (CheckHitBB(bullet[i].pos, thorn[j].pos, D3DXVECTOR2(BULLET_TEXTURE_SIZE_X, BULLET_TEXTURE_SIZE_Y), D3DXVECTOR2(THORN_TEXTURE_SIZE_X, THORN_TEXTURE_SIZE_Y)))
			{
				bullet[i].use = false;		// �e�̏��ŏ������s��
				thorn[j].use = false;		// ���΂�͓|�����

				GetPlayer()->dmg = true;	//�_���[�W�F�̓K�p

				// �G�t�F�N�g����
				SetEffect(bullet[i].pos.x, bullet[i].pos.y, 30, EFFECT_TYPE_PLAYER);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_HIT);

				// �X�R�A�v�Z
				AddScore(1, GetScore()->score_mag);

				break;
			}
		}
	}

	// ���S�������ʑJ��
	if (player->use == false)
	{
		// SetStage(STAGE_GAME_OVER);
		SetFade(FADE_OUT, SCENE_RESULT, SOUND_LABEL_BGM_GAMEOVER);
	}

	// �G���S�ł������ʑJ��
	int	cnt = 0;						//�G�l�~�[�̐����J�E���g
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].use == true)
		{
			cnt++;
		}
	}

	// ���������ʓG���S�ŁH
	if (cnt == 0)
	{
		goal->use = true;	//�S�[���o��
	}
}

//=============================================================================
// �Q�[���̍ď�������������
// �߂�l�F����
//=============================================================================
void InitGame(void)
{
	InitTutorial(1);	// �`���[�g���A���̍ď�����
	InitPlayer(1);		// �v���C���[�̍ď�����
	InitEnemy(1);		// �G�l�~�[�̍ď�����
	InitBullet(1);		// �o���b�g�̍ď�����
	InitObstacle(1);	// �o���b�g�̍ď�����
	InitScore(1);		// �X�R�A�̍ď�����
	InitHp(1);			// HP�̍ď�����
	InitBG(1);			// BG�̍ď�����
	InitEffect(1);		// �G�t�F�N�g�̍ď�����
	InitResult(1);		// ���U���g�̍ď�����
	InitRetry(1);		// ���g���C�̍ď�����
}
//=============================================================================
// BG�擾�֐�
//=============================================================================
int *GetScene(void)
{
	return(&g_nScene);
}

