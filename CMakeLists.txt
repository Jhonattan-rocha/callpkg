cmake_minimum_required(VERSION 3.5)
project(CALLPKG)

set(CMAKE_CXX_STANDARD 20)  # Define a versão do C++ que será utilizada
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/utils")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Commands")

# Adiciona os arquivos fonte do seu projeto
add_executable(CALLPKG 
    main.cpp
    utils/StringTools/stringtools.h utils/StringTools/stringtools.inl utils/StringTools/stringtools.cpp
    utils/FileManager/filemanager.h utils/FileManager/filemanager.cpp
    utils/curl_request/requests.h utils/curl_request/requests.cpp
    utils/PathManager/pathmanager.h utils/PathManager/pathmanager.cpp
    utils/Linux/linux.h utils/Linux/linux.cpp
    utils/PackagesManager/packagesmanager.h utils/PackagesManager/packagesmanager.cpp
    Commands/GenericCommand/genericcommand.h Commands/GenericCommand/genericcommand.cpp
    Commands/Exec/exec.h Commands/Exec/exec.cpp
    Commands/Validate/validate.h Commands/Validate/validate.cpp
    Commands/Logging/logging.h
)

# Define as bibliotecas que seu projeto precisa
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(CALLPKG ${CURL_LIBRARIES})

find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})
target_link_libraries(CALLPKG ${nlohmann_json_LIBRARIES})