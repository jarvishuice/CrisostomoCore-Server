cmake_minimum_required(VERSION 3.10)
project(Infrastructure)

add_library(infrastructure SHARED 
    DAO/UserDAO.cpp
    DAO/CategoryDAO.cpp
    Providers/StaticConnPsql.cpp
   
)

target_link_libraries(infrastructure PRIVATE domain pqxx pq)    

# set_target_properties(infrastructure PROPERTIES
#   POSITION_INDEPENDENT_CODE ON
# )
target_include_directories(infrastructure PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/DAO
    ${CMAKE_CURRENT_SOURCE_DIR}/Providers
)
link_directories(/usr/lib/x86_64-linux-gnu) 