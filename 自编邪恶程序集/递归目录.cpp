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
std::string root = "E:\\��ֽ\\SogouWP\\Local\\WallPaper";//��Ŀ¼
std::string type = "\\*.*";//Ҫ���ҵ��ļ����ͣ������ļ�
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
//bool myFindNextFile(HANDLE &handle, WIN32_WIN32_FIND_DATA &fdFIND_DATA &fd, int layer);//�ҵ��ڼ���Ŀ¼

void showFileAttribute(WIN32_FIND_DATA &fd)//��ʾ�ļ�����
{
	using  std::cout;
	using std::endl;
	using namespace std;
	ofstream ccout;
	ccout.open("attribute.txt", ios::app);
	if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || fd.dwFileAttributes == 17)
		ccout << "Ŀ¼";
	ccout << "�ļ�����:" << fd.cFileName << endl <<
		" 8.3��ʽ�ļ���:" << fd.cAlternateFileName << endl <<
		"�ļ�����:" << fd.dwFileAttributes << endl <<
		"ϵͳ����0:" << fd.dwReserved0 << endl <<
		"ϵͳ����1:" << fd.dwReserved1 << endl <<
		"�ļ�����ʱ��:" << fd.ftCreationTime.dwHighDateTime << "," << fd.ftCreationTime.dwLowDateTime << endl <<
		"�ļ����һ�η���ʱ��:" << fd.ftLastAccessTime.dwHighDateTime << "," << fd.ftLastAccessTime.dwLowDateTime << endl <<
		"�ļ����һ��д��ʱ��:" << fd.ftLastWriteTime.dwHighDateTime << "," << fd.ftLastWriteTime.dwLowDateTime << endl <<
		"�ļ���С:" << fd.nFileSizeHigh << "," << fd.nFileSizeLow << endl << endl;
}
void writeTree(WIN32_FIND_DATA &fd, int layer,int disk)//��ʾ��״ͼ
{
	int i;
	using namespace std;
	ofstream os;
	string file = directory[disk][0] + string("treeNotFile.txt");
	os.open(file, ios::app);
	for (i = 1; i < layer; i++)
	{
		if (level[i])
			os << "��  ";
		else
			os << "    ";

	}
	if (level[i])
		os << "����" << fd.cFileName << std::endl;
	else
		os << "����" << fd.cFileName << std::endl;
}
void showTree(WIN32_FIND_DATA &fd, int layer)//��ʾ��״ͼ
{
	int i;
	for (i = 1; i < layer; i++)
	{
		if (level[i])
			std::cout << "��  ";
		else
			std::cout << "    ";

	}
	if (level[i])
		std::cout << "����" << fd.cFileName << std::endl;
	else
		std::cout << "����" << fd.cFileName << std::endl;

}

int countCurrentDirectoryFile(std::string CurrentPath, bool showFile)//��ǰĿ¼���ļ�������������.��..Ŀ¼
{//showFileΪtrue������ļ���Ŀ¼��Ϊfalse��ֻ����Ŀ¼
	using namespace std;
	HANDLE handle;//handle�ļ�����
	WIN32_FIND_DATA fd;//fd�ļ���Ϣ�ṹ
	string test, find;
	int count = 0;
	find = CurrentPath + type;
	//std::cout << "find=" << find << endl;
	handle = FindFirstFile((CurrentPath + type).c_str(), &fd);
	do
	{
		if (fd.cFileName[0] == '.')//win32��һ����������ļ��У�һ���ǡ�.��ָ���ǵ�ǰ�ļ��У�һ���ǡ�..��ָ�����ϲ��ļ��У����һ�־�����ͨ���²��ļ������ļ�������ʾ��cd .�Ǳ�Ŀ¼��cd ..���ϼ�Ŀ¼
			continue;//����Ϊ�˲��ص��ϼ�Ŀ¼����ԭĿ¼��ת������.��..�����Ŀ¼
		if (showFile)
		  count++;
		else
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
				count++;
		}
	} while (FindNextFile(handle, &fd));//FindFirstFile����ʱָ����һ���ļ���������һ���ļ�
	FindClose(handle);
	return count;
}
void FindAllFile(  int layer,std::string CurrentPath,bool showFile,int disk )//���������ļ���Ŀ¼;
{//layer�ļ�Ŀ¼��Σ�CurrentPath��ǰ·��,showFileΪtrue����ʾ�ļ���Ŀ¼��Ϊfalse��ֻ��ʾĿ¼
	using namespace std;
	/*
	typedef struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes; //�ļ�����
	FILETIME ftCreationTime; // �ļ�����ʱ��
	FILETIME ftLastAccessTime; // �ļ����һ�η���ʱ��
	FILETIME ftLastWriteTime; // �ļ����һ���޸�ʱ��
	DWORD nFileSizeHigh; // �ļ����ȸ�32λ
	DWORD nFileSizeLow; // �ļ����ȵ�32λ
	DWORD dwReserved0; // ϵͳ����
	DWORD dwReserved1; // ϵͳ����
	_Field_z_ CHAR   cFileName[ MAX_PATH ];// ���ļ���

	_Field_z_ CHAR   cAlternateFileName[ 14 ]; // 8.3��ʽ�ļ���
	#ifdef _MAC
	DWORD dwFileType;
	DWORD dwCreatorType;
	WORD  wFinderFlags;
	#endif
	} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
	*/
	WIN32_FIND_DATA fd;//fd�ļ���Ϣ�ṹ
	HANDLE handle;//handle�ļ�����
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
			if (fd.cFileName[0] == '.')//win32��һ����������ļ��У�һ���ǡ�.��ָ���ǵ�ǰ�ļ��У�һ���ǡ�..��ָ�����ϲ��ļ��У����һ�־�����ͨ���²��ļ������ļ�������ʾ��cd .�Ǳ�Ŀ¼��cd ..���ϼ�Ŀ¼
				continue;//����Ϊ�˲��ص��ϼ�Ŀ¼����ԭĿ¼��ת������.��..�����Ŀ¼
			if (showFile)
			count++;
			else
			{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
					count++;
			}
			if (count == countCurrentDirectoryFile(CurrentPath,showFile))
				level[layer] = 0;
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
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
		} while (FindNextFile(handle, &fd));//FindFirstFile����ʱָ����һ���ļ���������һ���ļ�


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
	//FindAllFile(1,directory[i],false,i);//�Ӹ�Ŀ¼������1�㿪ʼ��
	//FindAllFile(1, directory[i], true, i);//�Ӹ�Ŀ¼������1�㿪ʼ��
	FindAllFile(1, root, true, i);//�Ӹ�Ŀ¼������1�㿪ʼ��
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



