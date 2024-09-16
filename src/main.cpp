#include <stdio.h>
#include "internet.h"
#include <stdlib.h>


int main() {
    printf("Hello, World!\n");
    bool connected = internet_connected();
    printf("Internet connected: %s\n", connected ? "true" : "false");
    return 0;
}
