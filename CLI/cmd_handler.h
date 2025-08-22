#ifndef CMD_HANDLER
#define CMD_HANDLER

typedef int (*command_fnc)();
typedef struct {
    int name;
    command_fnc func;
} Command;
typedef enum {
    CMD,
    TL,
    GTL,
    CTL,
    DTL,
    DDTL,
    UTL,
    ERR
} State;

int handle_command(int argc, char* argv[]);
int deleteTaskList();
int getTaskLists();
int getTaskListById();
int createTaskList();
int updateTaskList();
int error_handler();
void dispatch(State s);


#endif