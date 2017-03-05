# include<stdio.h>
# include<string.h>
# include<time.h>
void main()
{
	int i=0;
	time_t rawtime;//时间类型，在time.h定义
	struct tm *timeinfo;//时间结构，在time.h中定义如下
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
	time(&rawtime);//将rawtime地址传过去，获得时间，以秒计
	timeinfo=localtime(&rawtime);//转换成本地时间，保存在tm时间结构体中
	printf("当前时间是%s %d年,%d月,%d日，%d:%d:%d",asctime(timeinfo),1900+timeinfo->tm_year,1+timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	//tm_year是从1900年开始计算经过了多少年，所以年份数要加1900，月份是从0月份开始算，比如tm_mon=5,是从0-5一共6个月
	srand((int)time(NULL));//设定随机数种子
	for(i=0;i<10;i++)
		printf("%d  ",rand()%7);
	if(strcmp("张三","李四")==0)
	{
		printf("张三李四相等\n");
	}
	if(strcmp("张三","张三")==0)
	{
		printf("张三张三相等\n");
	}


	printf("\n");
}