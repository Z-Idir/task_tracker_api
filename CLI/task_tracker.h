#ifndef TASK_TRACKER
#define TASK_TRACKER





int sendGetTaskLists();
int sendDeleteTaskList(char *id);
int sendGetTaskList(char *id);
int sendPostTaskList(char *title, char *description);
int sendPatchTaskList(char *id, char *title, char *description);
int sendGetTasksForTaskList(char *id);

#endif