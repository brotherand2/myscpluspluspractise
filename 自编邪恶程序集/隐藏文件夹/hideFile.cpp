# include<iostream>
# include<string>
# include<windows.h>
# include<fstream>
std::string directory[26] = { "a:", "b:", "c:", "d:", "e:", "f:", "g:",
"h:", "i:", "j:", "k:", "l:", "m:", "n:", "o:", "p:", "q:","r:", "s:", 
"t:", "u:", "v:", "w:", "x:", "y:", "z:" };//������
std::string path[100];//��ǰ���̵������ļ���
std::string type = "\\*.*";//Ҫ���ҵ��ļ����ͣ������ļ�
void hideFile(int disk )//���������ļ���Ŀ¼;
{//diskΪ�ĸ���
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
	int count = 0;//���ֵ��ļ���
	string  find=root + type;

	handle = FindFirstFile((directory[disk] + type).c_str(), &fd);//���ҵ�һ���ļ�
	if (handle == INVALID_HANDLE_VALUE)//�Ҳ����ļ�
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
			path[count]=fd.cFileName;//���ҵ����ļ�������
			count++;			
		} while (FindNextFile(handle, &fd));//FindFirstFile����ʱָ����һ���ļ���������һ���ļ�
        string attrib="attrib +s +r +h /s /d ";
        /*for(int i=0;i<count;i++)
		{
		  cout << "the  file is " << path[i] << endl;
		  if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
		  system((attrib + "\\\""+path[i] + "\"\\*.* /s /d").c_str());//���ص�ǰĿ¼����Ŀ¼�������ļ�
		 system((attrib+"\\\""+path[i]+"\"").c_str());//������Ŀ¼�ļ�
		}*/
		cout<<directory[disk]<<endl;

		system((attrib+directory[disk]+type).c_str());
       	system("pause");
		attrib = "attrib -s -r -h /s /d " ;
     /*
       for( i=0;i<count;i++)
		{
  	    cout << "recover the  file is " << path[i] << endl;
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//ֻҪFILE_ATTRIBUTE_DIRECTORY=0x00000010����ֻҪ����������5λΪ1�������ļ�Ŀ¼������λ�Ǳ�ֻ����ֻд�����ص�����
		  system((attrib + "\\\""+path[i] + "\"\\*.* /s /d").c_str());//���ص�ǰĿ¼����Ŀ¼�������ļ�
		  system((attrib+"\\\""+path[i]+"\"").c_str());//������Ŀ¼�ļ�
		}
		*/
		system((attrib+directory[disk]+type).c_str());
       	system("pause");
		FindClose(handle);//�ر��ļ����
	}
}
int main()
{
	int i;
	for(i=0;i<26;i++)
		hideFile(i);
    return 0;
}
