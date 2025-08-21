#include <stdio.h>
#include <string.h>

#include "cmd_handler.h"
#include "task_tracker.h"

#define TOK_COUNT 4
#define S_COUNT 6
#define FINAL_STATE_COUNT 3



int number_of_handlers = 3;
Command commands[] = {
    {GTL, sendGetTaskLists},
    {DDTL, deleteTaskList},
    {ERR, error_handler}
};

State final_states[] = {GTL,DDTL,ERR};
typedef struct {
    State final_state;
    int tokens_consumed;
} ParseResult;

typedef enum {
    TSKL,
    SHOW,
    DEL,
    ID
} Token;

char* id;

ParseResult finite_state_machine(int token_count,char* tokens[]);
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

int is_final_state(State s);


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
    ParseResult parse_result = finite_state_machine(argc,argv);
    State reached_state = parse_result.final_state;
    printf("reached this state : %d\n", reached_state);
    
    printf("tokens consumed : %d number of args %d\n", parse_result.tokens_consumed, argc);
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
        printf("iteration state is: %d\n",current_state);
        printf("token is: %d literal %s\n",token,tokens[i]);

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

int is_final_state(State s){
    for (int i = 0; i < FINAL_STATE_COUNT; i++){
        if (s == final_states[i]){
            return 1;
        }
    }
    return 0;
}