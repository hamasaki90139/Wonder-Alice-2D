//=============================================================================
//
// Main�w�b�_�[ [main.h]
// Author : GP11B292 29 �_�菬�t
//
//=============================================================================
#pragma once

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <math.h>


#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

#define SCREEN_WIDTH	(640)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(480)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)					// ���_��
#define	NUM_POLYGON		(2)					// �|���S����

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��ʑJ�ڒ萔
enum E_SCENE
{
	SCENE_TITLE,
	SCENE_TUTORIAL,
	SCENE_GAME1,
	SCENE_GAME2,
	SCENE_RETRY,
	SCENE_EXTRA,
	SCENE_RESULT,
	SCENE_MAX
};

//enum E_STAGE
//{
//	STAGE_GAME1,
//	STAGE_GAME2,
//	STAGE_MAX
//};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�擾�֐�

bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
void SetScene(int Scene);
void InitGame(void);
int *GetScene(void);
