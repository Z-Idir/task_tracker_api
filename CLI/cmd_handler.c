#include <stdio.h>
#include <string.h>

#include "cmd_handler.h"
#include "task_tracker.h"

#define TOK_COUNT 4
#define S_COUNT 6



int number_of_handlers = 3;
Command commands[] = {
    {GTL, sendGetTaskLists},
    {DDTL, deleteTaskList},
    {ERR, error_handler}
};

typedef enum {
    TSKL,
    SHOW,
    DEL,
    ID
} Token;

char* id;

State finite_state_machine(int token_count,char* tokens[]);
Token map_string_to_token(char* string);

State transitions[S_COUNT][TOK_COUNT]= {
    {TL,ERR,ERR,ERR},
    {ERR,GTL,DTL,ERR},
    {ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,DDTL},
    {ERR,ERR,ERR,ERR},
    {ERR,ERR,ERR,ERR}
};
void print_transition_matrix(State matrix[S_COUNT][TOK_COUNT],int cols, int rows);


int main(int argc, char* argv[]){    
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
    State reached_state = finite_state_machine(argc,argv);
    printf("reached this state : %d\n", reached_state);
    dispatch(reached_state);
    // Command command = {"hello",hello_handler};
    
    // printf("calling the hello handler\n");
    // command.func(argc,argv);

    return 0;
}

State finite_state_machine(int token_count,char* tokens[]){

    State initial = CMD;
    State current_state = CMD;
    for (int i = 1; i < token_count; i++){
        if (current_state == ERR){
            printf("error state\n");
            break;
        }
    
        Token token = map_string_to_token(tokens[i]);
        printf("iteration state is: %d\n",current_state);
        printf("token is: %d literal %s\n",token,tokens[i]);

        current_state = transitions[current_state][token];
    }
    printf("return\n");
    return current_state;
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