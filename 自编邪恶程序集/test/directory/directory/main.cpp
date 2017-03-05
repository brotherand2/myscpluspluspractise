#include<stdio.h>
#include<locale.h>
#include<tchar.h>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//#include<windows.h>
void ShowFileTime(FILETIME &ft)
{
	FILETIME temp;
	FileTimeToLocalFileTime(&ft, &temp);
	SYSTEMTIME st;
	FileTimeToSystemTime(&temp, &st);
	cout << st.wYear << "年" << st.wMonth << "月" << st.wDay << "日," << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
}
typedef struct
{
	unsigned int G, M, K, B;
}capacity;
void calculateCapacity(capacity &c,DWORD64 size)
{
	c.G = size / (1024 * 1024 * 1024);
	size %= (1024 * 1024 * 1024);
	c.M = size / ( 1024 * 1024);
	size %= (1024 * 1024);
	c.K = size / 1024;
	size %= 1024;
	c.B = size;
}
int main()
{
	//setlocale(LC_ALL, "chs");
	//char ch = '国';
	//printf("hello :%c\n", ch);
	//wchar_t name = L'国';
	//wprintf(L"wchar_t :%lc", name);
	//TCHAR t[] = _T("中国");
	//_tprintf(_T("%s\n"), t);
	TCHAR path[MAX_PATH];
	unsigned long len = GetSystemDirectory(path, MAX_PATH);
	cout << TEXT("length=") << len << TEXT(",  path=") << path << endl;
	 len = GetCurrentDirectory(MAX_PATH, path);
	cout << TEXT("length=") << len << TEXT(",  path=") << path << endl;
	HANDLE file;
	////file = CreateFile(TEXT("zeng.txt"), GENERIC_ALL, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM,nullptr);
	//file = CreateFile(TEXT("1zeng.txt"), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_DIRECTORY, nullptr);
	file = CreateFile(TEXT("zeng.txt"), GENERIC_ALL, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM, nullptr);

	if (file != INVALID_HANDLE_VALUE)
	{
		if (!WriteFile(file, path, lstrlen(path), &len, nullptr))
		{
			cout << TEXT("you can write")<<			GetLastError();
		}
		else
		{
			cout << TEXT("length=") << len << endl;
		}
	}
	CloseHandle(file);
	WIN32_FILE_ATTRIBUTE_DATA attri;
	GetFileAttributesEx(TEXT("zeng"), GetFileExInfoStandard, &attri);
	cout << TEXT("创建时间");
	ShowFileTime(attri.ftCreationTime);
	cout << TEXT("访问时间");
	ShowFileTime(attri.ftLastAccessTime);
	cout << TEXT("修改时间");
	ShowFileTime(attri.ftLastWriteTime);
	TCHAR driverString[MAX_PATH];
	//ZeroMemory(driverString, MAX_PATH);
	GetLogicalDriveStrings(MAX_PATH - 1, driverString);
	TCHAR *temp = driverString;
	while (*temp)
	{
		cout << temp << endl;
		while (*temp++)
			;
	}
	HANDLE drive = FindFirstVolume(driverString, MAX_PATH);
	if (drive != INVALID_HANDLE_VALUE)
	{
		do
		{

			cout << driverString<<endl;
		} while (FindNextVolume(drive, driverString,MAX_PATH));

	}
	FindVolumeClose(drive);
	//PULARGE_INTEGER total, free;
	DWORD64 total, free,free1;
	int result = GetDiskFreeSpaceEx(TEXT("C:"), (PULARGE_INTEGER)&free, (PULARGE_INTEGER)&total, (PULARGE_INTEGER) &free1);
	if (result)
	{
		cout << TEXT("TOTAL :") << total << TEXT(",free:") << free << endl;
		capacity c_total, c_free;
		calculateCapacity(c_total, total);
		calculateCapacity(c_free,free);

		cout << "total:" << c_total.G << "Gb," << c_total.M << "Mb," << c_total.K << "Kb," << c_total.B << "byte" << endl;
		cout << "free:" << c_free.G << "Gb," << c_free.M << "Mb," << c_free.K << "Kb," << c_free.B << "byte" << endl;

	}
	//fstream fs(TEXT("main.cpp"));
	//string str;
	//if (fs.is_open())
	//{
	//	while(getline(fs, str))
	//	cout << str << endl;
	//}
	//fs.close();
	//HANDLE hFile;
	//unsigned long size;
	//hFile = CreateFile(TEXT("main.cpp"), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	//TCHAR szBuffer[25];
	//ZeroMemory(szBuffer, 25);
	//while(ReadFile(hFile, szBuffer, 24, &size, nullptr)&&size>0)
	//cout << szBuffer ;
	//CloseHandle(hFile);
	//MoveFile(TEXT("1zeng.txt"), TEXT("yonghua.cpp"));
	//DeleteFile(TEXT("2zeng.txt"));
	//CopyFile(TEXT("main.cpp"), TEXT("copy.txt"),true);
		//perror("main.cpp not exist\n");
	if (!CreateDirectory(TEXT("f:\\zeng"), nullptr))
		cout << TEXT("create failed") << endl;
	GetCurrentDirectory(MAX_PATH, path);
	cout << TEXT("path:") << path << endl;
	SetCurrentDirectory(TEXT("e:\\"));
	GetCurrentDirectory(MAX_PATH, path);
	cout << TEXT("******") << path << endl;
	if(!CreateDirectory(TEXT("haha.java"), nullptr))
		cout << TEXT("create failed") << endl;
	if (!GetModuleFileName(nullptr, path, MAX_PATH))
		cout << TEXT("get modual name failed");
	else
		cout << TEXT("modual name:") << path << endl;
	HMODULE hKernel32;
	hKernel32 = LoadLibrary(TEXT("kernel32.dll"));
	if (!GetModuleFileName(hKernel32, path, MAX_PATH))
		cout << TEXT("get modual name failed");
	else
		cout << TEXT("modual name:") << path << endl;

	cin.get();
	return 0;
}