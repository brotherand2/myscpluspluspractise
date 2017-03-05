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
#ifndef UNICODE //���û�ж���UNICODE ,��tstring�滻Ϊstring,�����滻Ϊwstring
using  tstring = string;
#else
using  tstring = wstring;
#endif
static bool bFullScreen = false;//�Ƿ�ȫ��
static RECT windowRect;//���ڵ����꣬������ȫ��ʱ����ԭ����
static int cxScreen, cyScreen;//��Ļ��ȡ��߶�
static HWND hDestop;//������
static HBITMAP hBitmap;//λͼ���
bool startBoot = true;
#define ID_HOTKEYCLIP 1
#define ID_HOTKEYDELETE 2

# define ID_FULL 2
TCHAR tip[5][MAX_PATH] =
{
	TEXT("ɵ�ƣ����ʲô������ˣ���ʲô�㣬��ʲô�õ��"),
	TEXT("�Ʊƣ��㻹�ڵ㣬��֪����˵�������𣬶��������ˣ��㻹��"),
	TEXT("�走�����ٵ�Ҳû�ã���Ļ��Ҫ��ռ�������õ��Ը����޷���������AƬ�����ף����������ٿص��ԣ�����ҵ�"),
	TEXT("����������ˣ����ѽ�����б����ؿ���������Ҳû�У�������������"),
	TEXT("�����ٵ���꣬�Ҿ͸�ʽ��Ӳ�̣����Ų��ţ�������˵���ⲻ����ĵ��ԣ�������")
};
int bit[5] = { IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP4, IDB_BITMAP5 };
HBITMAP Bitmap[5];
void GetDestopBK(HWND hDestop, HBITMAP &hBitmap, int cxScreen, int cyScreen)//��ô��ڱ�����ѡ��λͼ
{
	HDC hdcMem = CreateCompatibleDC(0);//�������Ļ���ݵĻ���
	HDC  hdcScr = GetDCEx(hDestop, 0,DCX_LOCKWINDOWUPDATE);//�����Ļ�Ļ���,��ʹ��Ļ��סҲ��ˢ��
	hBitmap = CreateCompatibleBitmap(hdcScr, cxScreen,cyScreen);//��������Ļ��С���ݵ�λͼ
	SelectObject(hdcMem, hBitmap);//��λͼѡ�뻭��
	BitBlt(hdcMem, 0, 0, cxScreen, cyScreen, hdcScr, 0, 0, SRCCOPY);//����Ļ��λͼ�����������ϵ�λͼ
	DeleteDC(hdcMem);
	ReleaseDC(hDestop, hdcScr);
}
void ShowFullScreen(HWND hwnd, int cxScreen, int cyScreen)//�ô���ȫ��
{
	SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);//���ô�����ʽΪ����ʽ���ڣ�����ȥ��ϵͳ�˵������������߿�ȣ�Ҳ����WS_BORDER��ʽ
	SetMenu(hwnd, 0);//ȥ���˵�
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, cxScreen, cyScreen, SWP_SHOWWINDOW);//�ô�����ʾȫ�����ö�
	bFullScreen = true;//��ȫ��
}
void RecoveryWindow(HWND hwnd, RECT windowRect)//�ָ�����ԭ���Ĵ�Сλ��
{
	SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);//�ָ�������ʽ
	SetWindowPos(hwnd, HWND_NOTOPMOST,44,44,444,444, SWP_SHOWWINDOW);//�ָ�ԭ��λ��
	bFullScreen = false;//����ȫ��
}
void SetStartingUpBoot()//���ÿ�������
{
	HKEY m_regkey;//ע�����
	TCHAR filename[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);//���س����ȫ·��
	TCHAR lpRun[] = TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");//�Ӽ�·��
	long iRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &m_regkey);//��������ע����
	if (iRet == ERROR_SUCCESS)//�򿪳ɹ�
	{
		if (startBoot)
		RegSetValueEx(m_regkey, TEXT("ȫ��ZENG"), 0, REG_SZ, (const unsigned char *)filename, MAX_PATH);//����ǰ����·����ӵ�ע�����������
		else
			RegDeleteValue(m_regkey, TEXT("ȫ��ZENG"));//ɾ��ע���
	}
	RegCloseKey(m_regkey);//�ر�ע���
}
int _stdcall DlgProc(HWND hwnd, unsigned int UMsg, unsigned int wParam, long lParam)
{
	HDC hdc;//����
	HDC hdcMem;
	PAINTSTRUCT ps;//���ʽṹ������������Ϣ
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
		hdc = BeginPaint(hwnd, &ps);//��ô��ڻ���
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, Bitmap[i]);
		BitBlt(hdc, 0, 0,bm.bmWidth,bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);//�ͷŻ�����Դ
		break;
	case WM_TIMER:
		KillTimer(hwnd, 1);
		EndDialog(hwnd,0);
		break;
	}
	return false;
}
long _stdcall WndProc(HWND hwnd, unsigned int UMsg, unsigned int wParam, long lParam)//���ڹ���
{
	PAINTSTRUCT ps;//���ʽṹ������������Ϣ
	HDC hdc;//����
	static int cxClient, cyClient;//�ͻ�����ȡ��߶�
	static int cxChar, cyChar;//��ĸ��ȡ��߶�
	int wmId, wmEvent;//�ؼ�ID,�ؼ�֪ͨ�룬�����
	static HINSTANCE hInst;//����ʵ�����
	static HDC hdcMem;//�ڴ滭��
	NOTIFYICONDATA nid;
	switch (UMsg)
	{
	case WM_CREATE://���ڱ�����
	   	hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);//��ô���ʵ�����
		cxChar = LOWORD(GetDialogBaseUnits());//�õ��Ի�������ĸ�Ŀ��
		cyChar = HIWORD(GetDialogBaseUnits());//�õ��Ի�������ĸ�ĸ߶�
		cxScreen = GetSystemMetrics(SM_CXSCREEN);//��Ļ��ȡ��߶�
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		for (int i = 0; i < 5; i++)
			Bitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(bit[i]));
		srand(time(0));
		SetTimer(hwnd, 2, 2000, 0);
		SetStartingUpBoot();
		break;
	case WM_SIZE://���ڴ�С�ı�ʱ
		cxClient = LOWORD(lParam);//���¿ͻ����Ĵ�С
		cyClient = HIWORD(lParam);
		break;
	case WM_TIMER:
		ShowFullScreen(hwnd, cxScreen, cyScreen);//ȫ����ʾ
		InvalidateRect(hwnd, 0, true);//�ڴ��ڻ������汳��
		break;
	case WM_COMMAND://���Ӵ��ڡ��˵��ϲ���ʱ��������
		wmId = LOWORD(wParam);//�ؼ�ID
		wmEvent = HIWORD(wParam);//�ؼ�֪ͨ�룬�����
		switch (wmId)
		{
		case ID_HOTKEYCLIP:
			SetStartingUpBoot();
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			break;
		case ID_FULL:
			GetDestopBK(hDestop, hBitmap, cxScreen, cyScreen);//�õ�����λͼ
			ShowFullScreen(hwnd, cxScreen, cyScreen);//ȫ����ʾ
			InvalidateRect(hwnd, 0, true);//�ڴ��ڻ������汳��
			break;
		}
		break;
	case WM_PAINT://������ʧЧ�������ػ�
		hdc = BeginPaint(hwnd, &ps);//��ô��ڻ���
		if (hBitmap)//λͼ����
		{
			hdcMem = CreateCompatibleDC(0);//�������Ļ���ݵĻ���
			BITMAP bm;//λͼ�ṹ
			GetObject(hBitmap, sizeof(BITMAP), &bm);//���λͼ��Ϣ
			SelectObject(hdcMem,hBitmap);//��λͼѡ�뻭��
			BitBlt(hdc, 0, 0, cxScreen,cyScreen, hdcMem, 0, 0, SRCCOPY);//�ڴ�������ʾ��ͼ
			DeleteObject(hdcMem);
		}
		EndPaint(hwnd, &ps);//�ͷŻ�����Դ
		break;
	case WM_SYSKEYDOWN:
		if (wParam == VK_F4)//����ALT+F4�رռ�
			return 0;
		break;
	case WM_LBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
		break;
	case WM_CLOSE://���ڹر�
		return 0;
	case WM_DESTROY://��������ʱ
		PostQuitMessage(0);//�׳�һ������ֵΪ0�˳���Ϣ
		break;
	}
	return DefWindowProc(hwnd, UMsg, wParam, lParam);//��Ĭ�ϵĴ��ڹ��̴���������Ϣ����Щ��������
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *  szCmdCommand, int nCmdShow)
{
	WNDCLASS wndclass;//������
	wndclass.cbClsExtra = 0;//Ϊ�����Ķ���ռ䣬���Ա���һЩ��ַ������
	wndclass.cbWndExtra = 0;//Ϊ���ڷ���Ķ���ռ䣬���Ա���һЩ��ַ������
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//������ˢ
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);//�����
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));//ͼ��
	wndclass.hInstance = hInstance;//ʵ�������������PID��һ���������������������ϵͳ�����ҵ����̵ĵ�ַ
	wndclass.lpfnWndProc = WndProc;//���ڹ���
	wndclass.lpszClassName = TEXT("zeng");//����
	wndclass.lpszMenuName = nullptr;//�˵�
	wndclass.style = CS_VREDRAW | CS_HREDRAW;//��Щ�ı��Ҫ�ػ�������ˮƽ�ʹ�ֱ�ı���ػ�
	if (!RegisterClass(&wndclass))//ע�ᴰ����
	{
		MessageBox(nullptr, TEXT("register failed"), TEXT("error"), MB_ICONINFORMATION);
		return 0;
	}
	HWND hwnd = CreateWindow(TEXT("zeng"), TEXT(""),WS_POPUP,
		-50,-50,0,0,
		nullptr, nullptr, hInstance, nullptr);//��������
	if (!hwnd)
	{
		MessageBox(nullptr, TEXT("create window failed"), TEXT("error"), MB_ICONASTERISK);
	}
	RegisterHotKey(0, ID_HOTKEYCLIP, MOD_CONTROL | MOD_ALT|MOD_SHIFT, 'E');//��ͼ�ȼ�
	RegisterHotKey(0, ID_HOTKEYDELETE, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 'D');//��ͼ�ȼ�
	ShowWindow(hwnd, nCmdShow);//��ʾ����
	UpdateWindow(hwnd);//�����ػ�
	SendMessage(hwnd, WM_COMMAND, ID_FULL, 0);
	MSG msg;//��Ϣ�ṹ
	while (GetMessage(&msg, nullptr, 0, 0))//����Ϣ���л�ȡ��Ϣ
	{
		if (msg.message == WM_HOTKEY)//�����ϵͳ�ȼ�
		{
			if (msg.wParam==ID_HOTKEYCLIP)
			    SendMessage(hwnd, WM_COMMAND, ID_HOTKEYCLIP, 0);
			if (msg.wParam == ID_HOTKEYDELETE)
				startBoot = false;
		}
		TranslateMessage(&msg);//��һЩ������Ϣת�����ַ���Ϣ���ڰ�����Ϣ����
		DispatchMessage(&msg);//�ַ���Ϣ�������ô��ڹ��̽��д�����Ϣ
	}
}