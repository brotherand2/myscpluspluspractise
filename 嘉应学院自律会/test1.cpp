# include<stdio.h>
# include<malloc.h>
# include<windows.h>
#include <stdio.h>
#include <time.h>
# include<string.h>
# include<string>
# include<iostream>
# include<fstream>
# include<vector>
# include<algorithm>
std::vector<WIN32_FIND_DATA> vect;
std::string root = "E:\\壁纸\\SogouWP\\Local\\WallPaper";//根目录
std::string type = "\\*.*";//要查找的文件类型，所有文件
std::string directory[25] = { "a:", "b:", "d:", "e:", "f:", "g:",
"h:", "i:", "j:", "k:", "l:", "m:", "n:", "o:", "p:", "q:","r:", "s:", 
"t:", "u:", "v:", "w:", "x:", "y:", "z:" };
bool level[1001] = { 0 };
class point
{
public:
	int x = 2;
	int y = 2;
	int z;
	static const int x1 = 2;
	static int y1;
	point()
	{
		std::cout << "x=" << x << "y=" << y << std::endl;
	};
};
//point b;
//void showFile(WIN32_FIND_DATA &);
//bool myFindNextFile(HANDLE &handle, WIN32_WIN32_FIND_DATA &fdFIND_DATA &fd, int layer);//找到第几次目录

void showFileAttribute(WIN32_FIND_DATA &fd)//显示文件属性
{
	using  std::cout;
	using std::endl;
	using namespace std;
	ofstream ccout;
	ccout.open("attribute.txt", ios::app);
	if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || fd.dwFileAttributes == 17)
		ccout << "目录";
	ccout << "文件名字:" << fd.cFileName << endl <<
		" 8.3格式文件名:" << fd.cAlternateFileName << endl <<
		"文件属性:" << fd.dwFileAttributes << endl <<
		"系统保留0:" << fd.dwReserved0 << endl <<
		"系统保留1:" << fd.dwReserved1 << endl <<
		"文件创建时间:" << fd.ftCreationTime.dwHighDateTime << "," << fd.ftCreationTime.dwLowDateTime << endl <<
		"文件最后一次访问时间:" << fd.ftLastAccessTime.dwHighDateTime << "," << fd.ftLastAccessTime.dwLowDateTime << endl <<
		"文件最后一次写入时间:" << fd.ftLastWriteTime.dwHighDateTime << "," << fd.ftLastWriteTime.dwLowDateTime << endl <<
		"文件大小:" << fd.nFileSizeHigh << "," << fd.nFileSizeLow << endl << endl;
}
void writeTree(WIN32_FIND_DATA &fd, int layer,int disk)//显示树状图
{
	int i;
	using namespace std;
	ofstream os;
	string file = directory[disk][0] + string("treeNotFile.txt");
	os.open(file, ios::app);
	for (i = 1; i < layer; i++)
	{
		if (level[i])
			os << "│  ";
		else
			os << "    ";

	}
	if (level[i])
		os << "├─" << fd.cFileName << std::endl;
	else
		os << "└─" << fd.cFileName << std::endl;
}
void showTree(WIN32_FIND_DATA &fd, int layer)//显示树状图
{
	int i;
	for (i = 1; i < layer; i++)
	{
		if (level[i])
			std::cout << "│  ";
		else
			std::cout << "    ";

	}
	if (level[i])
		std::cout << "├─" << fd.cFileName << std::endl;
	else
		std::cout << "└─" << fd.cFileName << std::endl;

}

int countCurrentDirectoryFile(std::string CurrentPath, bool showFile)//当前目录的文件数量，不包括.和..目录
{//showFile为true则计算文件、目录，为false则只计算目录
	using namespace std;
	HANDLE handle;//handle文件名柄
	WIN32_FIND_DATA fd;//fd文件信息结构
	string test, find;
	int count = 0;
	find = CurrentPath + type;
	//std::cout << "find=" << find << endl;
	handle = FindFirstFile((CurrentPath + type).c_str(), &fd);
	do
	{
		if (fd.cFileName[0] == '.')//win32下一般会有三种文件夹，一种是“.”指的是当前文件夹，一种是“..”指的是上层文件夹，最后一种就是普通的下层文件夹用文件夹名显示，cd .是本目录，cd ..是上级目录
			continue;//所以为了不回到上级目录和在原目录打转，过滤.和..这二个目录
		if (showFile)
		  count++;
		else
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
				count++;
		}
	} while (FindNextFile(handle, &fd));//FindFirstFile函数时指定的一个文件名查找下一个文件
	FindClose(handle);
	return count;
}
void FindAllFile(  int layer,std::string CurrentPath,bool showFile,int disk )//查找所有文件、目录;
{//layer文件目录层次，CurrentPath当前路径,showFile为true则显示文件、目录，为false则只显示目录
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
	string test,find;
	int count = 0;
	int la;
	find = CurrentPath + type;
	//std::cout << "find=" << find << endl;
	handle = FindFirstFile((CurrentPath + type).c_str(), &fd);
	if (handle == INVALID_HANDLE_VALUE)
	{
		fstream fout;
		fout.open("file not found.txt", ios::app);
		fout << "the file directory " << find << " is fault\n";
		fout.close();
	}
	else
	{
		//showFile(fd);
		//showTree(fd, layer);
		level[layer] = 1;
		la = layer;
		do
		{
			if (fd.cFileName[0] == '.')//win32下一般会有三种文件夹，一种是“.”指的是当前文件夹，一种是“..”指的是上层文件夹，最后一种就是普通的下层文件夹用文件夹名显示，cd .是本目录，cd ..是上级目录
				continue;//所以为了不回到上级目录和在原目录打转，过滤.和..这二个目录
			if (showFile)
			count++;
			else
			{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
					count++;
			}
			if (count == countCurrentDirectoryFile(CurrentPath,showFile))
				level[layer] = 0;
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
			{

				//showTree(fd, layer);
				//writeTree(fd, layer,disk);
				test = string(fd.cFileName);
				//cout << "test=" << test << endl;
				//FindAllFile( layer + 1,CurrentPath+"\\"+string(fd.cFileName),showFile,disk);

			}
			else
			{
				if (showFile)
				{
					//writeTree(fd, layer,disk);
					//showTree(fd,layer);
				}
			}
			//showFileAttribute(fd);
			vect.push_back(fd);
			//cout << "the  file is " << fd.cFileName << endl;
			//showFile(fd);
		} while (FindNextFile(handle, &fd));//FindFirstFile函数时指定的一个文件名查找下一个文件


		FindClose(handle);
	}
}
bool sortSize(WIN32_FIND_DATA &fd1, WIN32_FIND_DATA &fd2)
{
		if (fd1.nFileSizeLow < fd2.nFileSizeLow)
			return false;
}
int main()
{
	int i=0,j;
	FILE *fp;
	//for (i = 0; i < 25;i++)
	//FindAllFile(1,directory[i],false,i);//从根目录，即第1层开始找
	//FindAllFile(1, directory[i], true, i);//从根目录，即第1层开始找
	FindAllFile(1, root, true, i);//从根目录，即第1层开始找
	using namespace std;
	int count = 0,repeat=0;
	vector<WIN32_FIND_DATA>::iterator iter;

	sort(vect.begin(), vect.end(),sortSize);
	for (iter = vect.begin(); iter != vect.end()-1; iter++)
	{
		count++;
		cout << "name:"<<(*iter).cFileName <<"size:"<<(*iter).nFileSizeLow<< endl;
		if ((*iter).nFileSizeLow == (*(iter + 1)).nFileSizeLow)
		{
			repeat++;
	 	    system(("del "+root+"\\"+(*iter).cFileName).c_str());
		}
	}
	std::cout << "mytreeNotFile is complete,the count is"<<count+1<<"repeat is:"<<repeat<<"\n";
	/*system("start explorer");
	char c[52]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','r',
	'u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J',
	'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int letter,num1,num2;
	char name[100],temp[10];
	srand( (unsigned)time( NULL ) );
	for (j = 0; j < 100; j++)
	{
		letter = rand() % 10 + 2;
		for (i = 0; i<letter; i++)
			name[i] = c[rand() % 52];
		name[letter] = '\0';
		//printf("name=%s\n",name);
		num1 = rand();
		num2 = rand();
		itoa(num1, temp, 10);
		strcat(name, temp);
		itoa(num2, temp, 10);
		strcat(name, temp);
		strcat(name, ".txt");
		printf("name=%s\n", name);
		//fp = fopen(name, "w");
		string command = "ftype >>";
		command += name;
		system(command.c_str());
		//system("start");
		//system("test1.exe");
		//fclose(fp);
	}
	int **a=(int **)malloc(sizeof(int *)*5);
	for(i=0;i<5;i++)
		a[i]=(int *)malloc(sizeof(int)*5);
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			a[i][j]=i+j;
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<5;i++)
	{*/
	 //system("start");
	 //system("test1.exe");
	//}
	return 0;
}



