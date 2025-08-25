#ifndef CMD_HANDLER
#define CMD_HANDLER

typedef int (*command_fnc)();
typedef struct {
    int name;
    command_fnc func;
} Command;
typedef enum {
    CMD, // command
    TL, // TaskLists
    GTL, // GET TaskLists
    CTL, // CREATE  TaskList
    DTL, // DELETE-TaskList READY
    DDTL, // DO DELETE TaskList
    UTL, // UPDATE TaskList
    TSKS, // Tasks 
    TLS, // TaskList SPECIFIED
    GTS, // getTasks
    ETLID, // expect taskList ID
    CT, // createTask
    UT, // updateTask
    DT, // deleteTask
    ERR // ERROR
} State;

int handle_command(int argc, char* argv[]);
int deleteTaskList();
int getTaskLists();
int getTaskListById();
int createTaskList();
int updateTaskList();
int getTasksForTaskList();
int error_handler();
int deleteTask();
int updateTask();
int createTask();
void dispatch(State s);


#endif