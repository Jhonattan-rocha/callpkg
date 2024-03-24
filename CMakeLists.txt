cmake_minimum_required(VERSION 3.5)
project(callpkg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)  # Define a versão do C++ que será utilizada
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/**")

# Adiciona os arquivos fonte do seu projeto
add_executable(callpkg main.cpp)

# Define as bibliotecas que seu projeto precisa
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(callpkg ${CURL_LIBRARIES})