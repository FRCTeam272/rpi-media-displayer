#ifndef CSV_H
#define CSV_H

#include<string>
#include<vector>

using namespace std;

class CSVData
{

 public:
    std::string name;
    std::string url;

    CSVData(std::string name, std::string url)
    {
        this->name = name;
        this->url = url;
    }
};

vector<CSVData> GetDataFromCsv(string filepath);

#endif