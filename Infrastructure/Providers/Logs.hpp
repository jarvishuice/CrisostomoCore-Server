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

enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:
    // Obtiene la instancia global
    static Logger &instance()
    {
        static Logger _instance;
        return _instance;
    }

    // Inicializa el logger: fichero, nivel mínimo y salida a consola
    void init(const std::string &filename,
              LogLevel minLevel = LogLevel::DEBUG,
              bool consoleOutput = true)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (outFile_.is_open())
            outFile_.close();

        outFile_.open(filename, std::ios::app);
        if (!outFile_)
            throw std::runtime_error("No se pudo abrir log: " + filename);

        minLevel_ = minLevel;
        consoleOutput_ = consoleOutput;
    }

    // Log genérico
    void log(LogLevel level, const std::string &message)
    {
        if (level < minLevel_)
            return;

        std::string ts = timestamp();
        std::string lvl = levelToString(level);
        std::ostringstream full;
        full << "[" << ts << "]"
             << "[" << lvl << "] "
             << message << "\n";

        std::lock_guard<std::mutex> lock(mutex_);
        if (consoleOutput_)
            std::cout << full.str();
        if (outFile_)
            outFile_ << full.str();
    }

    // Helpers por nivel
    void debug(const std::string &msg) { log(LogLevel::DEBUG, msg); }
    void info(const std::string &msg) { log(LogLevel::INFO, msg); }
    void warn(const std::string &msg) { log(LogLevel::WARN, msg); }
    void error(const std::string &msg) { log(LogLevel::ERROR, msg); }

private:
    Logger() = default;
    ~Logger()
    {
        if (outFile_.is_open())
            outFile_.close();
    }
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    // Convierte nivel a texto
    static std::string levelToString(LogLevel lvl)
    {
        switch (lvl)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO ";
        case LogLevel::WARN:
            return "WARN ";
        case LogLevel::ERROR:
            return "ERROR";
        }
        return "UNKWN";
    }

    // Timestamp formato YYYY-MM-DD HH:MM:SS
    static std::string timestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                          now.time_since_epoch()) %
                      1000;
        auto t_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &t_c);
#else
        localtime_r(&t_c, &tm);
#endif

        std::ostringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
           << "." << std::setfill('0') << std::setw(3) << millis.count();
        return ss.str();
    }

    std::ofstream outFile_;
    LogLevel minLevel_ = LogLevel::DEBUG;
    bool consoleOutput_ = true;
    std::mutex mutex_;
};

#endif // LOGGER_HPP
