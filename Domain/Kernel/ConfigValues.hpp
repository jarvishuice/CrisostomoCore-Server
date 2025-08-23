#pragma once
#include "ConfigReaderHelper.hpp"

namespace Domain::Kernel
{

    class ConfigValues
    {

    private:
        ConfigValues() = delete;

    public:
        inline static std::string DB_HOST;
        inline static std::string DB_PORT;
        inline static std::string DB_USER;
        inline static std::string DB_PASSWORD;
        inline static std::string DB_NAME;
        inline static std::string LOG_PATH;
        inline static std::string LOG_LEVEL;
        inline static int SERVER_PORT;

        static void start()
        {
            Domain::kernel::ConfigReaderHelper helper = Domain::kernel::ConfigReaderHelper();
            DB_HOST = helper.dbHost;
            DB_PORT = helper.dbPort;
            DB_USER = helper.dbUser;
            DB_PASSWORD = helper.dbPassword;
            DB_NAME = helper.dbName;
            LOG_PATH = helper.logPath;
            LOG_LEVEL = helper.logLevel;
            // SERVER_PORT = (int)helper.serverPort;
        }
    };

}