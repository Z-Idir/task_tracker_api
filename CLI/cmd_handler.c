#include <stdio.h>
#include <string.h>

#include "cmd_handler.h"
#include "task_tracker.h"

#define TOK_COUNT 6
#define S_COUNT 9
#define FINAL_STATE_COUNT 5



int number_of_handlers = FINAL_STATE_COUNT;
Command commands[] = {
    {GTL, getTaskLists},
    {DDTL, deleteTaskList},
    {CTL, createTaskList},
    {UTL, updateTaskList},
    {ERR, error_handler}
};

State final_states[] = {GTL,DDTL,ERR,CTL,UTL};
typedef struct {
    State final_state;
    int tokens_consumed;
} ParseResult;

typedef enum {
    TSKL,
    SHOW,
    DEL,
    ID,
    CR,
    UP
} Token;

typedef struct params {
    char *task_list_id;
    char *task_list_title;
    char *task_list_desc;
    int has_task_list_id;
    int has_task_list_title;
    int has_task_list_desc;
} Parameters;

Parameters params ;

char* id;

ParseResult finite_state_machine(int token_count,char* tokens[]);
Token map_string_to_token(char* string);

State transitions[S_COUNT][TOK_COUNT]= {
    {TL,ERR,ERR,ERR,ERR,ERR},
    {ERR,GTL,DTL,ERR,CTL,UTL},
    {ERR,ERR,ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,DDTL,ERR,ERR},
    {ERR,ERR,ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,ERR,ERR,ERR}
};
void print_transition_matrix(State matrix[S_COUNT][TOK_COUNT],int cols, int rows);
int parse_options(int argc, char *argv[], Parameters *output);
int is_final_state(State s);


int main(int argc, char* argv[]){    
    memset(&params, 0, sizeof(params));
    return handle_command(argc, argv);
}

int hello_handler(){
    printf("helloo there\n");
    return 0;
}
int bye_handler(){
    printf("bye bye ...\n");
    return 0;
}

int handle_command(int argc, char* argv[]){

    // we first need to parse the full command to see what state we landed on
    ParseResult parse_result = finite_state_machine(argc,argv);
    State reached_state = parse_result.final_state;
    // printf("reached this state : %d\n", reached_state);
    int tokens_consumed = parse_result.tokens_consumed;

    char **remaining_args = argv + tokens_consumed;
    int remaining_arg_count = argc - tokens_consumed;
    // for (int i = 0; i < argc - tokens_consumed; i++){
    //      printf("arg %d value: %s\n",i,remaining_args[i]);
    // }
    if(parse_result.tokens_consumed < argc){
        
        parse_options(remaining_arg_count,remaining_args,&params);
        // if (params.has_task_list_title){
        //     printf("we got the title : %s\n",params.task_list_title);
        // }
        // if (params.has_task_list_desc){
        //     printf("we got the description : %s\n",params.task_list_desc);
        // }
        // if (params.has_task_list_id){
        //     printf("we got the ID : %s\n",params.task_list_id);
        // }
        
    }

    // printf("tokens consumed : %d number of args %d\n", parse_result.tokens_consumed, argc);
    dispatch(reached_state);
    // Command command = {"hello",hello_handler};
    
    // printf("calling the hello handler\n");
    // command.func(argc,argv);

    return 0;
}

ParseResult finite_state_machine(int token_count,char* tokens[]){

    State initial = CMD;
    State current_state = CMD;
    int i = 1;
    while (!is_final_state(current_state) && current_state != ERR){
        if (current_state == ERR){
            printf("error state\n");
            break;
        }
    
        Token token = map_string_to_token(tokens[i]);
        // printf("iteration state is: %d\n",current_state);
        // printf("token is: %d literal %s\n",token,tokens[i]);
        // printf("next state is %d\n",transitions[current_state][token]);

        current_state = transitions[current_state][token];
        i++;
    }
    return (ParseResult){current_state,i};
}

Token map_string_to_token(char* string){
    Token token = ID;
    if (strcmp("taskLists",string) == 0){
        token = TSKL;
    }else if (strcmp("show",string) == 0){
        token = SHOW;
    }else if (strcmp("delete",string) == 0){
        token = DEL;
    }
    else if (strcmp("create",string) == 0){
        token = CR;
    }
    else if (strcmp("update",string) == 0){
        token = UP;
    }
    id = string;
    return token;
}
int error_handler(){
    printf("error: command is badddd\n");
}

void dispatch(State s){
    for (int i = 0; i < number_of_handlers; i++){
        if(commands[i].name == s){
            commands[i].func();
        }
    }
    
}

void print_transition_matrix(State matrix[S_COUNT][TOK_COUNT],int cols, int rows){
    printf("printing the matrix\n");
        for (int i = 0; i < TOK_COUNT; i++){
            printf("|");
            for (int j = 0; j < S_COUNT; j++){
                printf(" %d |",transitions[i][j]);
            }
            printf("\n ");
            for (int j = 0; j < S_COUNT; j++){
                printf("----");
            }
            printf("\n");
        }
}

int deleteTaskList(){
    sendDeleteTaskList(id);
    return 0;
}
int getTaskLists(){
    if(params.has_task_list_id){
        sendGetTaskList(params.task_list_id);
    }else{
        sendGetTaskLists();
    }
}
int createTaskList(){
    if(!params.has_task_list_title){
        fprintf(stderr,"title is needed to create a task list, specify it using -t <title>\n");
        return 1;
    }
    sendPostTaskList(params.task_list_title,params.task_list_desc);
    return 0;
}
int updateTaskList(){
    if(!params.has_task_list_id || !(params.has_task_list_title || params.has_task_list_desc)){
        fprintf(stderr,"error : title or description must be provided for update");
        return 1;
    }
    sendPatchTaskList(params.task_list_id,params.task_list_title,params.task_list_desc);
    printf("update handler\n");
    return 0;
}

int is_final_state(State s){
    for (int i = 0; i < FINAL_STATE_COUNT; i++){
        if (s == final_states[i]){
            return 1;
        }
    }
    return 0;
}

int parse_options(int argc, char *argv[], Parameters *output){
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-t")==0 && i + 1<argc){
            output->has_task_list_title = 1;
            output->task_list_title = argv[i + 1];
            i++;
        }else if(strcmp(argv[i], "-d")==0 && i + 1<argc){
            output->has_task_list_desc = 1;
            output->task_list_desc= argv[i + 1];
            i++;
        }
        else if(strcmp(argv[i], "-id")==0 && i + 1<argc){
            output->has_task_list_id = 1;
            output->task_list_id= argv[i + 1];
            i++;
        }
    }
    return 0;
}

