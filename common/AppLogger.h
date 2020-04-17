#pragma once

#include <chrono>
#include <string>
#include <memory>
#include <fstream>
#include <map>

using namespace std::chrono;

#define SPDLOG_LEVEL_TRACE 		0
#define SPDLOG_LEVEL_DEBUG 		1
#define SPDLOG_LEVEL_INFO 		2
#define SPDLOG_LEVEL_WARN 		3
#define SPDLOG_LEVEL_ERROR 		4
#define SPDLOG_LEVEL_CRITICAL 	5
#define SPDLOG_LEVEL_OFF 		6

// Log level enum
namespace level {
enum class level_enum
{
    trace = SPDLOG_LEVEL_TRACE,
    debug = SPDLOG_LEVEL_DEBUG,
    info = SPDLOG_LEVEL_INFO,
    warn = SPDLOG_LEVEL_WARN,
    err = SPDLOG_LEVEL_ERROR,
    critical = SPDLOG_LEVEL_CRITICAL,
    off = SPDLOG_LEVEL_OFF,
    n_levels
};
}

namespace Logging {

class AppLogger
{
public:
    AppLogger() = default;
	
    AppLogger(const AppLogger&) = delete;
    AppLogger& operator=(const AppLogger&) = delete;
    AppLogger(AppLogger&&) = delete;
    AppLogger& operator=(AppLogger&&) = delete;

    ~AppLogger();
	
    void	SetTag(std::string tag);
    void 	SetLogFile(std::string fileName);
	
    void        Msg(const std::string fmt, ...);
    void        Msg(const char* _log, ...);

private:
    milliseconds    GetTimestamp() const;
    bool            FileLogging;
    std::ofstream   LogFile;
    std::string     Tag;
};
}
