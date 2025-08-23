// CrowLoggerAdapter.hpp
#pragma once

#include "Logs.hpp"          // Tu Logger singleton
#include <crow/logging.h>      // Crow::ILogHandler

class CrowLoggerAdapter : public crow::ILogHandler {
public:
    void log(const std::string& message,
             crow::LogLevel level) override
    {
        using CL = crow::LogLevel;

        // Opcional: Prepend nivel Crow a tu mensaje
        std::string prefixed = "[" + crowLevelToString(level) + "] " + message;

        switch (level) {
            case CL::Debug:    Logger::instance().debug(prefixed); break;
            case CL::Info:     Logger::instance().info (prefixed); break;
            case CL::Warning:  Logger::instance().warn (prefixed); break;
            case CL::Error:    Logger::instance().error(prefixed); break;
            case CL::Critical: Logger::instance().error(prefixed); break;
        }
    }

private:
    static std::string crowLevelToString(crow::LogLevel lvl) {
        switch (lvl) {
          case crow::LogLevel::Debug:    return "DEBUG";
          case crow::LogLevel::Info:     return "INFO";
          case crow::LogLevel::Warning:  return "WARN";
          case crow::LogLevel::Error:    return "ERROR";
          case crow::LogLevel::Critical: return "CRITICAL";
        }
        return "UNKNOWN";
    }
};
