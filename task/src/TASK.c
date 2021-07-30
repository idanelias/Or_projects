#include "../include/TASK.h"
 
ptask create_new_task(char *tname ,char *description)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	ptask t1;
	t1 = (ptask)malloc(sizeof(task));
	strcpy(t1->name,tname);
	strcpy(t1->description, description);	
	t1->next = NULL;
}

void edit_existing_task(ptask task1,char *name ,char *description)
{
	//printf("DEBUG : in function [%s]\n", __func__);
	strcpy(task1->description, description);
	strcpy(task1->name ,name);
}

