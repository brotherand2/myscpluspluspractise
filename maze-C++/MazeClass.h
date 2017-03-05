#ifndef _MAZE_CLASS_H
#define _MAZE_CLASS_H

#include <iostream.h>
#include <string.h>
#include <time.h>
#include "LinkList.h"

//�����ⲿ����
extern HWND       hWndMain;        // �����ھ��
extern HBITMAP    h_MemBm;         // �ڴ�λͼ
extern HDC        h_MemDC;         // �ڴ�DC
extern RECT       rCliRet;         // ���ڴ�С
extern class  CMaze *game;         // �Թ���ָ��
extern class  CRoom  **map;        //��Ϸmapָ��
extern HBRUSH    hBrushes[10];     //����·����ˢ

#define RIGHT            0         //����
#define DOWN             1         //����
#define LEFT             2         //����
#define UP               3         //���
#define NODIR            4         

#define LEFT_WALL        0         //���ǽ��
#define UP_WALL          1         //����ǽ��
#define IS_WALL          0         //��ǽ��
#define NO_WALL          1         //û��ǽ��
#define HAS_DEAL         0         //map����״̬���Ѿ�����
#define IN_DEAL          1         //���ڴ���
#define NOT_DEAL         2         //δ����
#define STEP             12        //��������

#define AUTO_MODE        0         //������͵����Զ�
#define PLAY_MODE        1         //�ֶ�
#define INIT             0         //���״̬��ʼ��
#define GOING            1         //����
#define STOP             2         //��ͣ
#define OVER             3         //����

#define IDT_TIMER1       1         // ��ʱ�����
#define IDT_TIMER2       2

//�������
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

//Room��,�����Թ��õ�
class CRoom
{
	friend class CMaze;
private:
	point  pos;
	int    status;            //0:δ����,  1:���ڷ���, 2:�ѷ���
	int    upstatus;          //0:����ͨ�� 1:������ͨ��
	int    leftstatus;        //0:����ͨ�� 1:������ͨ��
	                          //ÿ���ڵ�ֻ���ж�up&left�Ƿ����ͨ������
};

//�Թ�ǽ����
class CWall
{
	friend class CMaze;
private:
	point pos;      //ǽ��λ��
 	int dir;        //���� 1:�� 0:��
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
	HBRUSH    hBrush;      //���Ʊ�����ˢ
	HPEN      hPen;        //���Ʊ߿��ߵĻ���
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

//·���ڵ���
class CPathNode
{
	friend class CPlayer;
private:
	int   index;              //�ڵ��������б��
	int   indir;              //�����ȥ����
	int   outdir;             //���һ�γ�ȥ����
	class point pos;          //�ڵ�λ��
public:
	CPathNode();
	CPathNode(point pos, int index, int indir, int outdir);
	~CPathNode();
	CPathNode(const CPathNode &p);
	CPathNode &operator =(const CPathNode &p);  //���ظ�ֵ�����
	bool operator ==(const CPathNode &p);       //���ص��ں�
};

//��Ϸ�����
class CPlayer: public CBoard
{
private:
	int  curdir;           //��ǰ���ƶ�����
	int  steps;            //��ǰ����
	time_t usedTime, stopTime;       //����ʱ����ʱ
	LinkList <class CPathNode> path;    //�����߹�����ȷ·������
	LinkList <class CPathNode> error;   //�����߹��Ĵ���·������
	LinkList <class CWall> *mazeptr;    //ָ��ǰ�Թ���ָ��
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
	LinkList <class CWall> wlist;   //����Թ�ǽ����������
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
	void onTimer(int id);                //��Ϸ���غ���
	void onKeyDown(unsigned short key);  //��Ϸ���غ���
	void onPaint(HDC hdc);
	LinkList<class CWall> *getWallList();
};

#endif
