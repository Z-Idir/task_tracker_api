#ifndef TASK_TRACKER
#define TASK_TRACKER





int sendGetTaskLists();
int sendDeleteTaskList(char *id);
int sendGetTaskList(char *id);
int sendPostTaskList(char *title, char *description);
int sendPutTaskList(char *id, char *title, char *description);

#endif