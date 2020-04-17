#include "AppLogger.h"

#include <cstdarg>
#include <iostream>
#include <vector>

using namespace Logging;

AppLogger::~AppLogger()
{
    if (FileLogging) {
        if (LogFile) {
            LogFile.close();
        }
    }
}

void AppLogger::SetTag(std::string tag)
{
    Tag += tag;
}

void AppLogger::SetLogFile(std::string fileName)
{
    LogFile.open(fileName, std::ofstream::out | std::ofstream::app);
    FileLogging = true;
}

void AppLogger::Msg(const std::string fmt, ...)
{
    std::vector<char> buff(1024); 	// include terminator space

    va_list args;
    va_start(args, fmt);

    vsnprintf(&buff[0], buff.size(), fmt.c_str(), args);

    if (FileLogging) {
        LogFile << this->GetTimestamp().count() << ": " << Tag << "\t: " << buff.data() << std::endl;
    }

    std::cout << this->GetTimestamp().count() << ": " << Tag << "\t: " << buff.data() << std::endl;
    va_end(args);
}

void AppLogger::Msg(const char* fmt, ...)
{
    char acText[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(acText, fmt, args);
    va_end(args);

    std::cout << this->GetTimestamp().count() << ": " << Tag << "\t: " << acText << std::endl;
}

milliseconds AppLogger::GetTimestamp() const
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}
