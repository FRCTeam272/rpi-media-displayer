#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include "csv.h"

using namespace std;

vector<string> SplitString(string text, char delimiter)
{
    stringstream ss(text);

    string token;
    vector<string> tokens;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<CSVData> GetDataFromCsv(string filepath)
{
    fstream fin;

    fin.open(filepath, ios::in);

    vector<CSVData> fileData;

    vector<string> row;
    string line;

    while(getline(fin, line)){
        //clear var used to temp store row data
        row.clear();

        row = SplitString(line, ',');

        if(row.size() >= 2){
            CSVData rowData;
            rowData.name = row[0];
            rowData.url = row[1];
            fileData.push_back(rowData);
        }
    }

    fin.close();

    return fileData;
}