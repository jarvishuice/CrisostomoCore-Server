cmake_minimum_required(VERSION 3.10)
project(CrisostomoCore)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_subdirectory(Domain)
# add_subdirectory(Application)
add_subdirectory(Infrastructure)
# add_subdirectory(Presentation)
link_directories(/usr/lib/x86_64-linux-gnu)
# Crea el ejecutable principal en la raíz
add_executable(api_rest_app app.cpp)

# Enlaza el ejecutable principal con todas las bibliotecas compartidas
target_link_libraries(api_rest_app PRIVATE infrastructure jsoncpp    # Agrega -ljsoncpp
    pqxx       # Agrega -lpqxx
    pq )        # Agrega -lpq) #application presentation)