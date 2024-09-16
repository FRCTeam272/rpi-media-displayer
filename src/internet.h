#ifndef INTERNET_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INTERNET_H

bool internet_connected();
bool download_file(const char* url, const char* destination);
#endif // INTERNET_H