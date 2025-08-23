cmake_minimum_required(VERSION 3.10)
project(Domain)

# Crea la biblioteca compartida 'domain'. 
# Los archivos .hpp no necesitan estar aquí, solo los .cpp
add_library(domain SHARED 
    Kernel/ConfigReaderHelper.cpp
    Validators/ValidatorsT.cpp
)

# Establece los directorios de inclusión para las otras capas.
# Se deben incluir los subdirectorios que contienen los archivos .h/.hpp
target_include_directories(domain PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities
    ${CMAKE_CURRENT_SOURCE_DIR}/IDAO
    ${CMAKE_CURRENT_SOURCE_DIR}/Kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/Validators
)