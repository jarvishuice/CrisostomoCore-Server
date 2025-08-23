
#pragma once
#include "StaticConnPsql.hpp"
#include <pqxx/pqxx>

class ConnectionRAII {
    pqxx::connection* conn;

public:
    // Constructor adquiere conexión
    ConnectionRAII() : conn(StaticConnPoolPsql::acquire()) {}

    // Destructor libera conexión automáticamente
    ~ConnectionRAII() {
        if (conn) {
            StaticConnPoolPsql::release(conn);
        }
    }

    // Acceso al puntero pqxx::connection como si fuera un puntero normal
    pqxx::connection* operator->() const { return conn; }
    pqxx::connection& operator*() const { return *conn; }

    // Prohibir copia para evitar dobles liberaciones
    ConnectionRAII(const ConnectionRAII&) = delete;
    ConnectionRAII& operator=(const ConnectionRAII&) = delete;

    // Permitir mover si se quiere
    ConnectionRAII(ConnectionRAII&& other) noexcept : conn(other.conn) {
        other.conn = nullptr;
    }
    ConnectionRAII& operator=(ConnectionRAII&& other) noexcept {
        if (this != &other) {
            if (conn) StaticConnPoolPsql::release(conn);
            conn = other.conn;
            other.conn = nullptr;
        }
        return *this;
    }
};
