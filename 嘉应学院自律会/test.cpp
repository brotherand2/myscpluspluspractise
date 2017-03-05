#include<stdio.h>
int main()
{
	char c=255;
    unsigned cc=255;
	printf("char :%c %d %02x\n",c,c,c);//看看unsigned char c和char c分别输出什么

	printf("unsigned char :%c %d %02x\n",cc,cc,cc);//看看unsigned char c和char c分别输出什么
	return 0;
}