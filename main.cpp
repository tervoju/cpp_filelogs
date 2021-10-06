#include "FileRotator.h"
#include <string.h>

class MyLogger
{
public:
    MyLogger() : mFileRotator(1024 /*bytes*/, "pc_.txt", 30)
    {
        mFileRotator.Open();
    }

    ~MyLogger()
    {
        mFileRotator.Close();
    }

    int Log(char *str) 
    {
        //
        // customize your log message like adding date, time, etc. here
        //
        std::string logStr = std::string("Info:") + str + std::string("\n");
        return mFileRotator.Write(logStr.c_str());
}

private:
    FileRotator mFileRotator;
};

int main()
{
    MyLogger myLogger;
    int i = 0;

    while (i < 10000) {
        myLogger.Log("Sample log text");
        i++;
    }
    return 0;
}