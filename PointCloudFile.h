#pragma once
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



class PointCloudFile
{
public:
    static int objectCount;
    PointCloudFile();
    PointCloudFile(std::string title, int maxFileCnt);
    void writeToFile(std::string);
    void closeFile();
    virtual ~PointCloudFile()
    {
        if (pointcloudfile)
        {
            pointcloudfile.close();
        }
    }

private:
    std::ofstream pointcloudfile;
    int maxFileCnt;
    int file_number;
    std::string file_name;
};