#include<Windows.h>
#include<iostream>
//#include<string>
#pragma   warning(disable: 4996)
using namespace std;
void Edit(WORD edition)
{
	if(edition& VER_SUITE_BACKOFFICE)
		cout << " office 组件安装"; 
	if (edition&VER_SUITE_BLADE)
		cout << "win2003网页版安装";
	if (edition&VER_SUITE_PERSONAL)
			cout << "家庭版";
	if (edition&VER_SUITE_ENTERPRISE)
		cout << "企业版";
	if (edition&VER_SUITE_COMPUTE_SERVER)
		cout << "Cluster Edition";
	if (edition&VER_SUITE_DATACENTER)

	cout << "Datacenter Edition";

}
void ShowVersionInfo()
{
	OSVERSIONINFOEX ovi;
	/*
	DWORD dwOSVersionInfoSize;       //在使用GetVersionEx之前要将此初始化为结构的大小
	DWORD dwMajorVersion;               //系统主版本号
	DWORD dwMinorVersion;               //系统次版本号
	DWORD dwBuildNumber;               //系统构建号
	DWORD dwPlatformId;                  //系统支持的平台(详见附1)
	TCHAR szCSDVersion[128];          //系统补丁包的名称
	WORD wServicePackMajor;            //系统补丁包的主版本
	WORD wServicePackMinor;            //系统补丁包的次版本
	WORD wSuiteMask;                      //标识系统上的程序组(详见附2)
	BYTE wProductType;                    //标识系统类型(详见附3)
	BYTE wReserved;                         //保留,未使用	*/
	ovi.dwOSVersionInfoSize = sizeof(ovi);
	if (!GetVersionEx((OSVERSIONINFO*)&ovi))
	{
		cout << "获取系统版本信息失败";
		return;
	}
	switch (ovi.dwMajorVersion)//主版本号
	{
	case 5:
		switch (ovi.dwMinorVersion)//次版本号
		{
		case 0:
			cout << "Window Server 2000\n";
			Edit(ovi.wSuiteMask);
			break;
		case 1:
			cout << "Windows Xp\n";
			Edit(ovi.wSuiteMask);
			break;
		case 2:
			cout << "Windows Server 2003\n ";
			Edit(ovi.wSuiteMask);

			break;
		}
		break;
	case 6:
		switch (ovi.dwMinorVersion)
		{
		case 0:
			if (ovi.wProductType == VER_NT_WORKSTATION)//如果是桌面系统
				cout << "Windows Vista \n";
			else
				cout << " Windows Server 2008\n";
			Edit(ovi.wSuiteMask);

			break;
		case 1:
			if (ovi.wProductType == VER_NT_WORKSTATION)//如果是桌面系统
				cout << " Windows 7\n";
			else
			cout << "Windows Server 2008 R2 " << endl;
			Edit(ovi.wSuiteMask);

			break;
		case  2:
			if (ovi.wProductType == VER_NT_WORKSTATION)//如果是桌面系统
				cout << " Windows 8\n";
			else
				cout <<"Windows Server 2012 \n";
			Edit(ovi.wSuiteMask);
			break;
		case 3:
			if (ovi.wProductType == VER_NT_WORKSTATION)//如果是桌面系统
				cout << " Windows 8.1\n";
			else
				cout << "Windows Server 2012 R2\n";
			Edit(ovi.wSuiteMask);

			break;
		}
		break;
	case 10:
		cout << "Windows 10\n";
		Edit(ovi.wSuiteMask);

		break;
	default :
		cout << "Windows NT4.0或其它低于Windows 2000的版本\n";
	}
	cout << "版本号:" << ovi.dwMajorVersion << "." << ovi.dwMinorVersion << ",构建号:" <<
		ovi.dwBuildNumber << " 平台: " << ovi.szCSDVersion << endl;
}
void ShowSystemInfo()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	cout << "\n内存分页大小:" << si.dwPageSize << endl;
	cout << "内存地址开始:0X" << si.lpMinimumApplicationAddress << endl;
	cout << "内存地址结束:0X" << si.lpMaximumApplicationAddress << endl;
	cout << "处理器个数：" << si.dwNumberOfProcessors << endl;
	cout << "处理器类型:" ;
	switch (si.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
		cout << "386" << endl;
		break;
	case PROCESSOR_INTEL_486:
		cout << "486" << endl;
		break;
	case PROCESSOR_INTEL_PENTIUM:
		cout << "pentium" << endl;
		break;
	}
	cout << "处理器架构:";
	switch (si.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		cout << "64 bit amd" << endl;
	case PROCESSOR_ARCHITECTURE_INTEL:
		cout << "intel" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		cout << "intel 64 bit" << endl;
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		cout << "unknown" << endl;
		break;
	}
}
int main()
{
	ShowVersionInfo();
	ShowSystemInfo();
	TCHAR szBuffer[MAX_PATH];
	GetSystemDirectory(szBuffer, MAX_PATH);
	cout << "系统目录:" << szBuffer << endl;
	GetWindowsDirectory(szBuffer, MAX_PATH);
	cout << "Windows目录:" << szBuffer << endl;
	unsigned long len = MAX_COMPUTERNAME_LENGTH + 1;
	GetUserName(szBuffer, &len);
	cout << "用户名:" << szBuffer << endl;
	GetComputerName(szBuffer, &len);
	cout << "电脑名：" << szBuffer << endl;
	cin.get();
}