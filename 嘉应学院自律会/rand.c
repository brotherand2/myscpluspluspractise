# include<stdio.h>
# include<string.h>
# include<time.h>
void main()
{
	int i=0;
	time_t rawtime;//ʱ�����ͣ���time.h����
	struct tm *timeinfo;//ʱ��ṹ����time.h�ж�������
	/*
	 int tm_sec;
	 int tm_min;
	 int tm_hour;
	 int tm_mday;
	 int tm_mon;
	 int tm_year;
	 int tm_wday;
	 int tm_yday;
	 int tm_isdst;
	*/
	time(&rawtime);//��rawtime��ַ����ȥ�����ʱ�䣬�����
	timeinfo=localtime(&rawtime);//ת���ɱ���ʱ�䣬������tmʱ��ṹ����
	printf("��ǰʱ����%s %d��,%d��,%d�գ�%d:%d:%d",asctime(timeinfo),1900+timeinfo->tm_year,1+timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	//tm_year�Ǵ�1900�꿪ʼ���㾭���˶����꣬���������Ҫ��1900���·��Ǵ�0�·ݿ�ʼ�㣬����tm_mon=5,�Ǵ�0-5һ��6����
	srand((int)time(NULL));//�趨���������
	for(i=0;i<10;i++)
		printf("%d  ",rand()%7);
	if(strcmp("����","����")==0)
	{
		printf("�����������\n");
	}
	if(strcmp("����","����")==0)
	{
		printf("�����������\n");
	}


	printf("\n");
}