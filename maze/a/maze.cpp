// maze.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "maze.h"
#include "maze_pub.cpp"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK GameSet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MAZE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MAZE);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MAZE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_MAZE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

/*
   hWnd = CreateWindow(szWindowClass, "迷宫游戏", WS_OVERLAPPEDWINDOW,
					100, 40, 700, 640+28, NULL, NULL, hInstance, NULL); 
*/
   hWnd = CreateWindow(szWindowClass, "迷宫游戏", WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
					80, 30, 850, 620+28, NULL, NULL, hInstance, NULL); 

   if (!hWnd)
   {
      return FALSE;
   }

   initgame(hWnd);

   if(createMaze() < 0)
	   return FALSE;

   drawMaze();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   DialogBox(hInst, (LPCTSTR)IDD_GAME_SET, hWnd, (DLGPROC)GameSet);

   createPlayer(game.mode);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, ret = 0;
	unsigned short key = 0;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDM_GAMESET:
					KillTimer(hWndMain, IDT_TIMER2);
					DialogBox(hInst, (LPCTSTR)IDD_GAME_SET, hWnd, (DLGPROC)GameSet);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			BitBlt(hdc,0,0,rt.right-rt.left,rt.bottom-rt.top,h_MemDC,0,0,SRCCOPY);
			EndPaint(hWnd, &ps);
			break;
		case WM_KEYDOWN:
			key=wParam;
			switch(key)
			{
			case 0x1b:             /* ESC结束程序 */
				gameOver();
				break;
			case 0x25:             /* left */
				if(game.mode == PLAY_MODE && game.status == GOING)
				{
					play.direction = LEFT;
					ret = doOperation();
					if(ret != 0)
						gameOver();
				}
				break;
			case 0x26:             /* up */
				if(game.mode == PLAY_MODE && game.status == GOING)
				{
					play.direction = UP;
					ret = doOperation();
					if(ret != 0)
						gameOver();
				}
				break;
			case 0x27:             /* right */
				if(game.mode == PLAY_MODE && game.status == GOING)
				{
					play.direction = RIGHT;
					ret = doOperation();
					if(ret != 0)
						gameOver();
				}
				break;
			case 0x28:             /* down */
				if(game.mode == PLAY_MODE && game.status == GOING)
				{
					play.direction = DOWN;
					ret = doOperation();
					if(ret != 0)
						gameOver();
				}
				break;
			case ' ':
				chgGameStatus();
				break;
			}
			break;
		case WM_TIMER:
			//定时器处理
			switch(wParam)
			{
			case IDT_TIMER1: /*定时器IDT_TIMER1消息*/
				showTime();
				break;
			case IDT_TIMER2: /*定时器IDT_TIMER2消息*/
				if(game.mode == AUTO_MODE && game.status == GOING)
				{
					ret = autoGo(game.times);
					if(ret != 0)
						gameOver();
				}
				if(game.status == GOING)
				{
					showPlayInfo();
				}
				break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


LRESULT CALLBACK GameSet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, cell;
	switch (message)
	{
		case WM_INITDIALOG:
				initGameSet(hDlg);				
				return TRUE;

		case WM_COMMAND:
			wmId = LOWORD(wParam);
			switch(wmId)
			{
			case IDOK:
				destroyPlayer();
				cell = game.cell;
				game.cell = GetDlgItemInt(hDlg, IDC_EDIT_CELL, NULL, NULL);
				game.speed = GetDlgItemInt(hDlg, IDC_EDIT_SPEED, NULL, NULL);

				if(game.speed > 10)
					game.times = game.speed - 10 + 1;
				else
					game.times = 1;

				if(game.speed <= 10)
					game.timer = (10 - game.speed)*10 + 1;
				else
					game.timer = 1;

				if(game.cell < 7)
					game.cell = 7;
				if(game.cell > 100)
					game.cell = 100;

				if(IsDlgButtonChecked(hDlg, IDC_RADIO_PLAY) == TRUE) 
					game.mode = PLAY_MODE;
				if(IsDlgButtonChecked(hDlg, IDC_RADIO_AUTO) == TRUE)
					game.mode = AUTO_MODE;
				EndDialog(hDlg, LOWORD(wParam));

				if(game.cell != cell)
				{
					game.nx = game.size/game.cell;
					game.ny = game.nx*10/13;
					createMaze();				
				}
				initBkGnd();
				drawMaze();
				createPlayer(game.mode);
				SetTimer(hWndMain, IDT_TIMER2, game.timer, (TIMERPROC)NULL);

				return TRUE;
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
	}
    return FALSE;
}


int initGameSet(HWND hDlg)
{
	SetDlgItemInt(hDlg, IDC_EDIT_CELL, game.cell, NULL);
	SetDlgItemInt(hDlg, IDC_EDIT_SPEED, game.speed, NULL);
	if(game.mode == PLAY_MODE)
	{
		CheckDlgButton(hDlg, IDC_RADIO_PLAY, TRUE);
		CheckDlgButton(hDlg, IDC_RADIO_AUTO, FALSE);
	}
	else
	{
		CheckDlgButton(hDlg, IDC_RADIO_PLAY, FALSE);
		CheckDlgButton(hDlg, IDC_RADIO_AUTO, TRUE);
	}


	return 0;
}

int initgame(HWND hWnd)
{
	HDC hDC;
	RECT rc;

	hWndMain = hWnd;    /* 复制主窗口句柄 */

	GetClientRect(hWndMain, &rc);

	/* 创建内存位图 */
	hDC = GetDC(hWnd);
	h_MemDC = CreateCompatibleDC(hDC);
	h_MemBm = CreateCompatibleBitmap(hDC, rc.right-rc.left, rc.bottom-rc.top);

	/* 边框 */
	hPenBorder = CreatePen(PS_SOLID, 1, 0x404040);
	/* 背景 */
	hBrushBkGnd = CreateSolidBrush(0x00);

	SelectObject(h_MemDC, hPenBorder);
	SelectObject(h_MemDC, h_MemBm);
	ReleaseDC(hWnd, hDC);

	/* 绘制路径和迷宫墙壁 */
	hBrushes[0] = CreateSolidBrush(RGB(0, 0, 255));
	hBrushes[1] = CreateSolidBrush(RGB(0, 255, 0));
	hBrushes[2] = CreateSolidBrush(RGB(255, 0, 0));
	hBrushes[3] = CreateSolidBrush(RGB(3, 238, 10));
	hBrushes[4] = CreateSolidBrush(RGB(10, 211, 170));
	hBrushes[5] = CreateSolidBrush(RGB(204, 0, 170));
	hBrushes[6] = CreateSolidBrush(RGB(51, 176 , 30));
	hBrushes[7] = CreateSolidBrush(RGB(255, 255, 255));
	hBrushes[8] = CreateSolidBrush(RGB(0, 0, 0));
	hBrushes[9] = CreateSolidBrush(RGB(50, 50, 50));

	memset(&game, 0x00, sizeof(game));
	/* 游戏参数 */
	game.pos.x = 10;
	game.pos.y = 10;
	game.size = 700;
	game.cell = 20;
	game.speed = 8;
	game.mazemode = 0;
	game.timer = 1;
	game.times = 1;

	game.nx = game.size/game.cell;
	game.ny = game.nx*10/13;
	game.mode = AUTO_MODE;
	game.status = INIT;

	SetTimer(hWnd, IDT_TIMER1, 1000, (TIMERPROC)NULL);

	initBkGnd();

	return 0;
}

int newGame(int type, int mode)
{
	initBkGnd();

	if(type == 0)
	{
		if(createMaze() < 0)
			return -1;
	}
	drawMaze();

	if(createPlayer(mode) < 0)
		return -1;
	return 0;
}

int gameOver()
{
	game.status = OVER;
	DisplayText((game.nx -3) * game.cell/2, game.ny * game.cell + 20, "按空格开始新游戏");
	destroyPlayer();
	return 0;
}

int initBkGnd()
{
	int i = 0;
	RECT rc;
	SYSTEMTIME sysTime;

	GetClientRect(hWndMain, &rc);

	FillRect(h_MemDC, &rc, hBrushBkGnd);

#if 0
	/* 绘制网格线 */
	for(i = 0; i <= game.nx; i++)
	{
		MoveToEx(h_MemDC, game.pos.x + i*game.cell, game.pos.y, NULL);
		LineTo(h_MemDC, game.pos.x + i*game.cell, game.pos.y + game.ny*game.cell);
	}
	
	for(i = 0; i <= game.ny; i++)
	{
		MoveToEx(h_MemDC, game.pos.x, game.pos.y + i*game.cell, NULL);
		LineTo(h_MemDC, game.pos.x + game.nx*game.cell, game.pos.y + i*game.cell);
	}
#endif
	/* 绘制边框 */
	MoveToEx(h_MemDC, game.pos.x - 4, game.pos.y - 4, NULL);
	LineTo(h_MemDC, game.pos.x + game.nx*game.cell + 4, game.pos.y - 4);
	LineTo(h_MemDC,game.pos.x + game.nx*game.cell + 4, game.pos.y + game.ny*game.cell + 4);
	LineTo(h_MemDC,game.pos.x - 4, game.pos.y + game.ny*game.cell + 4);
	LineTo(h_MemDC,game.pos.x - 4, game.pos.y - 4);

	showTime();

	/* 根据系统时间生成随机种子 */
	GetLocalTime(&sysTime);
	srand(sysTime.wHour*3600+sysTime.wMinute*60+sysTime.wSecond+sysTime.wMilliseconds);

	return 0;
}

int markpath(int x, int y, int dir, int color)
{
	RECT rc;

	rc.left= game.pos.x + x*game.cell + 2;
	rc.top= game.pos.y + y*game.cell + 2;
	rc.right = rc.left + game.cell - 4;
	rc.bottom = rc.top + game.cell - 4;

	switch(dir)
	{
	case RIGHT:
		rc.right += 4;
		break;
	case DOWN:
		rc.bottom += 4;
		break;
	case LEFT:
		rc.left -= 4;
		break;
	case UP:
		rc.top -= 4;
		break;
	}
	FillRect(h_MemDC, &rc, hBrushes[color]);
	InvalidateRect(hWndMain, NULL, FALSE);

	return 0;
}

int drawWall(int x, int y, int dir)
{
	RECT rc;

	if(dir == UP_WALL)
	{
		rc.left= game.pos.x + x*game.cell;
		rc.top= game.pos.y + y*game.cell - 1;
		rc.right = rc.left + game.cell;
		rc.bottom = rc.top + 2;
	}
	else
	{
		rc.left= game.pos.x + x*game.cell - 1;
		rc.top= game.pos.y + y*game.cell;
		rc.right = rc.left + 2;
		rc.bottom = rc.top + game.cell;
	}

	FillRect(h_MemDC, &rc, hBrushes[6]);
	InvalidateRect(hWndMain, NULL, FALSE);

	return 0;
}

int drawMaze()
{
	int i = 0;

	markpath(maze.entry.x, maze.entry.y, 4, 0);
	markpath(maze.exit.x, maze.exit.y, 4, 7);

	for(i = 0; i < maze.num; i ++)
		drawWall(maze.data[i].pos.x, maze.data[i].pos.y, maze.data[i].diretcion);

	return 0;
}

/* 采用图的深度优先遍历算法,生成迷宫 */
int createMaze()
{
	int i = 0, j = 0, flag = 0;
	struct position pos;

	memset(&pos, 0x00, sizeof(pos));
	memset(&maze, 0x00, sizeof(maze));

	initMalloc();   /* 初始化动态分配内存结构 */

	/* 入口 */
	flag = rand()%4;
	if(flag == 0)
	{
		maze.entry.x = 0;
		maze.entry.y = rand()%game.ny;
	}
	if(flag == 1)
	{
		maze.entry.x = game.nx -1;
		maze.entry.y = rand()%game.ny;
	}
	if(flag == 2)
	{
		maze.entry.x = rand()%game.nx;
		maze.entry.y = 0;
	}
	if(flag == 3)
	{
		maze.entry.x = rand()%game.nx;
		maze.entry.y = game.ny-1;
	}

	/* 出口 */
	maze.exit.x = game.nx - maze.entry.x - 1;
	maze.exit.y = game.ny - maze.entry.y - 1;

	if(getWallCfg() < 0)
	{
		freeMallocNode();
		return -1;
	}
	/* 释放内存 */
	freeMallocNode();

	return 0;
}

/* 生成迷宫墙壁数据 */
int getWallCfg()
{
	struct travInfo *phead, *t = NULL, *p = NULL;
	struct position pos;
	int    randomdir = 0, i= 0, j = 0, ret = 0, travtype = 0;
	int    dir = 0, count = 0;

	void  **maphead = NULL, **mapbody = NULL;

	/* map二维数组动态分配内存 */
	maphead = (void **)gcCalloc(sizeof(void *) + sizeof(struct MapCfg)*game.ny, game.nx);
	if(maphead == NULL)
	{
		MessageBox(hWndMain, "分配内存失败", "错误", MB_OK);
		return -1;
	}

	mapbody = maphead + game.nx;
	for(i = 0; i < game.nx; i++)
         maphead[i] = mapbody + i*game.ny*sizeof(struct MapCfg)/sizeof(void *);

	map = (struct MapCfg **)maphead;

	/* 初始化map数据 */
	for(i = 0; i < game.nx; i ++)
	{
		for(j = 0; j < game.ny; j ++)
		{
			map[i][j].pos.x = i;
			map[i][j].pos.y = j;
			map[i][j].status = 0;
			map[i][j].upstatus = 1;
			map[i][j].leftstatus = 1;
		}
	}

	phead = (struct travInfo *)gcCalloc(sizeof(struct travInfo), 1);
	if(phead == NULL)
	{
		MessageBox(hWndMain, "分配内存失败", "错误", MB_OK);
		return -1;
	}
	memset(phead, 0x00, sizeof(struct travInfo));

	phead->pos.x = 0;       /* 借用此字段保存链表中节点数 */
	phead->next = NULL;

	pos.x = rand()%game.nx;
	pos.y = rand()%game.ny;

	randomdir = rand()%4;

	for(i = 0; i < 4; i ++)
	{					
		ret = setDirStatus(pos, phead, (randomdir + i)%4, 1);
		if(ret < 0)
			return -1;
	}

	count = 1;
	for(;;)
	{
		if(phead->next == NULL)
			break;

		count ++;

		if(count < STEP)
		{
			/* 从链表中删除第一个节点 */
			t = phead->next;
			if(t == NULL)
			{
				MessageBox(hWndMain, "查找链表节点错误", "错误", MB_OK);
				return -1;
			}
			phead->next = t->next;
			phead->pos.x --;
		}
		/* 到达搜索步长,强制停止,从正在处理的节点中随机选择一个继续搜索 */
		else
		{
			j = rand()%(phead->pos.x);

			p = phead;
			for(i = 0; i < j; i++)
			{
				if(p == NULL)
				{
					MessageBox(hWndMain, "查找链表节点错误", "错误", MB_OK);
					return -1;
				}
				p = p->next;
			}

			/* 从链表中删除节点 */
			t = p->next;
			if(t == NULL)
			{
				MessageBox(hWndMain, "查找链表节点错误", "错误", MB_OK);
				return -1;
			}
			p->next = t->next;
			phead->pos.x --;
			count = 0;		
		}

		/* 生成随机方向 */
		randomdir = rand()%4;
		travtype = randomdir%2;  /* 搜索方向,0顺时针,1逆时针*/

		for(i = 0; i < 4; i ++)
		{			
			if(travtype == 0)
				ret = setDirStatus(t->pos, phead, (randomdir + i)%4, randomdir);			
			else					
				ret = setDirStatus(t->pos, phead, (4 + randomdir - i)%4, randomdir);

			if(ret < 0)
				return -1;
		}
	}

	maze.num = 0;
	/* 赋值wall数据 */
	for(i = 0; i < game.nx; i ++)
	{
		for(j = 0; j < game.ny; j ++)
		{
			if(maze.num >= M)
				return 0;
			if(map[i][j].leftstatus == 1)
			{
				maze.data[maze.num].diretcion = LEFT_WALL;
				maze.data[maze.num].pos.x = i;
				maze.data[maze.num].pos.y = j;
				maze.num ++;
			}

			if(maze.num >= M)
				return 0;
			if(map[i][j].upstatus == 1)
			{
				maze.data[maze.num].diretcion = UP_WALL;
				maze.data[maze.num].pos.x = i;
				maze.data[maze.num].pos.y = j;
				maze.num ++;
			}

			if(maze.num >= M)
				return 0;
			if(i == (game.nx -1))
			{
				maze.data[maze.num].diretcion = LEFT_WALL;
				maze.data[maze.num].pos.x = i + 1;
				maze.data[maze.num].pos.y = j;
				maze.num ++;
			}
			
			if(maze.num >= M)
				return 0;
			if(j == (game.ny -1))
			{
				maze.data[maze.num].diretcion = UP_WALL;
				maze.data[maze.num].pos.x = i;
				maze.data[maze.num].pos.y = j+1;
				maze.num ++;
			}
		}
	}

	return 0;
}

/* 判断位置pos,dir方向节点处理状态,并修改处理状态 */
int setDirStatus(struct position pos, struct travInfo *head, int dir, int depth)
{
	struct travInfo *t = NULL;
	struct position tpos;

	memset(&tpos, 0x00, sizeof(struct position));

	tpos.x = pos.x;
	tpos.y = pos.y;

	/* 修改处理标志 */
	map[pos.x][pos.y].status = 2;

	switch(dir)
	{
	case RIGHT:                     /* RIGHT */
		tpos.x = pos.x + 1;
		break;
	case DOWN:                     /* DOWN */
		tpos.y = pos.y + 1;
		break;
	case LEFT:                     /* LEFT */
		tpos.x = pos.x -1;
		break;
	case UP:                     /* UP   */
		tpos.y = pos.y - 1;
		break;
	default:
		MessageBox(hWndMain, "错误探索方向", "错误", MB_OK);
		return -1;
	}

	/* 出界不可以通过, 返回*/
	if(tpos.x < 0 || tpos.y < 0 || tpos.x >= game.nx || tpos.y >= game.ny)
	{
		return 0;
	}

	/* 未被访问,则修改为正在访问,开辟一条路径 */
	if(map[tpos.x][tpos.y].status == 0)
	{
		/* 修改处理状态 */
		map[tpos.x][tpos.y].status = 1;

		/* 插入正在处理链表 */
		t = (struct travInfo *)gcCalloc(sizeof(struct travInfo), 1);
		if(t == NULL)
		{
			MessageBox(hWndMain, "分配内存失败", "错误", MB_OK);
			return -1;
		}
		memset(t, 0x00, sizeof(struct travInfo));

		t->pos.x = tpos.x;
		t->pos.y = tpos.y;
		t->next = NULL;

		t->next = head->next;
		head->next = t;
		head->pos.x ++;

		/* 修改墙壁标志 */
		switch(dir)
		{
		case RIGHT:                     /* RIGHT */
			map[tpos.x][tpos.y].leftstatus = 0;
			break;
		case DOWN:                     /* DOWN */
			map[tpos.x][tpos.y].upstatus = 0;
			break;
		case LEFT:                     /* LEFT */
			map[pos.x][pos.y].leftstatus = 0;
			break;
		case UP:                     /* UP   */
			map[pos.x][pos.y].upstatus = 0;
			break;
		default:
			MessageBox(hWndMain, "错误探索方向", "错误", MB_OK);
			return -1;
		}
	}
	if(depth <= 0)
		return 0;

	if(setDirStatus(tpos, head, dir, depth-1) < 0)
		return -1;

	return 0;
}

int createPlayer(int mode)
{
	initMalloc();

	game.mode = mode;
	game.status = INIT;
	play.direction = rand()%4;
	play.steps = 0;
	play.usedTime = 0;
	play.endTime = play.stopTime = time(NULL);

	play.errPtr = NULL;

	play.RoadPtr = (struct RoadInfo *)gcCalloc(sizeof(struct RoadInfo), 1);
	if(play.RoadPtr == NULL)
	{
		MessageBox(hWndMain, "分配内存失败", "错误", MB_OK);
		return -1;
	}
	memset(play.RoadPtr, 0x00, sizeof(struct RoadInfo));

	play.RoadPtr->indir = play.direction;
	play.RoadPtr->outdir = play.RoadPtr->indir;
	play.RoadPtr->index = 1;
	play.RoadPtr->pos.x = maze.entry.x;
	play.RoadPtr->pos.y = maze.entry.y;
	play.RoadPtr->next = NULL;

	DisplayText((game.nx -3) * game.cell/2, game.ny * game.cell + 20, "按空格开始");

	return 0;
}

int destroyPlayer()
{
	freeMallocNode();
	return 0;
}

void drawPath()
{
	struct RoadInfo *p;

	markpath(maze.entry.x, maze.entry.y, 4, 0);

	p = play.errPtr;
	for(;;)
	{
		if(p == NULL)
			break;
		markpath(p->pos.x, p->pos.y, p->outdir, 2);
		p = p->next;
	}

	p = play.RoadPtr;
	for(;;)
	{
		if(p == NULL)
			break;
		markpath(p->pos.x, p->pos.y, p->outdir, 1);
		p = p->next;
	}
}

int canMove()
{
	int i = 0;
	struct MazeWall twall;

	memset(&twall, 0x00, sizeof(twall));

	twall.pos.x = play.RoadPtr->pos.x;
	twall.pos.y = play.RoadPtr->pos.y;
	switch(play.direction)
	{
	case RIGHT:
		twall.pos.x += 1;
		twall.diretcion = LEFT_WALL;
		break;
	case DOWN:
		twall.pos.y += 1;
		twall.diretcion = UP_WALL;
		break;
	case LEFT:
		twall.diretcion = LEFT_WALL;
		break;
	case UP:
		twall.diretcion = UP_WALL;
		break;
	}

	for(i = 0; i < maze.num; i ++)
	{
		if(twall.diretcion == maze.data[i].diretcion &&
			twall.pos.x == maze.data[i].pos.x &&
			twall.pos.y == maze.data[i].pos.y)
		{
			return -1;
		}
	}

	return 0;
}

int havePathed(struct RoadInfo node)
{
	struct RoadInfo *cur;
	cur = play.RoadPtr;

	for(;;)
	{
		if(cur == NULL)
			break;

		if(cur->pos.x == node.pos.x &&
			cur->pos.y == node.pos.y)
		{
			return 0;
		}
		cur = cur->next;
	}

	return -1;
}

void errOut(char *errMsg)
{
	game.status = 3;
	MessageBox(hWndMain, errMsg, "错误", MB_OK);
}

int doOperation()
{
	struct position pos;
	struct RoadInfo *t, *cur;
	int ret = 0;

	if(canMove() < 0)
		return 0;

	cur = play.RoadPtr;
	pos.x = cur->pos.x;
	pos.y = cur->pos.y;
	switch(play.direction)
	{
	case RIGHT:
		pos.x += 1;
		break;
	case DOWN:
		pos.y += 1;
		break;
	case LEFT:
		pos.x -= 1;
		break;
	case UP:
		pos.y -= 1;
		break;
	}

	cur->outdir = play.direction;
	markpath(cur->pos.x, cur->pos.y, 4, 8);
	play.steps ++;

	/* 如果是后退,则直接删除当前节点 */
	if(cur->next != NULL && cur->outdir == cur->indir)
	{
		markpath(pos.x, pos.y, 4, 0);

		play.RoadPtr = cur->next;
		cur->next = play.errPtr;
		play.errPtr = cur;
		return 0;
	}

	if(pos.x == maze.exit.x &&
		pos.y == maze.exit.y)
	{
		drawPath();
		return 1;
	}

	t = (struct RoadInfo *)gcCalloc(sizeof(struct RoadInfo), 1);
	if(t == NULL)
	{
		errOut("分配内存失败");
		return -1;
	}
	memset(t, 0x00, sizeof(struct RoadInfo));

	t->index = cur->index + 1;
	t->indir = (play.direction + 2)%4;
	t->outdir = t->indir;
	t->pos.x = pos.x;
	t->pos.y = pos.y;
	t->next = NULL;

	t->next = play.RoadPtr;
	play.RoadPtr = t;

	markpath(t->pos.x, t->pos.y, 4, 0);

	return 0;
}

int autoGo(int num)
{
	struct position pos;
	struct RoadInfo *t, *cur;
	int ret = 0, count = 0;

	if(num <= 0)
		num = 1;
	if(num >= 5)
		num = 5;

	for(int i = 0; i < num; i ++)
	{
		cur = play.RoadPtr;	
		/* 从上次出去的方向顺时针搜索 */
		count = 0;
		for(;;)
		{
			count ++;
			if(count > 4)
			{
				errOut("墙壁配置错误");
				return -1;
			}
			
			cur->outdir = (cur->outdir + 1)%4;
			play.direction = cur->outdir;
			
			if(canMove() == 0)
				break;
		}
		
		pos.x = cur->pos.x;
		pos.y = cur->pos.y;
		switch(play.direction)
		{
		case RIGHT:
			pos.x += 1;
			break;
		case DOWN:
			pos.y += 1;
			break;
		case LEFT:
			pos.x -= 1;
			break;
		case UP:
			pos.y -= 1;
			break;
		}
		play.steps ++;
		
		/* 如果是后退,则直接删除当前节点 */
		if(cur->next != NULL && cur->outdir == cur->indir)
		{
			markpath(cur->pos.x, cur->pos.y, cur->outdir, 2);
			
			play.RoadPtr = cur->next;  /* 从链表中删除 */
			
			cur->next = play.errPtr;   /* 插入错误路径 */
			play.errPtr = cur;
			continue;
		}
		
		markpath(cur->pos.x, cur->pos.y, cur->outdir, 1);
		
		if(pos.x == maze.exit.x &&
			pos.y == maze.exit.y)
		{
			gameOver();
			return 1;
		}
		
		t = (struct RoadInfo *)gcCalloc(sizeof(struct RoadInfo), 1);
		if(t == NULL)
		{
			errOut("分配内存失败");
			return -1;
		}
		memset(t, 0x00, sizeof(struct RoadInfo));
		
		t->index = cur->index + 1;
		t->indir = (play.direction + 2)%4;
		t->outdir = t->indir;
		t->pos.x = pos.x;
		t->pos.y = pos.y;
		t->next = NULL;
		
		t->next = play.RoadPtr;
		play.RoadPtr = t;
	}

	return 0;
}

void DisplayText(int posx, int posy, char *text)
{
	RECT rc;

	rc.left=game.pos.x + posx - 4;
	rc.top=game.pos.x + posy - 4;
	rc.right=rc.left + 8*strlen(text) + 8;
	rc.bottom=rc.top + 28;

	FillRect(h_MemDC,&rc, hBrushBkGnd);

	TextOut(h_MemDC, game.pos.x + posx, game.pos.y + posy,text,strlen(text));
	
	InvalidateRect(hWndMain,&rc,FALSE);	
}

/*显示当前时间*/
void showTime()
{
	char sCurTime[64];
	struct tm *tmtime; 
	time_t curtime;

	memset(sCurTime, 0x00, sizeof(sCurTime));

	curtime = time(NULL);
	tmtime = localtime(&curtime);

	sprintf(sCurTime, "时间: %02d:%02d:%02d ", 
		tmtime->tm_hour, tmtime->tm_min, tmtime->tm_sec);

	DisplayText(game.size + 12 , game.pos.y, sCurTime);

	if(game.mode == PLAY_MODE)
		DisplayText(game.size + 12 , game.pos.y + 30, "模式【计时】");

	else
		DisplayText(game.size + 12 , game.pos.y + 30, "模式【演示】");
}

void showPlayInfo()
{
	char sbuf[64];

	play.endTime = time(NULL);

	memset(sbuf, 0x00, sizeof(sbuf));
	sprintf(sbuf, "用时:  %d 秒  ",   play.usedTime + play.endTime-play.stopTime);
	
	DisplayText(game.size + 12 , game.pos.y + 60, sbuf);
	
	memset(sbuf, 0x00, sizeof(sbuf));
	sprintf(sbuf, "步数: %d  ", play.steps);
	DisplayText(game.size + 12 , game.pos.y + 90, sbuf);
}

int chgGameStatus()
{
	if(game.status == INIT)      /* 游戏开始 */
	{
		DisplayText((game.nx -3) * game.cell/2, game.ny * game.cell + 20, "按空格暂停");
		play.stopTime = time(NULL);
		play.usedTime = 0;
		game.status = GOING;
	}
	else if(game.status == OVER) /* 游戏结束 */
	{
		game.mazemode = 0;
		if(newGame(game.mazemode, game.mode) < 0)
			return -1;
	}
	else if(game.status == GOING)  /* 游戏运行 */
	{
		play.usedTime += (time(NULL)- play.stopTime);
		DisplayText((game.nx -3) * game.cell/2, game.ny * game.cell + 20, "按空格开始");
		game.status = STOP;
	}
	else
	{
		play.stopTime = time(NULL);
		DisplayText((game.nx -3) * game.cell/2, game.ny * game.cell + 20, "按空格暂停");
		game.status = GOING;
	}
	return 0;
}
