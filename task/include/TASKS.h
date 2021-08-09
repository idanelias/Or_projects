#ifndef TASKS
#define TASKS

ptask insert(ptask t1, ptask tasks);
ptask tremove(ptask t1, ptask tasks);
int search_function(char *task, ptask tasks);
void save(ptask tasks);
void tprint(ptask tasks);

#endif
