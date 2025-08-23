#include "SimpleIni.h"
#include <iostream>

int main() {
    CSimpleIniA ini;
    ini.SetUnicode();          // si quieres soporte UTF-8
    SI_Error rc = ini.LoadFile("config.ini");
    if (rc < 0) {
        std::cerr << "No se pudo abrir config.ini\n";
        return 1;
   
    }


    // Leer valores
    const char* dbHost = ini.GetValue("database", "host",     "localhost");
    const char* dbPort = ini.GetValue("database", "port",     "5432");
    const char* apiUrl = ini.GetValue("api",      "url",      "");

    std::cout
        << "DB Host: " << dbHost << "\n"
        << "DB Port: " << dbPort << "\n"
        << "API URL: " << apiUrl << "\n";

    return 0;
}
