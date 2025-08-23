cmake_minimum_required(VERSION 3.10)
project(Infrastructure)

add_library(infrastructure SHARED 
    DAO/UserDAO.cpp
    Providers/PostgresProvider.cpp
)

target_link_libraries(infrastructure PRIVATE domain)

target_include_directories(infrastructure PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/DAO
    ${CMAKE_CURRENT_SOURCE_DIR}/Providers
)