#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jsonUtils.h"

int main(){
    JsonContainer *json = NULL ;
    createJsonObject(&json, "name","idir");
    addField(&json,"age","66");
    printJson(json);
    return 0;
}

int createJsonObject(JsonContainer **json){

    *json = malloc(sizeof **json);
    if(*json == NULL){
        perror("malloc failure");
        return 1;
    }
    (*json)->field_name = NULL;
    (*json)->value.
    (*json)->next = NULL;
    return 0;
}

int addField(JsonContainer **head,char *name, char *value){
    if(head == NULL){
        return createJsonObject(head,name,value);
    }
    JsonContainer *nextField ;
    int ret = createJsonObject(&nextField, name, value);
    if(ret != 0){
        return ret;
    }
    JsonContainer *p = *head;
    while (p->next !=NULL){
        p = p->next;
    }
    p->next = nextField;
    return 0;
}

void printJson(JsonContainer *head){
    if(head == NULL){
        printf("json object reference is null\n");
        return;
    }
    printf("{");
    JsonContainer *iter = head;
    while (iter != NULL){
        printf("\"%s\":\"%s\",",iter->field_name,iter->field_value);
        iter = iter->next;
    }
    printf("\b}");
    
}

int addStringValue(JsonContainer **json ,char *name, char *value ){
    return 0;
}
int addNumberValue(JsonContainer **json ,char *name, double value ){
    return 0;
}