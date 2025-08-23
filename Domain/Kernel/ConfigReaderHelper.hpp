#pragma once
#include "SimpleIni.h"
#include <iostream>
namespace Domain::kernel{
class ConfigReaderHelper
{
public:
    const char *dbHost;
    const char *dbPort;
    const char *dbUser;
    const char *dbPassword;
    const char *dbName;
    const char *logPath;
    const char *logLevel;
    const int *serverPort;

    ConfigReaderHelper()
    {
        CSimpleIniA ini;
        ini.SetUnicode();
        SI_Error rc = ini.LoadFile("config.ini");
        if (rc < 0)
        {
            std::cerr << "No se pudo abrir config.ini\n";
        }

        this->dbHost = ini.GetValue("database", "host", "localhost");
        this->dbPort = ini.GetValue("database", "port", "5432");
        this->dbUser = ini.GetValue("database", "user", "crisostomo");
        this->dbPassword = ini.GetValue("database", "password", "psql");
        this->dbName = ini.GetValue("database", "name", "crisostomo");
        this->logPath = ini.GetValue("database", "name", "crisostomo");
        this->logLevel = ini.GetValue("logs", "level", "debug");
        this->logPath  = ini.GetValue("logs", "path", "/logs");
        
        
    }
};
};
// int main()
// {
//     CSimpleIniA ini;
//     ini.SetUnicode(); // si quieres soporte UTF-8
//     SI_Error rc = ini.LoadFile("config.ini");
//     if (rc < 0)
//     {
//         std::cerr << "No se pudo abrir config.ini\n";
//         return 1;
//     }

//     // Leer valores
//     const char *dbHost = ini.GetValue("database", "host", "localhost");
//     const char *dbPort = ini.GetValue("database", "port", "5432");
//     const char *apiUrl = ini.GetValue("api", "url", "");

//     std::cout
//         << "DB Host: " << dbHost << "\n"
//         << "DB Port: " << dbPort << "\n"
//         << "API URL: " << apiUrl << "\n";

//     return 0;
// }
