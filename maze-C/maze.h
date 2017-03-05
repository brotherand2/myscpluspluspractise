
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

#define M                 50000         /* 迷宫最大墙壁数 */
#define MAX_NODE_NUMBER   50000         /* 最大分配内存节点 */
#define MAXGRADE          150           /* 游戏最大难度 */
#define IDT_TIMER1        1             /* 定时器编号 */
#define IDT_TIMER2        2
#define STEP              16            /* 搜索步长 */ 

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
	struct position pos;      /* 背景位置坐标 */
	int    size;              /* 大小 */
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
 	int diretcion;       /* 方向 0:横 1:竖 */
};

struct MazeCfg
{
	struct MazeWall data[M];       /* 墙壁坐标数据   */
	struct position entry, exit;   /* 入口和出口位置 */
	int    num;                    /* 墙壁个数       */
}maze;

struct MapCfg
{
	struct position pos;
	int    status;            /* 0:未访问, 1:正在访问, 2:已访问 */
	int    upstatus;          /* 0:可以通过 1:不可以通过 */
	int    leftstatus;        /* 0:可以通过 1:不可以通过 */
	                          /* 每个节点只需判断up&left是否可以通过即可 */
};

struct MapCfg  **map;

struct travInfo
{
	struct position pos;
	struct travInfo *next;
};

struct RoadInfo
{
	int    index;             /* 编号 */
	int    indir;             /* 进去方向 */
	int    outdir;            /* 出去方向 */
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

HWND       hWndMain;         /* 主窗口句柄 */
HBITMAP    h_MemBm = NULL;   /* 内存位图 */
HDC        h_MemDC = NULL;   /* 内存DC */


HBRUSH  hBrushes[10];     /* 绘制方块的画刷 */
HBRUSH  hBrushBkGnd;     /* 背景色画刷 */
HPEN    hPenBorder;      /* 绘制边框线的画笔 */

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
