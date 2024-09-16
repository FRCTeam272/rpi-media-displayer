#include "files.h"
#include <stdio.h>
#include <stdlib.h>


int create_folder(const char* folder_name) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s", folder_name);
    int result = system(command);
    return result == 0;
}

std::vector<std::string> list_files(const char* folder_name){
    std::vector<std::string> files;
        
    return files;
}