#ifndef _MAZE_CLASS_H
#define _MAZE_CLASS_H

#include <iostream.h>
#include <string.h>
#include <time.h>
#include "LinkList.h"

//引入外部变量
extern HWND       hWndMain;        // 主窗口句柄
extern HBITMAP    h_MemBm;         // 内存位图
extern HDC        h_MemDC;         // 内存DC
extern RECT       rCliRet;         // 窗口大小
extern class  CMaze *game;         // 迷宫类指针
extern class  CRoom  **map;        //游戏map指针
extern HBRUSH    hBrushes[10];     //绘制路径画刷

#define RIGHT            0         //向右
#define DOWN             1         //向下
#define LEFT             2         //向左
#define UP               3         //向后
#define NODIR            4         

#define LEFT_WALL        0         //左边墙壁
#define UP_WALL          1         //上面墙壁
#define IS_WALL          0         //有墙壁
#define NO_WALL          1         //没有墙壁
#define HAS_DEAL         0         //map处理状态，已经处理
#define IN_DEAL          1         //正在处理
#define NOT_DEAL         2         //未处理
#define STEP             12        //搜索步长

#define AUTO_MODE        0         //玩家类型电脑自动
#define PLAY_MODE        1         //手动
#define INIT             0         //玩家状态初始化
#define GOING            1         //运行
#define STOP             2         //暂停
#define OVER             3         //结束

#define IDT_TIMER1       1         // 定时器编号
#define IDT_TIMER2       2

//坐标点类
class point
{
public:
	int x;
	int y;
	point();
	~point();
	point(int x, int y);
	point(const point &p);
	point &operator =(const point &p);
	bool operator ==(const point &p);
};

//Room类,生成迷宫用到
class CRoom
{
	friend class CMaze;
private:
	point  pos;
	int    status;            //0:未访问,  1:正在访问, 2:已访问
	int    upstatus;          //0:可以通过 1:不可以通过
	int    leftstatus;        //0:可以通过 1:不可以通过
	                          //每个节点只需判断up&left是否可以通过即可
};

//迷宫墙壁类
class CWall
{
	friend class CMaze;
private:
	point pos;      //墙壁位置
 	int dir;        //方向 1:横 0:竖
public:
	CWall();
	CWall(const point &pos, const int &dir);
	CWall(const CWall &p);
	~CWall();
	CWall &operator =(const CWall &p);
	bool operator ==(const CWall &p);
};

class CBoard
{
protected:
	HBRUSH    hBrush;      //绘制背景画刷
	HPEN      hPen;        //绘制边框线的画笔
	point   m_pos, m_entry, m_exit;
	int     m_size, m_cell, m_nx, m_ny;
	int     m_mode, m_speed, m_status;
	void fillCell(point pos, int color, int dir);
	void displayText(point p, char *text);
public:
	CBoard();
	~CBoard();
	int   getCell();
	int   getMode();
	int   getSpeed();
	int   getStatus();
	int   getSize();
	point getPos();
	point getEntry();
	point getExit();
	void  messageBox(char *errMsg, char *title, int style);
	void  setTimer(int id, int time);
	void  killTimer(int id);
};

//路径节点类
class CPathNode
{
	friend class CPlayer;
private:
	int   index;              //节点在链表中编号
	int   indir;              //最初进去方向
	int   outdir;             //最后一次出去方向
	class point pos;          //节点位置
public:
	CPathNode();
	CPathNode(point pos, int index, int indir, int outdir);
	~CPathNode();
	CPathNode(const CPathNode &p);
	CPathNode &operator =(const CPathNode &p);  //重载赋值运算符
	bool operator ==(const CPathNode &p);       //重载等于号
};

//游戏玩家类
class CPlayer: public CBoard
{
private:
	int  curdir;           //当前的移动方向
	int  steps;            //当前步数
	time_t usedTime, stopTime;       //所有时间用时
	LinkList <class CPathNode> path;    //保存走过的正确路径链表
	LinkList <class CPathNode> error;   //保存走过的错误路劲链表
	LinkList <class CWall> *mazeptr;    //指向当前迷宫的指针
	int  canMove();
	int  doOper();
	int  autoGo();
	void errOut(char *errMsg);
	void showInfo();
	void drawPath();
public:
	CPlayer(CMaze *maze);
	~CPlayer();
	void onKeyDown(unsigned short key);
	void onTimer(int id);
};

class CMaze: public CBoard
{
private:
	LinkList <class CWall> wlist;   //存放迷宫墙壁数据链表
	class CPlayer *m_player;
	void drawWall(class CWall wall);
	int  createWallList(LinkList<class point> *list);
	int  chgRoomStatus(point pos, LinkList<class point> *list, int dir, int depth);
	int  createMaze();
	void drawMaze();
	void showTime();
	void showHelpInfo();
	void initBkGnd();
	int  newGame();
	void gameOver();
public:
	CMaze();
	~CMaze();
	void dialogBox(HINSTANCE hInst, LPCTSTR IDD, DLGPROC myFunc);
	int  onInit();
	void initDlg(HWND hDlg);
	void onDlgOk(HWND hDlg);
	void onTimer(int id);                //游戏主控函数
	void onKeyDown(unsigned short key);  //游戏主控函数
	void onPaint(HDC hdc);
	LinkList<class CWall> *getWallList();
};

#endif
