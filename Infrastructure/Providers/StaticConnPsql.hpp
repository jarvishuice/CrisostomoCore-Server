#pragma once
#include <pqxx/pqxx>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Logs.hpp"
class StaticConnPoolPsql {
private:
    
    static std::queue<pqxx::connection*> connections;
    static std::mutex mtx;
    static std::condition_variable cv;
    static bool initialized;
    
    StaticConnPoolPsql() = delete; // Evitar instanciación

public:
    static void initialize(const std::string& conninfo, size_t poolSize) {
        auto& log = Logger::instance();
        log.info("iniciando el pool de conexiones hacia  DB  ") ;
        std::lock_guard<std::mutex> lock(mtx);
        if (!initialized) {
            for (size_t i = 0; i < poolSize; ++i) {
                pqxx::connection* conn = new pqxx::connection(conninfo + " application_name=microservicio_user_dev_aws");
                connections.push(conn);
               log.info("conexion #"+std::to_string(i)+" abierta con exito") ;

            }
            initialized = true;
            log.info("pool de conexion inicado de manera correcta");
        }
    }

    static pqxx::connection* acquire() {
        auto& log = Logger::instance();
        std::unique_lock<std::mutex> lock(mtx);

        while (connections.empty()) {
           log.info("no tenemos conexiones disponibles en el pool");
            cv.wait(lock);  // espera hasta que haya conexión disponible
        }
        pqxx::connection* conn = connections.front();
        connections.pop();
        
        return conn;
    }

    static void release(pqxx::connection* conn) {
        auto& log = Logger::instance();
        std::lock_guard<std::mutex> lock(mtx);
        connections.push(conn);
        log.info("Conexion devuelta al pool");
        cv.notify_one();
    }

    static void shutdown() {
        std::lock_guard<std::mutex> lock(mtx);
        auto& log = Logger::instance();
        while (!connections.empty()) {
            auto conn = connections.front();
            connections.pop();
            conn->disconnect();
            log.info("Cerrando conexiones del pool");
            delete conn;
        }
        initialized = false;
        log.info("Conexiones cerradas conexito ");
    }
};

// Definiciones estáticas
std::queue<pqxx::connection*> StaticConnPoolPsql::connections;
std::mutex StaticConnPoolPsql::mtx;
std::condition_variable StaticConnPoolPsql::cv;
bool StaticConnPoolPsql::initialized = false;
