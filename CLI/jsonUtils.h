#ifndef JSON_UTILS
#define JSON_UTILS


typedef enum {
    JSON_STRING,
    JSON_NUMBER
} JsonType;
typedef struct JsonContainer {
    char *field_name;
    JsonType type;
    union {
        char *string_value;
        double number_value;
    } value;
    
    struct JsonContainer *next;

} JsonContainer;


int createJsonObject(JsonContainer **json);
int addStringValue(JsonContainer **json ,char *name, char *value );
int addNumberValue(JsonContainer **json ,char *name, double value );
int addField(JsonContainer **json,char *name, char *value);
void printJson(JsonContainer *head);


#endif