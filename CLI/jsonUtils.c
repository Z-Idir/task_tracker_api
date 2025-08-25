#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jsonUtils.h"

int main(){
    JsonContainer **json ;
    createJsonObject(json, "name","idir");
    printf("after creation");
    printJson(*json);
    return 0;
}

int createJsonObject(JsonContainer **json ,char *name, char *value ){

    *json = (JsonContainer*) malloc(sizeof **json);
    if(json == NULL){
        perror("malloc failure");
        return 1;
    }
    (*json)->field_name = name;
    (*json)->field_value = value;
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
        printf("json object refrence is null\n");
        return;
    }
    printf("{");
    JsonContainer *iter = head;
    while (iter->next != NULL){
        printf("\"%s\":\"%s\",",iter->field_name,iter->field_value);
        iter = iter->next;
    }
    
}