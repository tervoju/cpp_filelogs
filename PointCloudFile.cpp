#include "PointCloudFile.h"


PointCloudFile::PointCloudFile(std::string title="PC_", int maxFileCnt = 100)
{
         // 1) open file
        // next file    pc_001 , pc_002, ..., pc_099 depends max on amount of files
        // file is existing -> overwrite

        file_number = ++objectCount % maxFileCnt;
        if (objectCount >= maxFileCnt)
            objectCount = 0;

        auto fileNro_string = boost::str(boost::format("%03d") % file_number);
        //std::string full_path = "./pointclouds/" + (std::string)title + fileNro_string + ".txt";
        std::string full_path = (std::string)title + fileNro_string + ".txt";
        pointcloudfile.open(full_path);

}

void PointCloudFile::writeToFile(std::string str)
{
     pointcloudfile << str << std::endl;
}

void PointCloudFile::closeFile()
{
	pointcloudfile.close();
}