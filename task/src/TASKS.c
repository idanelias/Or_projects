#include "../include/TASK.h"
#include "../include/TASKS.h"

ptask insert(ptask t1, ptask tasks)
{
	//printf("DEBUG : in function [%s]\n", __func__);
/*	while(tasks)
	{
		tasks = tasks->next;
	}
	if(tasks == NULL)
	{
		tasks = (ptask)malloc(sizeof(task));
		strcpy(tasks->name, t1->name);
		strcpy(tasks->description, t1->description);
		tasks->next= NULL;
	}*/
	t1->next = tasks;
	return t1;
	
}

int search_function(char *task, ptask tasks)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	int i=0;
	ptask tasks1 = tasks;
	while(tasks1 != NULL)
	{
		if(tasks1->name == task)
			return i;
		else
		{
			tasks1 = tasks1->next;
			i++;
		}
	}
	return -1;
}

ptask tremove(ptask t1, ptask tasks)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	int until =  search_function(t1->name, tasks);
	int i = 0;
	ptask tasks1 = tasks;
	for(;i<until;i++)
	{
		tasks1 = tasks1->next;
	}
	tasks = tasks1->next;
	
	return tasks;
}

void save(ptask tasks)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	int i = 1;
	ptask tasks1 = tasks;
	if (tasks1 == NULL)
	{
		printf ("tasks1 is empty\n");
	}
	while(tasks1->next)
	{
		printf("%d: %s, %s\n",i, tasks1->name, tasks1->description);
		tasks1 = tasks1->next;
		i++;
	}
}


void tprint(ptask tasks)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	int i = 1;
	
	while(tasks->next)
	{
		printf("location [%d] : name [%s] - desc [%s]\n",i, tasks->name, tasks->description);
		tasks = tasks->next;
		i++;
	}
	if (tasks == NULL)
	{
		printf ("tasks is empty\n");
	}
}
