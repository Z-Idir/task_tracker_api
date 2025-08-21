#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cJSON.h>

#include "cmd_handler.h"

#define API_BASE "http://192.168.80.1:8080/api/task-lists"




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