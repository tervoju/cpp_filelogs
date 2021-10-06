#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "PointCloudFile.h"



int PointCloudFile::objectCount = 0;

int main()
{

    int i = 0;
    int max_files = 30;
    int file_number = 0;

   
    while (i < 100)
    {
        PointCloudFile pcFile("PC_", 30);
        std::ostringstream sstr;
        sstr << i << " ";
        sstr << std::setw(12) << std::left << 0.001;
        sstr << std::setw(12) << std::left << 0.001;
        sstr << std::setw(12) << std::left << 0.001 << std::endl;

        pcFile.writeToFile(sstr.str());
        pcFile.closeFile();
        i++;
    }
    return 0;
}