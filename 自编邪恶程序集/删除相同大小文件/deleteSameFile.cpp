# include<iostream>
# include<vector>
# include<string>
# include<fstream>
# include<algorithm>
# include<windows.h>
using namespace std;
std::vector<WIN32_FIND_DATA> vect;
std::string root ;//��Ŀ¼
std::string type;//�ļ�����
char deleteType[100];//Ҫɾ��������
char path[100];//Ҫɾ����·��
bool sortSize(WIN32_FIND_DATA &fd1, WIN32_FIND_DATA &fd2)
{
	return(fd1.nFileSizeLow < fd2.nFileSizeLow);
}
void deleteSameSizeFile()//ɾ��ָ����ʽ��ͬ��С�ļ�
{
	int count = 0;//�ļ�����
	int repeat = 0;//�ظ�����
	vector<WIN32_FIND_DATA>::iterator iter;
	sort(vect.begin(), vect.end(), sortSize);
	for (iter = vect.begin(); iter != vect.end() - 1; iter++)
	{
		count++;
		cout << "name:" << (*iter).cFileName << "size:" << (*iter).nFileSizeLow << endl;
		if ((*iter).nFileSizeLow == (*(iter + 1)).nFileSizeLow)//��ǰ�ļ�����һ���ļ���С��ͬ
		{
			repeat++;
			if ((*iter).dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
				continue;
			system(("del \"" + root + "\\" + (*iter).cFileName+"\"").c_str());//ɾ����ǰ�ļ�
		}
	}
	std::cout << "mytreeNotFile is complete,the count is" << count + 1 << "��repeat is:" << repeat << "\n";
}
void findFile(string root)
{
	WIN32_FIND_DATA fd;//fd�ļ���Ϣ�ṹ
	HANDLE handle;//handle�ļ�����
	int count = 0;//�ļ�����
	string  find=root + type;
	handle = FindFirstFile((find).c_str(), &fd);//�ļ�����
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
			if (fd.cFileName[0] == '.')//win32��һ����������ļ��У�һ���ǡ�.��ָ���ǵ�ǰ�ļ��У�һ���ǡ�..��ָ�����ϲ��ļ��У����һ�־�����ͨ���²��ļ������ļ�������ʾ��cd .�Ǳ�Ŀ¼��cd ..���ϼ�Ŀ¼
				continue;//����Ϊ�˲��ص��ϼ�Ŀ¼����ԭĿ¼��ת������.��..�����Ŀ¼
				count++;
				vect.push_back(fd);
			cout << "the  file is " << fd.cFileName << endl;
		} while (FindNextFile(handle, &fd));//FindFirstFile����ʱָ����һ���ļ���������һ���ļ�
	}
}

void inputPath()//����·��
{
	do
	{
		cout << "\n�����Ŀ¼,����Ϊ��<��d:\\helloworld\\test>:";
		cin.getline(path, 100);
		root = path;
	} while (path[0] == '\0');
}
void inputType()//��������
{
	type= "\\*.*";//Ҫ���ҵ��ļ����ͣ������ļ�	
	cout << "�����ļ� *.*,�ı��ļ� *.txt �����ļ� *.mp3 \n����:1��*.*\n2��*.mp3 *.wmv\n3��*.txt *.mkv *.mp3 \n��\"-----1��ɾ��ָ����ʽ��ͬ��С�ļ���\"ֻ����һ������\n�����ļ�����<����enterĬ�������ļ�����>:";
	cin.getline(deleteType, 50);
	if (deleteType[0] != '\0')//���ǻس����������Ͳ���Ĭ��
		type = string("\\") + deleteType;
	cout << "will delete Type is:" << type << endl;
	cout << root + type << endl;
}
int main()
{
	using namespace std;
	int choise = 0;//ѡ��
	bool flag = true;//ѭ�����
	system("title ���»��ļ�����");
	system("mode con cols=105 lines=100&color 81");
	while (true)
	{
		choise = -1;
		cout << "-----0���˳�\n";
		cout << "-----1��ɾ��ָ����ʽ��ͬ��С�ļ� \n";
		cout << "-----2��ɾ��ָ����ʽ�������ļ�(��������Ŀ¼)\n";
		cout << "-----3��ɾ��ָ����ʽ�������ļ�(����Ŀ¼)\n";
		cout << "-----4��ɾ�������ļ���\n";
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
			findFile(root);//�Ӹ�Ŀ¼������1�㿪ʼ��
			cout << "���س�<enter>ɾ��";
			getchar();
			deleteSameSizeFile();//ɾ��ָ����ʽ��ͬ��С�ļ�
			break;
		case 2:
			inputPath();
			inputType();
			cout << "���س�<enter>ɾ��";
			getchar();
			system(("del \"" + root + type+"\" /q").c_str());//ɾ��ָ����ʽ�������ļ�(��������Ŀ¼)
			break;
		case 3:
			inputPath();
			inputType();
			cout << "���س�<enter>ɾ��";
			getchar();
			system(("del \"" + root + type + "\" /s /q").c_str());// ɾ��ָ����ʽ�������ļ�(����Ŀ¼)
			break;
		case 4:
			inputPath();
			cout << "���س�<enter>ɾ��";
			getchar();
			system(("del \"" + root + "\" /s /q").c_str());//��ɾ�����ļ��������ļ�
			system(("rd \"" + root + "\" /s /q").c_str());//���ɾ��ʣ�µĿ�Ŀ¼
			break;
		default:
			cout << "input error!\n";
			break;
		}
	}
	return 0;
}
