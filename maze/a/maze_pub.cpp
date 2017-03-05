#include "maze.h"

static char *MallocNode[MAX_NODE_NUMBER + 1];
static int  MallocIndex; 

void initMalloc()
{
	memset(MallocNode, 0x00, sizeof( MallocNode ));
	MallocIndex = 0;

	return;
}

void addMallocNode(char *mallocPtr)
{

	if( NULL != mallocPtr )
		MallocNode[MallocIndex++] = ( char *)mallocPtr;
	return;
}

void *gcCalloc(size_t nmemb, size_t size)
{
	char *ptr = (char *)calloc(nmemb, size);
	addMallocNode(ptr);
	return ptr;
}

/*
 * 功能：释放链表的全局节点
 */
void freeMallocNode()
{
	int index = 0;
	for(; index <  MAX_NODE_NUMBER; index ++) 
	{
		if(NULL !=  MallocNode[index])
		{
			free( MallocNode[index] );
			MallocNode[index] = NULL;
		}
	}
	MallocIndex = 0;
	return;
}

char *GetFldStr(char *sFldStr, char *sStr, char sFld)
{
    char *p;

    if(sStr == NULL)
    {
        sFldStr[0] = '\0';
        return NULL;
    }
    p = strchr(sStr, sFld);
    if(p == NULL)
    {
        strcpy(sFldStr, sStr);
        return NULL;
    }
    strncpy(sFldStr, sStr, p - sStr);
    sFldStr[p - sStr] = '\0';

    return (p + 1);
}
