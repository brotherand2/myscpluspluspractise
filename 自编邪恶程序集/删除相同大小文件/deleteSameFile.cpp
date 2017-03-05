# include<iostream>
# include<vector>
# include<string>
# include<fstream>
# include<algorithm>
# include<windows.h>
using namespace std;
std::vector<WIN32_FIND_DATA> vect;
std::string root ;//根目录
std::string type;//文件类型
char deleteType[100];//要删除的类型
char path[100];//要删除的路径
bool sortSize(WIN32_FIND_DATA &fd1, WIN32_FIND_DATA &fd2)
{
	return(fd1.nFileSizeLow < fd2.nFileSizeLow);
}
void deleteSameSizeFile()//删除指定格式相同大小文件
{
	int count = 0;//文件个数
	int repeat = 0;//重复个数
	vector<WIN32_FIND_DATA>::iterator iter;
	sort(vect.begin(), vect.end(), sortSize);
	for (iter = vect.begin(); iter != vect.end() - 1; iter++)
	{
		count++;
		cout << "name:" << (*iter).cFileName << "size:" << (*iter).nFileSizeLow << endl;
		if ((*iter).nFileSizeLow == (*(iter + 1)).nFileSizeLow)//当前文件与下一个文件大小相同
		{
			repeat++;
			if ((*iter).dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)//只要FILE_ATTRIBUTE_DIRECTORY=0x00000010，即只要从右数，第5位为1，即是文件目录，其它位是标只读、只写、隐藏等属性
				continue;
			system(("del \"" + root + "\\" + (*iter).cFileName+"\"").c_str());//删除当前文件
		}
	}
	std::cout << "mytreeNotFile is complete,the count is" << count + 1 << "，repeat is:" << repeat << "\n";
}
void findFile(string root)
{
	WIN32_FIND_DATA fd;//fd文件信息结构
	HANDLE handle;//handle文件名柄
	int count = 0;//文件个数
	string  find=root + type;
	handle = FindFirstFile((find).c_str(), &fd);//文件名柄
	if (handle == INVALID_HANDLE_VALUE)
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
				count++;
				vect.push_back(fd);
			cout << "the  file is " << fd.cFileName << endl;
		} while (FindNextFile(handle, &fd));//FindFirstFile函数时指定的一个文件名查找下一个文件
	}
}

void inputPath()//输入路径
{
	do
	{
		cout << "\n输入根目录,不能为空<如d:\\helloworld\\test>:";
		cin.getline(path, 100);
		root = path;
	} while (path[0] == '\0');
}
void inputType()//输入类型
{
	type= "\\*.*";//要查找的文件类型，所有文件	
	cout << "所有文件 *.*,文本文件 *.txt 音乐文件 *.mp3 \n样例:1、*.*\n2、*.mp3 *.wmv\n3、*.txt *.mkv *.mp3 \n在\"-----1、删除指定格式相同大小文件下\"只能有一个参数\n输入文件类型<输入enter默认所有文件类型>:";
	cin.getline(deleteType, 50);
	if (deleteType[0] != '\0')//不是回车符，则类型不是默认
		type = string("\\") + deleteType;
	cout << "will delete Type is:" << type << endl;
	cout << root + type << endl;
}
int main()
{
	using namespace std;
	int choise = 0;//选择
	bool flag = true;//循环标记
	system("title 曾勇华文件管理");
	system("mode con cols=105 lines=100&color 81");
	while (true)
	{
		choise = -1;
		cout << "-----0、退出\n";
		cout << "-----1、删除指定格式相同大小文件 \n";
		cout << "-----2、删除指定格式的所有文件(不包含子目录)\n";
		cout << "-----3、删除指定格式的所有文件(含子目录)\n";
		cout << "-----4、删除整个文件夹\n";
		cout << "input your choise:";
		cin >> choise;
		cin.get();
		switch (choise)
		{
		case 0:
			flag = false;
			break;
		case 1:
			inputPath();
			inputType();
			findFile(root);//从根目录，即第1层开始找
			cout << "按回车<enter>删除";
			getchar();
			deleteSameSizeFile();//删除指定格式相同大小文件
			break;
		case 2:
			inputPath();
			inputType();
			cout << "按回车<enter>删除";
			getchar();
			system(("del \"" + root + type+"\" /q").c_str());//删除指定格式的所有文件(不包含子目录)
			break;
		case 3:
			inputPath();
			inputType();
			cout << "按回车<enter>删除";
			getchar();
			system(("del \"" + root + type + "\" /s /q").c_str());// 删除指定格式的所有文件(含子目录)
			break;
		case 4:
			inputPath();
			cout << "按回车<enter>删除";
			getchar();
			system(("del \"" + root + "\" /s /q").c_str());//先删除该文件夹所有文件
			system(("rd \"" + root + "\" /s /q").c_str());//最后删除剩下的空目录
			break;
		default:
			cout << "input error!\n";
			break;
		}
	}
	return 0;
}
