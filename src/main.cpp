#include <stdio.h>
#include "internet.h"
#include <stdlib.h>


int main() {
    printf("Hello, World!\n");
    bool connected = internet_connected();
    printf("Internet connected: %s\n", connected ? "true" : "false");

    if (connected) {
        const char* url = "https://raw.githubusercontent.com/FRCTeam272/rpi-media-displayer/check_internet/data.csv";
        const char* destination = "data.csv";
        if (download_file(url, destination)) {
            printf("File downloaded successfully to %s\n", destination);
        } else {
            printf("Failed to download file from %s\n", url);
        }
    } else {
        printf("No internet connection. Cannot download file.\n");
    }

    return 0;
}
