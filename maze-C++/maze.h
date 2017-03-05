
#if !defined(AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_)
#define AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


#endif // !defined(AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_)

//全局变量
#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

#include "MazeClass.h"

class CMaze   *game = NULL;   //迷宫类对象指针
class CRoom   **map;          //游戏map指针    

HWND       hWndMain;          //主窗口句柄
HBITMAP    h_MemBm = NULL;    //内存位图
HDC        h_MemDC = NULL;    //内存DC
RECT       rCliRet;           //游戏窗口大小
HBRUSH     hBrushes[10];      //绘制方块的画刷

#endif