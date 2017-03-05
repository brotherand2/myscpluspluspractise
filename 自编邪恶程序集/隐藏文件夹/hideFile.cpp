# include<iostream>
# include<string>
# include<windows.h>
# include<fstream>
std::string directory[26] = { "a:", "b:", "c:", "d:", "e:", "f:", "g:",
"h:", "i:", "j:", "k:", "l:", "m:", "n:", "o:", "p:", "q:","r:", "s:", 
"t:", "u:", "v:", "w:", "x:", "y:", "z:" };//磁盘组
std::string path[100];//当前磁盘的所有文件名
std::string type = "\\*.*";//要查找的文件类型，所有文件
void hideFile(int disk )//隐藏所有文件、目录;
{//disk为哪个盘
	using namespace std;
	/*
	typedef struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes; //文件属性
	FILETIME ftCreationTime; // 文件创建时间
	FILETIME ftLastAccessTime; // 文件最后一次访问时间
	FILETIME ftLastWriteTime; // 文件最后一次修改时间
	DWORD nFileSizeHigh; // 文件长度高32位
	DWORD nFileSizeLow; // 文件长度低32位
	DWORD dwReserved0; // 系统保留
	DWORD dwReserved1; // 系统保留
	_Field_z_ CHAR   cFileName[ MAX_PATH ];// 长文件名

	_Field_z_ CHAR   cAlternateFileName[ 14 ]; // 8.3格式文件名
	#ifdef _MAC
	DWORD dwFileType;
	DWORD dwCreatorType;
	WORD  wFinderFlags;
	#endif
	} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
	*/
	WIN32_FIND_DATA fd;//fd文件信息结构
	HANDLE handle;//handle文件名柄
	int count = 0;//发现的文件数
	string  find=root + type;

	handle = FindFirstFile((directory[disk] + type).c_str(), &fd);//查找第一个文件
	if (handle == INVALID_HANDLE_VALUE)//找不到文件
	{
		fstream fout;
		fout.open("file not found.txt", ios::app);
		fout << "the file directory " << find << " is fault\n";
		fout.close();
	}
	else
	{

		do
		{
			if (fd.cFileName[0] == '.')//win32下一般会有三种文件夹，一种是“.”指的是当前文件夹，一种是“..”指的是上层文件夹，最后一种就是普通的下层文件夹用文件夹名显示，cd .是本目录，cd ..是上级目录
				continue;//所以为了不回到上级目录和在原目录打转，过滤.和..这二个目录
			path[count]=fd.cFileName;//将找到的文件名保存
			count++;			
		} while (FindNextFile(handle, &fd));//FindFirstFile函数时指定的一个文件名查找下一个文件
        string attrib="attrib +s +r +h /s /d ";
        /*for(int i=0;i<count;i++)
		{
		  cout << "the  file is " << path[i] << endl;
		  if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
		  system((attrib + "\\\""+path[i] + "\"\\*.* /s /d").c_str());//隐藏当前目录中子目录的所有文件
		 system((attrib+"\\\""+path[i]+"\"").c_str());//隐藏主目录文件
		}*/
		cout<<directory[disk]<<endl;

		system((attrib+directory[disk]+type).c_str());
       	system("pause");
		attrib = "attrib -s -r -h /s /d " ;
     /*
       for( i=0;i<count;i++)
		{
  	    cout << "recover the  file is " << path[i] << endl;
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
		  system((attrib + "\\\""+path[i] + "\"\\*.* /s /d").c_str());//隐藏当前目录中子目录的所有文件
		  system((attrib+"\\\""+path[i]+"\"").c_str());//隐藏主目录文件
		}
		*/
		system((attrib+directory[disk]+type).c_str());
       	system("pause");
		FindClose(handle);//关闭文件句柄
	}
}
int main()
{
	int i;
	for(i=0;i<26;i++)
		hideFile(i);
    return 0;
}
