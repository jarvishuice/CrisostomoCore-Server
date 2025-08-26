cmake_minimum_required(VERSION 3.10)
project(Presentation)

# Crea la biblioteca compartida 'presentation'.
# Lista aquí todos los archivos .cpp de tu capa de presentación.
add_library(presentation SHARED
    Controllers/UserController.cpp
    Controllers/AuthController.cpp
    # Puedes añadir más archivos .cpp de esta capa aquí.
)

# Vincula la biblioteca 'presentation' a sus dependencias.
target_link_libraries(presentation PRIVATE infrastructure application domain)

# Define los directorios de inclusión para las cabeceras de esta capa.
target_include_directories(presentation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Controllers
    ${CMAKE_CURRENT_SOURCE_SDIR}/Services
)