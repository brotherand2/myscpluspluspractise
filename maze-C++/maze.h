
#if !defined(AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_)
#define AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


#endif // !defined(AFX_MAZE_H__07B79E4D_5188_4AC4_BA75_2937E4F48C49__INCLUDED_)

//ȫ�ֱ���
#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

#include "MazeClass.h"

class CMaze   *game = NULL;   //�Թ������ָ��
class CRoom   **map;          //��Ϸmapָ��    

HWND       hWndMain;          //�����ھ��
HBITMAP    h_MemBm = NULL;    //�ڴ�λͼ
HDC        h_MemDC = NULL;    //�ڴ�DC
RECT       rCliRet;           //��Ϸ���ڴ�С
HBRUSH     hBrushes[10];      //���Ʒ���Ļ�ˢ

#endif