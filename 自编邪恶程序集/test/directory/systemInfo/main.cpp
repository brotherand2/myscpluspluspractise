#include<Windows.h>
#include<iostream>
//#include<string>
#pragma   warning(disable: 4996)
using namespace std;
void Edit(WORD edition)
{
	if(edition& VER_SUITE_BACKOFFICE)
		cout << " office �����װ"; 
	if (edition&VER_SUITE_BLADE)
		cout << "win2003��ҳ�氲װ";
	if (edition&VER_SUITE_PERSONAL)
			cout << "��ͥ��";
	if (edition&VER_SUITE_ENTERPRISE)
		cout << "��ҵ��";
	if (edition&VER_SUITE_COMPUTE_SERVER)
		cout << "Cluster Edition";
	if (edition&VER_SUITE_DATACENTER)

	cout << "Datacenter Edition";

}
void ShowVersionInfo()
{
	OSVERSIONINFOEX ovi;
	/*
	DWORD dwOSVersionInfoSize;       //��ʹ��GetVersionEx֮ǰҪ���˳�ʼ��Ϊ�ṹ�Ĵ�С
	DWORD dwMajorVersion;               //ϵͳ���汾��
	DWORD dwMinorVersion;               //ϵͳ�ΰ汾��
	DWORD dwBuildNumber;               //ϵͳ������
	DWORD dwPlatformId;                  //ϵͳ֧�ֵ�ƽ̨(�����1)
	TCHAR szCSDVersion[128];          //ϵͳ������������
	WORD wServicePackMajor;            //ϵͳ�����������汾
	WORD wServicePackMinor;            //ϵͳ�������Ĵΰ汾
	WORD wSuiteMask;                      //��ʶϵͳ�ϵĳ�����(�����2)
	BYTE wProductType;                    //��ʶϵͳ����(�����3)
	BYTE wReserved;                         //����,δʹ��	*/
	ovi.dwOSVersionInfoSize = sizeof(ovi);
	if (!GetVersionEx((OSVERSIONINFO*)&ovi))
	{
		cout << "��ȡϵͳ�汾��Ϣʧ��";
		return;
	}
	switch (ovi.dwMajorVersion)//���汾��
	{
	case 5:
		switch (ovi.dwMinorVersion)//�ΰ汾��
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
			if (ovi.wProductType == VER_NT_WORKSTATION)//���������ϵͳ
				cout << "Windows Vista \n";
			else
				cout << " Windows Server 2008\n";
			Edit(ovi.wSuiteMask);

			break;
		case 1:
			if (ovi.wProductType == VER_NT_WORKSTATION)//���������ϵͳ
				cout << " Windows 7\n";
			else
			cout << "Windows Server 2008 R2 " << endl;
			Edit(ovi.wSuiteMask);

			break;
		case  2:
			if (ovi.wProductType == VER_NT_WORKSTATION)//���������ϵͳ
				cout << " Windows 8\n";
			else
				cout <<"Windows Server 2012 \n";
			Edit(ovi.wSuiteMask);
			break;
		case 3:
			if (ovi.wProductType == VER_NT_WORKSTATION)//���������ϵͳ
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
		cout << "Windows NT4.0����������Windows 2000�İ汾\n";
	}
	cout << "�汾��:" << ovi.dwMajorVersion << "." << ovi.dwMinorVersion << ",������:" <<
		ovi.dwBuildNumber << " ƽ̨: " << ovi.szCSDVersion << endl;
}
void ShowSystemInfo()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	cout << "\n�ڴ��ҳ��С:" << si.dwPageSize << endl;
	cout << "�ڴ��ַ��ʼ:0X" << si.lpMinimumApplicationAddress << endl;
	cout << "�ڴ��ַ����:0X" << si.lpMaximumApplicationAddress << endl;
	cout << "������������" << si.dwNumberOfProcessors << endl;
	cout << "����������:" ;
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
	cout << "�������ܹ�:";
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
	cout << "ϵͳĿ¼:" << szBuffer << endl;
	GetWindowsDirectory(szBuffer, MAX_PATH);
	cout << "WindowsĿ¼:" << szBuffer << endl;
	unsigned long len = MAX_COMPUTERNAME_LENGTH + 1;
	GetUserName(szBuffer, &len);
	cout << "�û���:" << szBuffer << endl;
	GetComputerName(szBuffer, &len);
	cout << "��������" << szBuffer << endl;
	cin.get();
}