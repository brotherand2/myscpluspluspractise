/*C���԰汾  �������Ŀǰ���ȶ���������ʧ�ܵĽ������ʾ��·������ʾ��һ����ȷ�ķ���*/
# include<stdio.h>
# include<stdlib.h>//����exit()������ֹ��Ҫ����ļ�
# include<string.h>//�ַ���������ͷ�ļ�
# include<time.h>
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
typedef struct Student
{
	int class;//�༶
	char name[20];//����
	char sex[10];//�ձ�
	char institude[30];//ѧԺ
}Student;//ѧ������

typedef struct Institude
{
	Student stu[2];//�����޹�Ա
	int count;//ѧԺ������
	char institude[30];//ѧԺ����
	int isTheSameSex;//1��ʾ�ձ���ͬ��0��ʾ����ͬ
}Institude;//ѧԺ����
Institude college[13];//13��ѧԺ
Student stu[26];//26��ѧ��
int count;//��ȡѧ���ĸ���
int male=0;//��ͬѧ����
int female=0;//Ůͬѧ����
int isMaleBig;//�Ƿ���ͬѧ�����϶࣬1��ʾ�ǣ�0��ʾ��ȣ�-1��ʾŮͬѧ�϶�
int isSuccess;//��ǰѧ���Ƿ��ѳɹ����䵽ĳ��ѧԺ���
int theSameSexCount;//ͬ�ձ�Ķ���
void readStudent()//���ڶ�ȡ�ļ���ѧ����Ϣ
{	
	FILE *fp;//�ļ�ָ��

    int i=0;
	count=0;
	if((fp=fopen("�����ļ�.txt","r"))==NULL)//��ȡstudent.txt�ļ�
	{
		printf("���ܴ�student.txt�ļ�,��༭��ѧ����Ϣ�ļ�!\n");
		exit(0);//��ֹ����
	}
	while(!feof(fp)&&i<27)//feof(fp)��ʾ�ļ�β,��û�����ļ�β������������26������ȡ,ע�������26���˾���27�����
	{
		fscanf(fp,"%d %s %s %s",&stu[i].class,stu[i].name,stu[i].sex,stu[i].institude);
		if(stu[i].class<=0||(strcmp(stu[i].sex,"��")!=0&&strcmp(stu[i].sex,"Ů")!=0))
		{
			printf("student�ļ���ʽ����ȷ����ȷ��ʽ��ÿһ�ж���ʾ��\n���� �ַ���  �ַ���  �ַ��� ����1203  ���� ��  �����ѧԺ\n�����´���student.txt\n");
		    exit(0);
		}
        i++;
	}
    count=i-1;//ΪʲôҪ��1������13������ͬһ��ֱ���ϣ�����ֱ��ȴֻ��12���߶Σ��߶����ȵ����٣������ļ�������������βҲ����һ����ǣ������Ϊ���ݸ���+1
   	if(count<26)
	{
		printf("�޹�Ա����Ա��Ϣ����26�����޷�Ϊÿ��ѧԺ����2��ѧ������������д���޹�����Ϣ��ʹ����Ա�����ڵ���26\n");
		exit(0);
	}
	fclose(fp);//�ر��ļ�ָ��
}
void writeDistribute()//��������Ϣд��һ���ļ�����
{
	int i;
	FILE *fp;//�ļ�ָ��
	if((fp=fopen("C:\\Users\\���»�\\Desktop\\������.txt","a+"))==NULL)//�����ļ�����ѧԺ�޹���Ա�İ�����Ϣ
	{
		printf("�����ļ�ʧ��\n");
		exit(0);
	}
	time(&rawtime);//��rawtime��ַ����ȥ�����ʱ�䣬�����
	timeinfo=localtime(&rawtime);//ת���ɱ���ʱ�䣬������tmʱ��ṹ����
	fprintf(fp,"\n%s %d%s%d%s%d  %d%s%d%s%d\n","��ǰ�������Ĳ���ʱ�䣺",1900+timeinfo->tm_year,",",1+timeinfo->tm_mon,",",timeinfo->tm_mday,timeinfo->tm_hour,":",timeinfo->tm_min,":",timeinfo->tm_sec);
	for(i=0;i<13;i++)
	{
		fprintf(fp,"%s\n",college[i].institude);
		fprintf(fp,"%-10d%-10s%-10s%-10s\n",college[i].stu[0].class,college[i].stu[0].name,college[i].stu[0].sex,college[i].stu[0].institude);
		fprintf(fp,"%-10d%-10s%-10s%-10s\n\n",college[i].stu[1].class,college[i].stu[1].name,college[i].stu[1].sex,college[i].stu[1].institude);
	}
	if(!isSuccess)
		fprintf(fp,"%s\n","���䲻�ɹ��������·���");
	fclose(fp);
}
void showStudent()//��ʾѧ����Ϣ
{
	int i;
	printf("�༶      ����      �ձ�      ѧԺ\n");
	for(i=0;i<count;i++)
	{
		printf("%-10d%-10s%-10s%-10s\n",stu[i].class,stu[i].name,stu[i].sex,stu[i].institude);
	}
	printf("�޹���Աһ����:%d\n",count);
	if(count<26)
	{
		printf("�޹�Ա����Ա��Ϣ����26�����޷�Ϊÿ��ѧԺ����2��ѧ������������д���޹�����Ϣ��ʹ����Ա�����ڵ���26\n");
		exit(0);
	}
}

void initData()//��ʼ������
{
	int i,j,k;
	Student temp;
	char institude[16][30]={"��ľ����ѧԺ","����ѧԺ","����ѧԺ","�����ѧ������ѧԺ",
	           "���������Ϣ�Ƽ�ѧԺ","�������ѧѧԺ","��ѧԺ","������ѧѧԺ",
	           "������Ϣ����ѧԺ","��ѧѧԺ","����ѧԺ","��ѧ�뻷��ѧԺ",
	           "�����ѧԺ","���������ѧԺ","����ѧԺ","�����ѧԺ"
	};//��ʼ��16��ѧԺ������
	srand((int)time(NULL));//���������������Ϊ��ǰϵͳʱ�䣬ÿ�����Ӳ�ͬ�������������Ҳ��ͬ
	for(i=0;i<3;i++)//�޹�Աֻ��13��ѧԺȥ��飬���ȥ��3��ѧԺ
	{
		j=rand()%(16-i);//��ʣ�µ�16-i��ѧԺ�����ɾ��һ��ѧԺ
		for(k=j;k<16-i;k++)
			strcpy(institude[k],institude[k+1]);//��������ַ������θ���ǰ����ַ���
	}
	temp.institude[0]='\0';//��ʱѧ���ĸ���������Ϊ�ջ�0
	temp.name[0]='\0';
	temp.sex[0]='\0';
	temp.class=0;
	for(i=0;i<13;i++)
	{
		strcpy(college[i].institude,institude[i]);//Ϊÿ��ѧԺ���ֳ�ʼ��
		college[i].isTheSameSex=0;//��ʼ��Ϊÿ��ѧԺ�������ձ�2��ѧ��
		college[i].count=0;//���źõ�������ʼ��Ϊ0
		college[i].stu[0]=college[i].stu[1]=temp;//���յ�ѧ���ṹ���ÿ��ѧԺ���޹�Ա���г�ʼ��
	}

	male=female=0;//��Ů��������ʼ��Ϊ0
    isMaleBig=0;
    theSameSexCount=0;
}
void distrubute()//�����޹���Ա
{
	int i,j,n;
	int number;//����������Ĵ���
	int isSet;//���ñ�ǣ�0��ʾδ���ã�1��ʾ���ú��ˣ����õ���ĳѧԺ�����ѧ���ձ����
	printf("��Ҫ����ѧԺ������ѧԺ��\n");
	for(i=0;i<13;i++)
		printf("%s\n",college[i].institude);

	if(isMaleBig!=0)//��Ů�����������,����ĳЩѧԺ�����ѧ���ձ���ͬ
	{
		j=0;
		while(j<theSameSexCount)
		{
			isSet=0;//��ʼ��Ϊδ����
			while(!isSet)
			{
				n=rand()%13;//13��ѧԺ���ѡһ������Ϊ����ѧԺ�����ѧ���ձ���ͬ
				if(college[n].isTheSameSex==0)//�����ѧԺ��δ���ù������ѧ���ձ���ͬ
				{
					college[n].isTheSameSex=1;
					isSet=1;
				}
			}
			j++;//���õĸ�����1
		}
	}
	isSuccess=1;
	for(i=0;i<26&&isSuccess;i++)//��26��ѧ��������䵽13��ѧԺ�����޼�
	{
		isSuccess=0;//һ��ʼ��δ���䣬��ʼ��Ϊ0
		number=0;
		while(!isSuccess)//δ�����ʱ�������������
		{
			    n=rand()%13;
				number++;//����������Ĵ�����1
				if(number>1000)//1000�λ����ɹ���˵������һ��ѧ����δ��������Ϊ��δ���źõ�ʣ��һ��ѧԺ�������ѧ����ѧԺ���޷����䣬�����˽�����һ�ֵ����·���
				{
					break;
				}
				if(strcmp(stu[i].institude,college[n].institude)!=0)//�����ѧ�������������ѧԺ������������򲻿��԰����������Լ���ѧԺ
				{
					if(college[n].count==0)//��δ����һ��ѧ��
					{
						if(college[n].isTheSameSex==0)//���δҪ��2���޹���Ա�ձ���ͬ��������������������԰������������ѧԺ������
						{
							isSuccess=1;//��ѧ���ɹ�����
						}
						else//Ҫ��2���޹���Ա�ձ���ͬ
						{
							 if(isMaleBig==1)//���������϶�,���ѧԺֻ�ܰ�����ͬѧ
							 {
								 if(strcmp(stu[i].sex,"��")==0)
									 isSuccess=1;
							 }
							 else
							 {
								 if(strcmp(stu[i].sex,"Ů")==0)
									 isSuccess=1;
							 }
						}
						if(isSuccess==1)
						{
							college[n].count++;//���ŵ�������1
							college[n].stu[0]=stu[i];//����ѧ�����Ž���ѧԺ��������
						}
					}
					else
						if(college[n].count==1)//�Ѱ��ź�һ��ѧ���������ѧԺ
						{
							if(college[n].isTheSameSex==0)//Ҫ��2���޹���Ա�ձ���ͬ
							{
								if(strcmp(stu[i].sex,college[n].stu[0].sex)!=0)//�����ѧ���ձ�ͬ���Ѱ��źõ�����ͬѧ������԰������������ѧԺ������
								isSuccess=1;//��ѧ���ɹ�����
							}
							else//Ҫ��2���޹���Ա�ձ���ͬ
							{
								if(strcmp(stu[i].sex,college[n].stu[0].sex)==0)//�����ѧ���ձ���Ѱ��źõ�����ͬѧ��ͬ������԰������������ѧԺ������
								isSuccess=1;//��ѧ���ɹ�����	
							}
							if(isSuccess==1)
							{
								college[n].count++;//���ŵ�������1
								college[n].stu[1]=stu[i];//����ѧ�����Ž���ѧԺ��������
							}
						}
					}
		}
	}
}
void statistics()//ͳ��ѧ����Ů����
{
	int i;
	for(i=0;i<26;i++)
	{
		if(strcmp(stu[i].sex,"��")==0)//��ͬѧ������
			male++;//��ͬѧ������1
		else 
			female++;
	}
	if(male>female)
	{
		isMaleBig=1;//����������
		theSameSexCount=(male-female)/2;
	}
	else
	{
		if(male<female)
		{
			isMaleBig=-1;//Ů��������
			theSameSexCount=(female-male)/2;
		}
		else
		{
            isMaleBig=0;//��Ů���������
			theSameSexCount=0;//��ͬ�ձ�ѧ�����ֵ�ͬһ��ѧԺ
		}
	}
}
void showDistribute()//��ʾ������
{
	int i;
	printf("\n\n����������:\n");
	while(!isSuccess)//�����ǰѧ��û�з��䵽ѧԺ������ѧ�������ٷ��䣬ֱ������ѧ������ɹ�Ϊֹ
	{
		initData();//��ʼ������
		statistics();//ͳ�� ѧ����Ů����
		distrubute();//�����޹���Ա
	}
	for(i=0;i<13;i++)
	{
		printf("%s:\n",college[i].institude);
		printf("%-5d%-10s%-5s%-10s\n",college[i].stu[0].class,college[i].stu[0].name,college[i].stu[0].sex,college[i].stu[0].institude);
		printf("%-5d%-10s%-5s%-10s\n\n",college[i].stu[1].class,college[i].stu[1].name,college[i].stu[1].sex,college[i].stu[1].institude);	
	}
	if(!isSuccess)
		printf("���䲻�ɹ��������·���\n");
}
void menu()//�˵�
{
	printf("       ��������������������������������������\n"); 
	printf("       ��   <0>--------�˳�                ��\n"); 
	printf("       ��   <1>--------���䲢��ʾ������  ��\n"); 
	printf("       ��   <2>--------��ʾѧ����Ϣ        ��\n"); 
	printf("       ��������������������������������������\n");
}

void main()
{
	int entry=1;//��ڱ�־��1��ʾ�������0�˳�
	int choice;
	while(entry)
	{
		menu();
		choice=-1;//��ʼ��Ϊ-1��������0-2���κ�һ��ѡ��
		printf("���������ѡ��:");
		scanf("%d",&choice);
		while(getchar()!='\n')//���˷����ֵ��ַ�
			;
		switch(choice)
		{
		case 0:
			entry=0;//�˳�
			break;
		case 1:
			{
				initData();//��ʼ������
				readStudent();//���ڶ�ȡ�ļ���ѧ����Ϣ
				statistics();//ͳ�� ѧ����Ů����
				distrubute();//�����޹���Ա
				showDistribute();//��ʾ������
				writeDistribute();//��������Ϣд��һ���ļ�����
			}break;
		case 2:
             readStudent();//���ڶ�ȡ�ļ���ѧ����Ϣ
	         showStudent();//��ʾѧ����Ϣ
             break;
		default:
			printf("���������������.\n");
			break;
		}
	}
}