#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cJSON.h>

#include "cmd_handler.h"

#define API_BASE "http://192.168.80.1:8080/api/task-lists"

typedef struct {
    long status_code;
    char *body;
} HttpResponse;

HttpResponse http_request(const char *method, const char *url, const char *body);


size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    // This is called by libcurl when data is received
    printf("%.*s", (int)(size * nmemb), (char *)ptr);
    return size * nmemb;
}

int sendGetTaskLists(){
    CURL *curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,API_BASE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr,"failed to perform fetch %s\n",curl_easy_strerror(res));
        }else{

        }
        curl_easy_cleanup(curl);
    }
    return 0;
}
int sendGetTaskList(char *id){
    char endpoint[1000];
    strcat(endpoint,API_BASE);
    strcat(endpoint,"/");
    strcat(endpoint,id);
    HttpResponse res =  http_request("GET",endpoint,NULL);
    printf("fetched : %s",res.body);
    return 0;
}
int sendDeleteTaskList(char *id){
    CURL *curl = curl_easy_init();
    if(curl){
        char endpoint[300] = API_BASE;
        strcat(endpoint,"/");
        strcat(endpoint,id);
        curl_easy_setopt(curl,CURLOPT_URL, endpoint);
        curl_easy_setopt(curl,CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr,"failed to perform fetch %s\n",curl_easy_strerror(res));
        }else{
            printf("taskList with id :%s deleted\n",id);
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}

static size_t general_write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    HttpResponse *resp = (HttpResponse *) userp;

    // grow buffer
    resp->body = realloc(resp->body, (resp->body ? strlen(resp->body) : 0) + realsize + 1);
    if (resp->body == NULL) return 0; // out of memory

    if (!resp->body[0]) resp->body[0] = '\0'; // ensure null term for strcat
    strncat(resp->body, contents, realsize);

    return realsize;
}

HttpResponse http_request(const char *method, const char *url, const char *body) {
    printf("method is %s\n",method);
    printf("body is %s\n",body);
    HttpResponse resp;
    resp.status_code = 0;
    resp.body = calloc(1, 1); // start empty string

    CURL *curl = curl_easy_init();
    if (!curl) return resp;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, general_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

    if (strcmp(method, "POST") == 0) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (body) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    } else if (strcmp(method, "DELETE") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    } else if (strcmp(method, "PUT") == 0) {
        printf("matched to the put method\n");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (body) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    } 


    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp.status_code);
    } else {
        fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    return resp;
}

int sendPostTaskList(char *title, char *description){
    char jsonBody[510] ;
    snprintf(jsonBody,sizeof(jsonBody),"{ \"title\" : \"%s\" , \"description\" : \"%s\" }",title, description);
    HttpResponse res = http_request("POST",API_BASE,jsonBody);
    printf("fetched : %s\n",res.body);
    return 0;
}
int sendPutTaskList(char *id, char *title, char *description){
    char jsonBody[1000];
    size_t remaining = sizeof(jsonBody);
    char *ptr = jsonBody;
    int written = snprintf(ptr,remaining, "{");
    ptr += written;
    remaining -= written;
    printf("json %s\n",jsonBody);
    int first = 0;
    if(title){
        written = snprintf(ptr,remaining," \"title\" : \"%s\"",title);
        ptr += written;
        remaining -= written;
        first = 1;
    }
    if(description){
        char *comma = first ? "," : "";
        written = snprintf(ptr,remaining," %s \"description\" : \"%s\"",comma,description);
        ptr += written;
        remaining -= written;
    }
    written = snprintf(ptr,remaining, "}");
    ptr += written;
    remaining -= written;

    char endpoint[200];
    snprintf(endpoint,sizeof(endpoint),"%s/%s",API_BASE,id);
    HttpResponse res = http_request("PUT",endpoint,jsonBody);

    printf("fetched: %s\n",res.body);
    return 0;
}

