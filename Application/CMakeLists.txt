cmake_minimum_required(VERSION 3.10)
project(Application)

# Crea la biblioteca compartida 'application'.
# Debes listar todos los archivos .cpp de esta capa aquí.
add_library(application SHARED
    UseCases/GetUsersUseCase.cpp 
    UseCases/GetUserUseCase.cpp
    UseCases/SingUpUseCase.cpp
    Helpers/Sha256Helper.cpp
    Helpers/JwtHelper.cpp
    # Ejemplo de archivo de caso de uso
    # Puedes añadir más archivos .cpp aquí, separados por espacios o saltos de línea.
)

# Vincula la biblioteca 'application' con 'domain'.
# La palabra clave PRIVATE indica que la dependencia es interna.
target_link_libraries(application PRIVATE domain infrastructure
    jwt
)

# Establece los directorios de inclusión para las otras capas que dependen de esta.
target_include_directories(application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Helpers
    ${CMAKE_CURRENT_SOURCE_DIR}/UseCases
)