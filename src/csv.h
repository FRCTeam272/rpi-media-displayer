#ifndef CSV_H
#define CSV_H

#include<string>
#include<vector>

struct CSVData{
    std::string name;
    std::string url;
};

std::vector<CSVData> GetDataFromCsv(std::string filepath);

#endif