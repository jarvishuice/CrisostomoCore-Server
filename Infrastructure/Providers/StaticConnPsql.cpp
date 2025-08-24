
#include "StaticConnPsql.hpp"

// Una sola definición de cada miembro static:
std::queue<pqxx::connection*> StaticConnPoolPsql::connections;
std::mutex StaticConnPoolPsql::mtx;
std::condition_variable StaticConnPoolPsql::cv;
bool StaticConnPoolPsql::initialized = false;
// aquí implementas los métodos de StaticConnPoolPsql…

