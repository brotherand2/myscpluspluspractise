#include "stdafx.h"
#include "LinkList.cpp"
#include "resource.h"

//////////////////////////////////////////////
point::point()
{
	this->x = 0;
	this->y = 0;
}

point::~point()
{
}

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
}

point::point(const point &p)
{
	x = p.x;
	y = p.y;
}

point &point::operator =(const point &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

bool point::operator ==(const point &p)
{
	if(x == p.x && y == p.y)
		return true;
	return false;
}

//////////////////////////////////////////////
CWall::CWall()
{
	dir = 0;
}

CWall::CWall(const point &pos, const int &dir)
{
	this->pos = pos;
	this->dir = dir;
}

CWall::CWall(const CWall &p)
{
	this->pos = p.pos;
	this->dir = p.dir;
}


CWall::~CWall()
{
}

CWall &CWall::operator =(const CWall &p)
{
	this->pos = p.pos;
	this->dir = p.dir;
	return *this;
}

bool CWall::operator ==(const CWall &p)
{
	if(this->dir == p.dir && this->pos == p.pos)
		return true;
	return false;
}

//////////////////////////////////////////////
CBoard::CBoard()
{
	m_mode = AUTO_MODE;
	m_speed = 4;
	m_size = 700;
	m_status = INIT;
	m_pos = point(20, 10);
	m_entry = point(0, 0);
	m_exit = point(0, 0);
	m_cell = 20;
	m_nx = m_size/m_cell;
	m_ny = m_nx*10/13;
}

CBoard::~CBoard()
{
}

int CBoard::getCell()
{
	return m_cell;
}

int CBoard::getMode()
{
	return m_mode;
}

int CBoard::getSpeed()
{
	return m_speed;
}

int CBoard::getStatus()
{
	return m_status;
}

int CBoard::getSize()
{
	return m_size;
}

point CBoard::getPos()
{
	return this->m_pos;
}

point CBoard::getEntry()
{
	return this->m_entry;
}

point CBoard::getExit()
{
	return this->m_exit;
}

void CBoard::messageBox(char *errMsg, char *title, int style)
{
	MessageBox(hWndMain, errMsg, title, style);
}

void CBoard::setTimer(int id, int time)
{
	SetTimer(hWndMain, id, time, (TIMERPROC)NULL);
}

void CBoard::killTimer(int id)
{
	KillTimer(hWndMain, id);
}

void CBoard::fillCell(point pos, int color, int dir)
{
	RECT rc;

	rc.left= m_pos.x + pos.x*m_cell + 2;
	rc.top= m_pos.y + pos.y*m_cell + 2;
	rc.right = rc.left + m_cell - 4;
	rc.bottom = rc.top + m_cell - 4;

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
	case NODIR:
		break;
	}

	FillRect(h_MemDC, &rc, hBrushes[color]);
	InvalidateRect(hWndMain, NULL, FALSE);
}

void CBoard::displayText(point p, char *text)
{
	RECT rc;

	rc.left=m_pos.x + p.x - 4;
	rc.top=m_pos.y + p.y - 4;
	rc.right=rc.left + 200;
	rc.bottom=rc.top + 28;

	FillRect(h_MemDC, &rc, hBrush);

	TextOut(h_MemDC, m_pos.x + p.x, m_pos.y + p.y, text, strlen(text));
	
	InvalidateRect(hWndMain, &rc, FALSE);
}

//////////////////////////////////////////////
CPathNode::CPathNode()
{
	this->index = 0;
	this->indir = 0;
	this->outdir = 0;
	this->pos = point(0, 0);
}

CPathNode::CPathNode(point pos, int index, int indir, int outdir)
{
	this->pos = pos;
	this->index = index;
	this->indir = indir;
	this->outdir = outdir;
}

CPathNode::CPathNode(const CPathNode &p)
{
	index = p.index;
	indir = p.indir;
	outdir = p.outdir;
	pos = p.pos;
}

CPathNode::~CPathNode()
{
}

CPathNode &CPathNode::operator =(const CPathNode &p)
{
	index = p.index;
	indir = p.indir;
	outdir = p.outdir;
	pos = p.pos;
	return *this;
}

bool CPathNode::operator ==(const CPathNode &p)
{
	if(pos == p.pos)
		return true;
	return false;
}

///////////////////////////////////////////////////
CPlayer::CPlayer(CMaze *maze)
{
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_pos = maze->getPos();
	m_size = maze->getSize();
	m_cell = maze->getCell();
	m_nx = m_size/m_cell;
	m_ny = m_nx*10/13;
	m_mode = maze->getMode();

	m_entry = maze->getEntry();
	m_exit = maze->getExit();
	mazeptr = maze->getWallList();

	m_status = INIT;

	curdir = rand()%4;
	usedTime = 0;
	stopTime = time(NULL);
	steps = 0;
	path.clear();
	error.clear();
	path.insertFront(CPathNode(m_entry, 1, curdir, curdir));
}

CPlayer::~CPlayer()
{
	path.clear();
	error.clear();
	mazeptr = NULL;
}

void CPlayer::errOut(char *errMsg)
{
	m_status = OVER;
	messageBox(errMsg, "错误", MB_OK);
}

void CPlayer::showInfo()
{
	char sbuf[64];

	memset(sbuf, 0x00, sizeof(sbuf));
	sprintf(sbuf, " 用时:  %d 秒 ",   usedTime + time(NULL) - stopTime);
	
	displayText(point(m_cell*m_nx + 14 , m_pos.y + 60), sbuf);
	
	memset(sbuf, 0x00, sizeof(sbuf));
	sprintf(sbuf, " 步数: %d ", steps);
	displayText(point(m_cell*m_nx + 14 , m_pos.y + 90), sbuf);
}

void CPlayer::drawPath()
{
	error.reset();
	while(error.current() != NULL)
	{
		fillCell(error.current()->data.pos, 2, error.current()->data.outdir);
		error.next();
	}

	path.reset();
	while(path.current() != NULL)
	{
		fillCell(path.current()->data.pos, 1, path.current()->data.outdir);
		path.next();
	}
	path.clear();
	error.clear();
}

int CPlayer::canMove()
{
	int i = 0, direct = 0;
	point nextpos;

	Node<class CPathNode> *cur = NULL;

	path.reset();
	cur = path.current();

	if(cur == NULL)
	{
		errOut("链表为空");
		return -1;
	}

	nextpos = cur->data.pos;

	switch(this->curdir)
	{
	case RIGHT:
		nextpos.x += 1;
		direct = LEFT_WALL;
		break;
	case DOWN:
		nextpos.y += 1;
		direct = UP_WALL;
		break;
	case LEFT:
		direct = LEFT_WALL;
		break;
	case UP:
		direct = UP_WALL;
		break;
	}

	//如果找到了说明不可以通过
	if(mazeptr->findNode(CWall(nextpos, direct)) != NULL)		
		return 1;

	return 0;
}

int CPlayer::doOper()
{
	point  nextpos;
	Node<class CPathNode> *cur = NULL;
	int ret = 0, outdir = 0;

	ret = canMove();
	if(ret < 0)    return -1;
	if(ret == 1)   return 0;

	path.reset();
	cur = path.current();

	if(cur == NULL)
	{
		errOut("链表为空");
		return -1;
	}

	nextpos = cur->data.pos;

	switch(this->curdir)
	{
	case RIGHT:
		nextpos.x += 1;
		break;
	case DOWN:
		nextpos.y += 1;
		break;
	case LEFT:
		nextpos.x -= 1;
		break;
	case UP:
		nextpos.y -= 1;
		break;
	}

	cur->data.outdir = this->curdir;
	fillCell(cur->data.pos, 8, NODIR);
	steps ++;

	// 如果是后退,则直接删除当前节点
	if(cur->next() != NULL && cur->data.outdir == cur->data.indir)
	{
//		fillCell(cur->data.pos, 2, this->curdir);
		fillCell(nextpos, 0, NODIR);

		if(error.insertFront(cur->data) < 0)
		{
			errOut("插入错误路径链表失败");
			return -1;
		}

		ret = path.deleteFront(NULL);
		if(ret < 0)
		{
			errOut("删除节点失败");
			return -1;
		}
		return 0;
	}

//	fillCell(cur->data.pos, 1, this->curdir);

	if(nextpos == m_exit)
	{
		drawPath();
		m_status = OVER;
		return 1;
	}

	ret = path.insertFront(CPathNode(nextpos, cur->data.index + 1, (this->curdir + 2)%4, (this->curdir + 2)%4));
	if(ret < 0)
	{
		errOut("插入链表失败");
		return -1;
	}
	fillCell(nextpos, 0, NODIR);

	return 0;
}

int CPlayer::autoGo()
{
	point nextpos;
	Node<class CPathNode> *cur = NULL;
	int ret = 0, count = 0;

	path.reset();
	cur = path.current();

	if(cur == NULL)
	{
		errOut("迷宫无解");
		return -1;
	}
	
	count = 0;
	for(;;)
	{
		count ++;
		if(count > 4)
		{
			errOut("迷宫配置错误");
			return -1;
		}
		
		cur->data.outdir = (cur->data.outdir + 1)%4;
		curdir = cur->data.outdir;

		ret = canMove();
		if(ret == 0)
			break;
		if(ret < 0)
			return -1;
	}
	
	nextpos = cur->data.pos;

	switch(curdir)
	{
	case RIGHT:
		nextpos.x += 1;
		break;
	case DOWN:
		nextpos.y += 1;
		break;
	case LEFT:
		nextpos.x -= 1;
		break;
	case UP:
		nextpos.y -= 1;
		break;
	}
	steps ++;
	
	// 如果是后退,则直接删除当前节点
	if(path.next() != NULL&&cur->data.outdir == cur->data.indir)
	{
		fillCell(cur->data.pos, 2, cur->data.outdir);
		ret = path.deleteFront(NULL);
		if(ret < 0)
		{
			errOut("删除节点失败");
			return -1;
		}
		return 0;
	}
	fillCell(cur->data.pos, 1, cur->data.outdir);
	
	if(nextpos == m_exit)
	{
		m_status = OVER;
		return 1;
	}

	fillCell(nextpos, 1, NODIR);
	
	ret = path.insertFront(CPathNode(nextpos, cur->data.index + 1, (this->curdir + 2)%4, (this->curdir + 2)%4));
	if(ret < 0)
	{
		errOut("插入路径链表失败");
		return -1;
	}

	return 0;
}

void CPlayer::onKeyDown(unsigned short key)
{
	
	int ret = 0;
	switch(key)
	{
	case 0x25:             // left
		if(m_mode == PLAY_MODE && m_status == GOING)
		{
			curdir = LEFT;
			ret = doOper();
		}
		break;
	case 0x26:             // up
		if(m_mode == PLAY_MODE && m_status == GOING)
		{
			curdir = UP;
			ret = doOper();
		}
		break;
	case 0x27:             // right
		if(m_mode == PLAY_MODE && m_status == GOING)
		{
			curdir = RIGHT;
			ret = doOper();
		}
		break;
	case 0x28:             // down
		if(m_mode == PLAY_MODE && m_status == GOING)
		{
			curdir = DOWN;
			ret = doOper();
		}
		break;
	case ' ':
			if(m_status == GOING)
			{
				usedTime += (time(NULL) - stopTime);
				stopTime = time(NULL);
				m_status = STOP;
			}
			else if(m_status == STOP)
			{
				stopTime = time(NULL);
				m_status = GOING;
			}
			else if(m_status == INIT)
			{
				stopTime = time(NULL);
				m_status = GOING;
			}
		break;
	}
}

void CPlayer::onTimer(int id)
{
	int ret = 0;
	switch(id)
	{
	case IDT_TIMER2:
		if(m_mode == AUTO_MODE && m_status == GOING)
		{
			ret = autoGo();
			if(ret != 0)
			{
				m_status = OVER;
			}
		}
		if(m_status == GOING)
			showInfo();
		break;
	}
}

//默认初始值
CMaze::CMaze()
{
	m_mode = AUTO_MODE;
	m_speed = 4;
	m_size = 700;
	m_status = INIT;
	m_pos = point(20, 10);
	m_entry = point(0, 0);
	m_exit = point(0, 0);
	m_cell = 20;
	m_nx = m_size/m_cell;
	m_ny = m_nx*10/13;
	m_player = NULL;
}

CMaze::~CMaze()
{
	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}
	wlist.clear();  //释放链表内存
}

int CMaze::onInit()
{
	HDC hDC;
	SYSTEMTIME sysTime;

	this->hBrush = CreateSolidBrush(RGB(0, 0, 0));
	this->hPen = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));

	// 根据系统时间生成随机种子
	GetLocalTime(&sysTime);
	srand(sysTime.wHour*3600+sysTime.wMinute*60+sysTime.wSecond+sysTime.wMilliseconds);

	//初始化全局变量
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

	GetClientRect(hWndMain, &rCliRet);

	hDC = GetDC(hWndMain);
	h_MemDC = CreateCompatibleDC(hDC);
   
	h_MemBm = CreateCompatibleBitmap(hDC, rCliRet.right - rCliRet.left, 
	   rCliRet.bottom - rCliRet.top);

 	SelectObject(h_MemDC, hPen);
	SelectObject(h_MemDC, h_MemBm); 
	
	ReleaseDC(hWndMain, hDC);

	this->setTimer(IDT_TIMER1, 1000);
	this->initBkGnd();
	if(this->createMaze() < 0)    return -1;
	this->drawMaze();
	if(newGame() < 0)   return -1;

	return 0;
}

void CMaze::initBkGnd()
{
	int i = 0;

	FillRect(h_MemDC, &rCliRet, hBrush);

#if 0
	// 绘制网格线
	for(i = 0; i <= m_nx; i++)
	{
		MoveToEx(h_MemDC, m_pos.x + i*m_cell, m_pos.y, NULL);
		LineTo(h_MemDC, m_pos.x + i*m_cell, m_pos.y + m_ny*m_cell);
	}
	
	for(i = 0; i <= m_ny; i++)
	{
		MoveToEx(h_MemDC, m_pos.x, m_pos.y + i*m_cell, NULL);
		LineTo(h_MemDC, m_pos.x + m_nx*m_cell, m_pos.y + i*m_cell);
	}
#endif

	// 绘制边框
	MoveToEx(h_MemDC, m_pos.x - 4, m_pos.y - 4, NULL);
	LineTo(h_MemDC, m_pos.x + m_nx*m_cell + 4, m_pos.y - 4);
	LineTo(h_MemDC, m_pos.x + m_nx*m_cell + 4, m_pos.y + m_ny*m_cell + 4);
	LineTo(h_MemDC, m_pos.x - 4, m_pos.y + m_ny*m_cell + 4);
	LineTo(h_MemDC, m_pos.x - 4, m_pos.y - 4);

	this->showTime();

	InvalidateRect(hWndMain, NULL, FALSE);
}

void CMaze::dialogBox(HINSTANCE hInst, LPCTSTR IDD, DLGPROC myFunc)
{	
	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}

	DialogBox(hInst, (LPCTSTR)IDD, hWndMain, (DLGPROC)myFunc);
}

void CMaze::initDlg(HWND hDlg)
{
	SetDlgItemInt(hDlg, IDC_EDIT_CELL, m_cell, NULL);
	SetDlgItemInt(hDlg, IDC_EDIT_SPEED, m_speed, NULL);
	if(m_mode == PLAY_MODE)
	{
		CheckDlgButton(hDlg, IDC_RADIO_PLAY, TRUE);
		CheckDlgButton(hDlg, IDC_RADIO_AUTO, FALSE);
	}
	else
	{
		CheckDlgButton(hDlg, IDC_RADIO_PLAY, FALSE);
		CheckDlgButton(hDlg, IDC_RADIO_AUTO, TRUE);
	}
}

void CMaze::onDlgOk(HWND hDlg)
{
	int s_cell = 0, s_speed = 0, s_mode = 0;
	s_cell = GetDlgItemInt(hDlg, IDC_EDIT_CELL, NULL, NULL);
	s_speed = GetDlgItemInt(hDlg, IDC_EDIT_SPEED, NULL, NULL);

	if(s_cell < 7)      s_cell = 7;
	if(s_cell > 100)    s_cell = 100;
	if(s_speed <= 1)    s_speed = 1;
	if(s_speed > 10)    s_speed = 10;

	if(IsDlgButtonChecked(hDlg, IDC_RADIO_PLAY) == TRUE)
		s_mode = PLAY_MODE;
	if(IsDlgButtonChecked(hDlg, IDC_RADIO_AUTO) == TRUE)
		s_mode = AUTO_MODE;

	m_speed = s_speed;
	m_mode = s_mode;
	if(m_cell != s_cell)
	{
		m_cell = s_cell;
		m_nx = m_size/m_cell;
		m_ny = m_nx*10/13;
		if(createMaze() < 0)
			return;
	}
	initBkGnd();
	this->setTimer(IDT_TIMER2, 1000/(m_speed*m_speed*m_speed));
	drawMaze();
	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}
	m_player = new CPlayer(this);
	if(m_player == NULL)
	{
		messageBox("创建游戏失败", "错误", MB_OK);
		return;
	}
	showHelpInfo();
}

int CMaze::newGame()
{
	this->initBkGnd();
	this->setTimer(IDT_TIMER2, 1000/(m_speed*m_speed*m_speed));
	if(this->createMaze() < 0)
		return -1;
	this->drawMaze();

	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}

	m_player = new CPlayer(this);
	if(m_player == NULL)
		return -1;

	m_status = INIT;
	showHelpInfo();

	return 0;
}

void CMaze::gameOver()
{
	this->killTimer(IDT_TIMER2);
	if(m_player != NULL)
	{
		delete m_player;
		m_player = NULL;
	}
	showHelpInfo();
}

void CMaze::onPaint(HDC hdc)
{
	BitBlt(hdc,0,0, rCliRet.right - rCliRet.left,
		rCliRet.bottom - rCliRet.top, h_MemDC, 0, 0, SRCCOPY);
}

void CMaze::onTimer(int id)
{
	switch(id)
	{
	case IDT_TIMER1: //定时器IDT_TIMER1消息
		showTime();
		break;
	case IDT_TIMER2: //定时器IDT_TIMER2消息
		if(m_player != NULL)
		{ 
			if(m_player->getStatus() == GOING)
				m_player->onTimer(id);
			if(m_player->getStatus() == OVER)
				gameOver();
		}
		break;
	}
}

void CMaze::onKeyDown(unsigned short key)
{
	int status = 0;
	point p(m_pos.x + m_nx*m_cell/2 - 50, m_pos.y + m_ny*m_cell + 10);
	switch(key)
	{
	case 0x1b:             // ESC结束
		gameOver();
		break;
	case 0x25:             // left
	case 0x26:             // up
	case 0x27:             // right
	case 0x28:             // down
		if(m_mode == PLAY_MODE && m_player != NULL)
		{
			if(m_player->getStatus() == GOING)
				m_player->onKeyDown(key);
			if(m_player->getStatus() == OVER)
				gameOver();
		}
		break;
	case ' ':
		if(m_player == NULL)
		{
			if(newGame() < 0)
			{
				messageBox("创建新游戏失败", "错误", MB_OK);
				return;
			}
		}
		else
		{
			m_player->onKeyDown(key);
			showHelpInfo();
		}
		break;
	}

}

LinkList<class CWall> *CMaze::getWallList()
{
	return &wlist;
}

void CMaze::drawWall(CWall wall)
{
	RECT rc;

	if(wall.dir == UP_WALL)
	{
		rc.left= m_pos.x + wall.pos.x*m_cell;
		rc.top= m_pos.y + wall.pos.y*m_cell - 1;
		rc.right = rc.left + m_cell;
		rc.bottom = rc.top + 2;
	}
	else
	{
		rc.left= m_pos.x + wall.pos.x*m_cell - 1;
		rc.top= m_pos.y + wall.pos.y*m_cell;
		rc.right = rc.left + 2;
		rc.bottom = rc.top + m_cell;
	}

	FillRect(h_MemDC, &rc, hBrushes[6]);
	InvalidateRect(hWndMain, NULL, FALSE);
}

void CMaze::drawMaze()
{
	this->fillCell(m_entry, 0, NODIR);
	this->fillCell(m_exit, 7, NODIR);

	this->wlist.reset();
	while(wlist.current() != NULL)
	{
		drawWall(wlist.current()->data);
		wlist.next();
	}
}

int CMaze::createMaze()
{
	int i = 0, j = 0, flag = 0;
	void  **maphead = NULL, **mapbody = NULL;

	LinkList<class point> *dealist = NULL;

	// 入口
	flag = rand()%4;
	if(flag == 0)
	{
		m_entry.x = 0;
		m_entry.y = rand()%m_ny;
	}
	if(flag == 1)
	{
		m_entry.x = m_nx -1;
		m_entry.y = rand()%m_ny;
	}
	if(flag == 2)
	{
		m_entry.x = rand()%m_nx;
		m_entry.y = 0;
	}
	if(flag == 3)
	{
		m_entry.x = rand()%m_nx;
		m_entry.y = m_ny-1;
	}

	// 出口
	m_exit.x = m_nx - m_entry.x - 1;
	m_exit.y = m_ny - m_entry.y - 1;

	//map二维数组动态分配内存
	maphead = new void *[(sizeof(void *) + sizeof(class CRoom)*m_ny)*m_nx];
	if(maphead == NULL)
	{
		messageBox("分配内存失败", "错误", MB_OK);
		return -1;
	}

	mapbody = maphead + m_nx;
	for(i = 0; i < m_nx; i++)
         maphead[i] = mapbody + i*m_ny*sizeof(class CRoom)/sizeof(void *);

	map = (class CRoom **)maphead;

	// 初始化map数据
	for(i = 0; i < m_nx; i ++)
	{
		for(j = 0; j < m_ny; j ++)
		{
			map[i][j].pos = point(i, j);
			map[i][j].status = NOT_DEAL;
			map[i][j].upstatus = IS_WALL;
			map[i][j].leftstatus = IS_WALL;
		}
	}

	dealist = new LinkList<class point>();
	if(dealist == NULL)
	{
		messageBox("分配内存失败", "错误", MB_OK);
		delete[] map;
		map = NULL;
		return -1;
	}

	if(createWallList(dealist) < 0)
	{
		delete dealist;
		delete[] map;
		map = NULL;
		return -1;
	}

	delete dealist;
	delete[] map;
	map = NULL;
	return 0;
}

int CMaze::createWallList(LinkList<class point> *list)
{
	int ret = 0, i = 0, j = 0, randir = 0, srchdir = 0;
	int  icount = 0;
	point pos;
	CWall twall;

	pos = point(rand()%m_nx, rand()%m_ny);
	randir = rand()%4;

	list->clear();
	for(i = 0; i < 4; i ++)
	{					
		ret = chgRoomStatus(pos, list, (randir + i)%4, 1);
		if(ret < 0)
			return -1;
	}

	for(;;)
	{
		if(list->isEmpty() == true)
			break;

		icount ++;
		if(icount < STEP)
		{
			// 从链表中删第一个除节点
			if(list->deleteFront(&pos) < 0)
			{
				messageBox("删除节点失败[1]", "错误", MB_OK);
				return -1;
			}
		}

		// 到达搜索步长,强制停止,从正在处理的节点中随机选择一个继续搜索
		else
		{
			if(list->deleteNode(&pos, rand()%list->getSize()+1) < 0 )
			{
				messageBox("删除节点失败[2]", "错误", MB_OK);
				return -1;
			}

			icount = 0;		
		}


		// 生成随机方向
		randir = rand()%4;
		srchdir = randir%2;  // 搜索方向,0顺时针,1逆时针

		for(i = 0; i < 4; i ++)
		{			
			if(srchdir == 0)
				ret = chgRoomStatus(pos, list, (randir + i)%4, randir);			
			else					
				ret = chgRoomStatus(pos, list, (4 + randir - i)%4, randir);

			if(ret < 0)
				return -1;
		}
	}

	this->wlist.clear();  //释放墙壁链表节点内存
	// 赋值wall数据
	for(i = 0; i < m_nx; i ++)
	{
		for(j = 0; j < m_ny; j ++)
		{
			if(map[i][j].leftstatus == IS_WALL)
			{
				twall = CWall(point(i, j), LEFT_WALL);
				ret = wlist.insertTail(twall);
			}

			if(map[i][j].upstatus == IS_WALL)
			{
				twall = CWall(point(i, j), UP_WALL);
				ret = wlist.insertTail(twall);
			}
			if(i == (m_nx -1))
			{
				twall = CWall(point(i+1, j), LEFT_WALL);
				ret = wlist.insertTail(twall);
			}
			if(j == (m_ny -1))
			{
				twall = CWall(point(i, j+1), UP_WALL);
				ret = wlist.insertTail(twall);
			}
			if(ret < 0)
			{
				messageBox("分配内存失败", "错误", MB_OK);
				return -1;
			}
		}
	}

	return 0;
}

int CMaze::chgRoomStatus(point pos, LinkList<class point> *list, int dir, int depth)
{
	static point tpos;

	tpos = pos;

	map[tpos.x][tpos.y].status = HAS_DEAL;

	switch(dir)
	{
	case RIGHT:
		tpos.x = pos.x + 1;
		break;
	case DOWN:
		tpos.y = pos.y + 1;
		break;
	case LEFT:
		tpos.x = pos.x -1;
		break;
	case  UP:
		tpos.y = pos.y - 1;
		break;
	default:
		messageBox("错误探索方向", "错误", MB_OK);
		return -1;
	}
	// 出界不可以通过, 返回
	if(tpos.x < 0 || tpos.y < 0 || tpos.x >= m_nx || tpos.y >= m_ny)
	{
		return 0;
	}
	
	// 未被访问,则修改为正在访问,开辟一条路径
	if(map[tpos.x][tpos.y].status == NOT_DEAL)
	{
		// 修改处理状态
		map[tpos.x][tpos.y].status = IN_DEAL;

		if(list->insertFront(tpos) < 0)
		{
			messageBox("分配内存失败", "错误", MB_OK);
			return -1;
		}

		// 修改墙壁标志
		switch(dir)
		{
		case RIGHT:
			map[tpos.x][tpos.y].leftstatus = NO_WALL;
			break;
		case DOWN:
			map[tpos.x][tpos.y].upstatus = NO_WALL;
			break;
		case LEFT:
			map[pos.x][pos.y].leftstatus = NO_WALL;
			break;
		case UP:
			map[pos.x][pos.y].upstatus = NO_WALL;
			break;
		default:
			messageBox("错误探索方向", "错误", MB_OK);
			return -1;
		}
	}
	if(depth <= 0)
		return 0;

	if(chgRoomStatus(tpos, list, dir, depth-1) < 0)
		return -1;

	return 0;
}

void CMaze::showTime()
{
	char sCurTime[64];
	struct tm *tmtime; 
	time_t curtime;

	memset(sCurTime, 0x00, sizeof(sCurTime));

	curtime = time(NULL);
	tmtime = localtime(&curtime);

	sprintf(sCurTime, " 时间: %02d:%02d:%02d ", 
		tmtime->tm_hour, tmtime->tm_min, tmtime->tm_sec);

	displayText(point(m_cell*m_nx + 14 , m_pos.y), sCurTime);

	if(m_mode == PLAY_MODE)
	{
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 30), " 模式【计时】");
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 210), " 向上  ↑  ");
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 240), " 向下  ↓  ");
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 270), " 向左  ←  ");
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 300), " 向右  →  ");
	}

	else
		displayText(point(m_cell*m_nx + 14 , m_pos.y + 30), " 模式【演示】");
}

void CMaze::showHelpInfo()
{
	int status = 0;
	point p(m_pos.x + m_nx*m_cell/2 - 80, m_pos.y + m_ny*m_cell + 10);

	if(m_player == NULL)
	{
		displayText(p, "游戏结束,按空格重新开始");
		return;
	}
	status = m_player->getStatus();
	switch(status)
	{
	case OVER:
		displayText(p, "游戏结束,按空格重新开始");
		break;
	case INIT:
	case STOP:
		displayText(p, "按空格开始游戏,ESC结束游戏");
		break;
	case GOING:
		displayText(p, "按空格暂停游戏,ESC结束游戏");
		break;
	}
}
