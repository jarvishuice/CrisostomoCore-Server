#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }

    void init(const std::string& filename,
              LogLevel minLevel  = LogLevel::DEBUG,
              bool consoleOutput = true)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (ofs_.is_open()) ofs_.close();

        ofs_.open(filename, std::ios::app);
        if (!ofs_)
            throw std::runtime_error("Logger: no pudo abrir archivo " + filename);

        minLevel_     = minLevel;
        consoleOutput_= consoleOutput;
    }

    void log(LogLevel level, const std::string& message) {
        if (level < minLevel_) return;

        // Generar timestamp
        auto now   = std::chrono::system_clock::now();
        auto ms    = std::chrono::duration_cast<std::chrono::milliseconds>(
                         now.time_since_epoch()) % 1000;
        auto tc    = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
    #ifdef _WIN32
        localtime_s(&tm, &tc);
    #else
        localtime_r(&tc, &tm);
    #endif

        std::ostringstream full;
        full << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
             << "." << std::setw(3) << std::setfill('0') << ms.count()
             << "][" << levelToString(level) << "] "
             << message << "\n";

        std::lock_guard<std::mutex> lk(mutex_);

        if (consoleOutput_)
            std::cout << full.str();

        if (ofs_.is_open()) {
            ofs_ << full.str();
            ofs_.flush();
        } else {
            std::cerr << "Logger: archivo NO abierto para escritura\n";
        }
    }

    void debug(const std::string& msg)            { log(LogLevel::DEBUG, msg); }
    void info (const std::string& msg)            { log(LogLevel::INFO,  msg); }
    void warn (const std::string& msg)            { log(LogLevel::WARN,  msg); }
    void error(const std::string& msg)            { log(LogLevel::ERROR, msg); }

private:
    Logger()  = default;
    ~Logger() { if (ofs_.is_open()) ofs_.close(); }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static const char* levelToString(LogLevel lvl) {
        switch (lvl) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO : return "INFO ";
            case LogLevel::WARN : return "WARN ";
            case LogLevel::ERROR: return "ERROR";
        }
        return "UNKWN";
    }

    std::ofstream ofs_;
    LogLevel      minLevel_      = LogLevel::DEBUG;
    bool          consoleOutput_ = true;
    std::mutex    mutex_;
};

#endif // LOGGER_HPP
