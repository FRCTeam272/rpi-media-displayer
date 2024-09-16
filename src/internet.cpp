#include <stdlib.h>
#include "internet.h"
#include <stdio.h>
/**
 * @brief Check if the internet is connected
 * @return true if connected, false otherwise
 */
bool internet_connected() {
    int result = system("ping -c 1 -W 1 google.com > /dev/null 2>&1");
    return result == 0;
}

bool download_file(const char* url, const char* destination) {
    char command[256];
    snprintf(command, sizeof(command), "curl -o %s %s", destination, url);
    int result = system(command);
    return result == 0;
}