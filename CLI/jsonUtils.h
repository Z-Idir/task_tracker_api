#ifndef JSON_UTILS
#define JSON_UTILS


typedef struct JsonContainer {
    char *field_name;
    char *field_value;
    struct JsonContainer *next;
} JsonContainer;

int createJsonObject(JsonContainer **json ,char *name, char *value );
int addField(JsonContainer **json,char *name, char *value);
void printJson(JsonContainer *head);


#endif