#ifndef TASK
#define TASK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct task
{
	char description[2048];
	char name[1000];
	struct task *next;
} *ptask ,task;

ptask create_new_task(char *task ,char *description);
void edit_existing_task(ptask task1 ,char *name ,char *description);

#endif
