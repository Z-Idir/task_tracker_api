# Task tracker command line client
This project is a cmd tool that will interface with the task tracking api, it supports some fairly simple commands that will aloow you to perform CRUD operations on task lists and tasks.
this project was created in c using curl http client and cjson for parsing json responses from the api

# Structure
First of all we have the main file : cmd_handler.c which handles the command parsing and handler dispatch and response handling which makes it the controller/view layer, task_tracker.c is the service layer handling http calls to the server
Note : the controller/view layer for now is merged because json parsing and formating is still not in place but once that's in progress the two layer will be separated.

# Compiling and running
We have a build.bat and run.bat files, the build will simply compile and link the project files whereas run.bat will build and run this will only be used in developement for convenience and not in prod since we dont want to recompile the code each time we run it, the libraries used are in the lib folder and u need not to worry about them unless there are some compatibilty issues on whatever machine u are running on and in that case please post an issue and i will look into it even if you figure it out on your own it will be much appreciated if you report any problem



# Future features
- listing upcoming tasks; ex : <cmd> taskLists show upcoming -l <time frame>
- use my own http client from the http server project
- use my own json parser
- NOTE : this project must be included under the make it from scratch project