#include <stdio.h>
#include "internet.h"
#include <stdlib.h>
#include "csv.h"
#include <iostream>

using namespace std;

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

        string filepath = "../data.csv";
        vector<CSVData> data = GetDataFromCsv(filepath);

        //here to spit out csv data as a test
        for(int i = 0; i < data.size(); i++){
            cout << data[i].name << " - " << data[i].url << endl;
        }

    } else {
        printf("No internet connection. Cannot download file.\n");
    }

    return 0;
}
