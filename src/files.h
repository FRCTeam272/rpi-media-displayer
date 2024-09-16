#include <vector>
#include <string>
#ifndef FILES_H
#define FILES_H

int create_folder(const char* folder_name);
std::vector<std::string> list_files(const char* folder_name);
#endif // FILES_H