#include "../include/TASK.h"
#include "../include/TASKS.h"

void main()
{
	ptask t1 = NULL;
	ptask tasks = (ptask)malloc(sizeof(task));
	char description[2048];
	char name[1000];
	int i=0;
	for(;i<3;i++)
	{
		printf("Enter new task name:");
		scanf("%s",name);
		printf("Enter task [%s] description:",name);
		scanf("%s",description);
		t1 = create_new_task(name,description);
		tasks = insert(t1, tasks);
		save(tasks);

		if(i==2)
		{
			printf("Going to delete task #2\n");
			tasks = tremove(t1,tasks);
		}
		/*if(i==1)
			edit_existing_task(t1 ,"123" ,"123");
		printf("t1->name=[%s] , t1->description[%s]\n", t1->name, t1->description);
		printf("%d",i);*/
		
	}

	save(tasks);
	
}
