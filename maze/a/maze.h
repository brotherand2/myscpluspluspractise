
#if !defined(AFX_MAZE_H__FB7FCAE7_71BC_414B_BF7E_03C290B9E026__INCLUDED_)
#define AFX_MAZE_H__FB7FCAE7_71BC_414B_BF7E_03C290B9E026__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M                 50000         /* �Թ����ǽ���� */
#define MAX_NODE_NUMBER   50000         /* �������ڴ�ڵ� */
#define MAXGRADE          150           /* ��Ϸ����Ѷ� */
#define IDT_TIMER1        1             /* ��ʱ����� */
#define IDT_TIMER2        2
#define STEP              16            /* �������� */ 

#define RIGHT             0
#define DOWN              1
#define LEFT              2
#define UP                3

#define AUTO_MODE         0
#define PLAY_MODE         1

#define UP_WALL           0
#define LEFT_WALL         1

#define INIT              0
#define GOING             1
#define STOP              3
#define OVER              4

struct position
{
	int x;
	int y;
};

struct GameInfo
{
	struct position pos;      /* ����λ������ */
	int    size;              /* ��С */
	int    timer;
	int    nx;
	int    ny;
	int    cell;
	int    mode;
	int    mazemode;
	int    speed;
	int    times;
	int    status;
}game;

struct MazeWall
{
	struct position pos;
 	int diretcion;       /* ���� 0:�� 1:�� */
};

struct MazeCfg
{
	struct MazeWall data[M];       /* ǽ����������   */
	struct position entry, exit;   /* ��ںͳ���λ�� */
	int    num;                    /* ǽ�ڸ���       */
}maze;

struct MapCfg
{
	struct position pos;
	int    status;            /* 0:δ����, 1:���ڷ���, 2:�ѷ��� */
	int    upstatus;          /* 0:����ͨ�� 1:������ͨ�� */
	int    leftstatus;        /* 0:����ͨ�� 1:������ͨ�� */
	                          /* ÿ���ڵ�ֻ���ж�up&left�Ƿ����ͨ������ */
};

struct MapCfg  **map;

struct travInfo
{
	struct position pos;
	struct travInfo *next;
};

struct RoadInfo
{
	int    index;             /* ��� */
	int    indir;             /* ��ȥ���� */
	int    outdir;            /* ��ȥ���� */
	struct position pos;
	struct RoadInfo *next;
};

struct playercfg
{
	int    direction;
	int    steps;
	time_t usedTime, endTime, stopTime;
	struct RoadInfo *RoadPtr, *errPtr;
}play;

HWND       hWndMain;         /* �����ھ�� */
HBITMAP    h_MemBm = NULL;   /* �ڴ�λͼ */
HDC        h_MemDC = NULL;   /* �ڴ�DC */


HBRUSH  hBrushes[10];     /* ���Ʒ���Ļ�ˢ */
HBRUSH  hBrushBkGnd;     /* ����ɫ��ˢ */
HPEN    hPenBorder;      /* ���Ʊ߿��ߵĻ��� */

int initgame(HWND hWnd);
int markpath(int x, int y, int dir, int color);
int drawWall(int x, int y, int dir);
int drawMaze();
int readMazedata(int *num, int id);
char *GetFldStr(char *sFldStr, char *sStr, char sFld);
void initMalloc();
void addMallocNode(char *);
void freeMallocNode();
void *gcCalloc(size_t , size_t);
int  initBkGnd();
int createMaze();
int getWallCfg();
int setDirStatus(struct position pos, struct travInfo *head, int dir, int depth);
int createPlayer(int mode);
int destroyPlayer();
int canMove();
int doOperation();
int havePathed(struct RoadInfo node);
int newGame(int type, int mode);
void drawPath();
void showTime();
int gameOver();
int autoGo(int num);
void DisplayText(int posx, int posy, char *text);
int initGameSet(HWND hDlg);
int chgGameStatus();
void showUsedTime();
void showPlayInfo();
void errOut(char *errMsg);

#endif // !defined(AFX_MAZE_H__FB7FCAE7_71BC_414B_BF7E_03C290B9E026__INCLUDED_)
