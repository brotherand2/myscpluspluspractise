# include<stdio.h>
# include<stdlib.h>//调用exit()函数终止需要这个文件
# include<string.h>//字符串函数的头文件
# include<time.h>
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
typedef struct Student
{
	int class;//班级
	char name[20];//姓名
	char sex[10];//姓别
	char institude[30];//学院
}Student;//学生类型

typedef struct Institude
{
	Student stu[2];//两名宿管员
	int count;//学院的人数
	char institude[30];//学院名字
	int isTheSameSex;//1表示姓别相同，0表示不相同
}Institude;//学院类型
int isArrange[13];//学院标记，是否已安排好宿管员，1为安排好，0为没有
Institude college[13];//13个学院
Student stu[26];//26个学生
int count;//读取学生的个数
int male=0;//男同学人数
int female=0;//女同学人数
int isMaleBig;//是否男同学人数较多，1表示是，0表示相等，-1表示女同学较多
int theSameSexCount;//同姓别的对数
void readStudent()//用于读取文件中学生信息
{	
	FILE *fp;//文件指针

    int i=0;
	count=0;
	if((fp=fopen("student.txt","r"))==NULL)//读取student.txt文件
	{
		printf("不能打开student.txt文件,请编辑好学生信息文件!\n");
		exit(0);//终止程序
	}
	while(!feof(fp)&&i<27)//feof(fp)表示文件尾,还没读到文件尾并且人数少于26继续读取,注意如果有26个人就有27个标记
	{
		fscanf(fp,"%d %s %s %s",&stu[i].class,stu[i].name,stu[i].sex,stu[i].institude);
        i++;
	}
    count=i-1;//为什么要减1，比如13个点在同一条直线上，这条直线却只有12段线段，线段数比点数少，所以文件标记在最后数据尾也加了一个标记，标记数为数据个数+1
	fclose(fp);//关闭文件指针
}
void writeDistribute()//将分配信息写入一个文件保存
{
	int i;
	FILE *fp;//文件指针
	if((fp=fopen("distribute result.txt","a+"))==NULL)//创建文件保存学院宿管人员的安排信息
	{
		printf("创建文件失败\n");
		exit(0);
	}
	time(&rawtime);//将rawtime地址传过去，获得时间，以秒计
	timeinfo=localtime(&rawtime);//转换成本地时间，保存在tm时间结构体中
	fprintf(fp,"\n%s %d%s%d%s%d  %d%s%d%s%d\n","当前分配结果的产生时间：",1900+timeinfo->tm_year,",",1+timeinfo->tm_mon,",",timeinfo->tm_mday,timeinfo->tm_hour,":",timeinfo->tm_min,":",timeinfo->tm_sec);
	for(i=0;i<13;i++)
	{
		fprintf(fp,"%s\n",college[i].institude);
		fprintf(fp,"%-10d%-10s%-10s%-10s\n",college[i].stu[0].class,college[i].stu[0].name,college[i].stu[0].sex,college[i].stu[0].institude);
		fprintf(fp,"%-10d%-10s%-10s%-10s\n\n",college[i].stu[1].class,college[i].stu[1].name,college[i].stu[1].sex,college[i].stu[1].institude);
	}
}
void showStudent()//显示学生信息
{
	int i;
	printf("班级      姓名      姓别      学院\n");
	for(i=0;i<count;i++)
	{
		printf("%-10d%-10s%-10s%-10s\n",stu[i].class,stu[i].name,stu[i].sex,stu[i].institude);
	}
	printf("宿管人员一共有:%d\n",count);
	printf("需要检查的学院有以下学院：\n");
	for(i=0;i<13;i++)
		printf("%s\n",college[i].institude);
	if(count<26)
	{
		printf("宿管员的人员信息不足26个，无法为每个学院分配2名学生，请重新填写好宿管人信息，使人人员数大于等于26\n");
		exit(0);
	}
}
void showDistribute()//显示分配结果
{
	int i;
	printf("\n\n分配结果如下:\n");
	for(i=0;i<13;i++)
	{
		printf("%s:\n",college[i].institude);
		printf("%-5d%-10s%-5s%-10s\n",college[i].stu[0].class,college[i].stu[0].name,college[i].stu[0].sex,college[i].stu[0].institude);
		printf("%-5d%-10s%-5s%-10s\n\n",college[i].stu[1].class,college[i].stu[1].name,college[i].stu[1].sex,college[i].stu[1].institude);	
	}
}
void initData()//初始化数据
{
	int i,j,k;
	char institude[16][30]={"土木工程学院","体育学院","美术学院","地理科学与旅游学院",
	           "物理与光信息科技学院","生命与科学学院","文学院","教育科学学院",
	           "电子信息工程学院","数学学院","政法学院","化学与环境学院",
	           "外国语学院","经管与管理学院","音乐学院","计算机学院"
	};//初始化16个学院的名字
	srand((int)time(NULL));//设置于随机数种子为当前系统时间，每次种子不同，产生的随机数也不同
	for(i=0;i<3;i++)//宿管员只到13个学院去检查，随机去掉3个学院
	{
		j=rand()%(16-i);//从剩下的16-i个学院中随机删除一个学院
		for(k=j;k<16-i;k++)
			strcpy(institude[k],institude[k+1]);//将后面的字符串依次覆盖前面的字符串
	}
	for(i=0;i<13;i++)
	{
		isArrange[i]=0;//标记初始化为未标记
		strcpy(college[i].institude,institude[i]);//为每个学院名字初始化
		college[i].isTheSameSex=0;//初始化为每个学院分配异姓别2个学生
		college[i].count=0;//安排好的人数初始化为0
	}
}
void distrubute()//分配宿管人员
{
	int i,j,n;
	int isSuccess;//当前学生是否已成功分配到某个学院检查
	int isSet;//设置标记，0表示未设置，1表示设置好了，设置的是某学院分配的学生姓别相等
    if(isMaleBig!=0)//男女生人数不相等,设置某些学院分配的学生姓别相同
	{
		j=0;
		while(j<theSameSexCount)
		{
			isSet=0;//初始化为未设置
			while(!isSet)
			{
				n=rand()%13;//13个学院随机选一个设置为检查该学院宿舍的学生姓别相同
				if(college[n].isTheSameSex==0)//如果该学院还未设置过分配的学生姓别相同
				{
					college[n].isTheSameSex=1;
					isSet=1;
				}
			}
			j++;//设置的个数加1
		}
	}
	for(i=0;i<26;i++)//将26名学生随机分配到13个学院进行宿检
	{
		isSuccess=0;//一开始还未分配，初始化为0
		printf("要分配的学生姓名:%s\n",stu[i].name);
		while(!isSuccess)//未分配好时，重新随机分配
		{
			    n=rand()%13;
				if(strcmp(stu[i].institude,college[n].institude)!=0)//如果该学生不是来自这个学院，则继续，否则不可以安排他管理自己的学院
				{
					if(college[n].count==0)//还未安排一个学生
					{
						if(college[n].isTheSameSex==0)//如果未要求2名宿管人员姓别相同，满足以上条件，则可以安排他管理这个学院的宿舍
						{
							isSuccess=1;//该学生成功分配
						}
						else//要求2名宿管人员姓别相同
						{
							 if(isMaleBig==1)//男生人数较多,这个学院只能安排男同学
							 {
								 if(strcmp(stu[i].sex,"男")==0)
									 isSuccess=1;
							 }
							 else
							 {
								 if(strcmp(stu[i].sex,"女")==0)
									 isSuccess=1;
							 }
						}
						if(isSuccess==1)
						{
							college[n].count++;//安排的人数加1
							college[n].stu[0]=stu[i];//将该学生安排进该学院管理名单
						}
					}
					else
						if(college[n].count==1)//已安排好一个学生管理这个学院
						{
							if(college[n].isTheSameSex==0)//要求2名宿管人员姓别不相同
							{
								if(strcmp(stu[i].sex,college[n].stu[0].sex)!=0)//如果该学生姓别不同于已安排好的那名同学，则可以安排他管理这个学院的宿舍
								isSuccess=1;//该学生成功分配
							}
							else//要求2名宿管人员姓别相同
							{
								if(strcmp(stu[i].sex,college[n].stu[0].sex)==0)//如果该学生姓别和已安排好的那名同学相同，则可以安排他管理这个学院的宿舍
								isSuccess=1;//该学生成功分配	
							}
							if(isSuccess==1)
							{
								college[n].count++;//安排的人数加1
								college[n].stu[1]=stu[i];//将该学生安排进该学院管理名单
							}
						}
					}
		}
	}
}
void statistics()//统计学生男女人生
{
	int i;
	for(i=0;i<26;i++)
	{
		if(strcmp(stu[i].sex,"男")==0)//该同学是男性
			male++;//男同学人数加1
		else 
			female++;
	}
	if(male>female)
	{
		isMaleBig=1;//男生人数多
		theSameSexCount=(male-female)/2;
	}
	else
	{
		if(male<female)
		{
			isMaleBig=-1;//女生人数多
			theSameSexCount=(female-male)/2;
		}
		else
		{
            isMaleBig=0;//男女生人数相等
			theSameSexCount=0;//无同姓别学生被分到同一个学院
		}
	}
}
void main()
{
	initData();//初始化数据
	readStudent();//用于读取文件中学生信息
	showStudent();//显示学生信息
	statistics();//统计 学生男女人生
	distrubute();//分配宿管人员
    showDistribute();//显示分配结果
	writeDistribute();//将分配信息写入一个文件保存
}