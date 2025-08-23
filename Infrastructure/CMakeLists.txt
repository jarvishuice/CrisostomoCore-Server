cmake_minimum_required(VERSION 3.10)
project(Infrastructure)

add_library(infrastructure SHARED 
    DAO/UserDAO.cpp
    Providers/StaticConnPsql.cpp
)

target_link_libraries(infrastructure PRIVATE domain pqxx pq)    


target_include_directories(infrastructure PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/DAO
    ${CMAKE_CURRENT_SOURCE_DIR}/Providers
)
link_directories(/usr/lib/x86_64-linux-gnu) 