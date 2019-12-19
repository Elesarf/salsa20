# Check minimum required CMake version
cmake_minimum_required(VERSION 3.7)

project("salsa")

set(SOURCES
    src/main.cpp
    src/salsa20.cpp
    src/salsa_file_wrapper.cpp
    )

set(HEADERS
    include/salsa20.h
    include/salsa_file_wrapper.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${OTHER})

set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_EXTENSIONS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    )

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC -Wall
    PUBLIC -Wextra
    PUBLIC -Werror
    PUBLIC -O0
    )

target_compile_options(${PROJECT_NAME} PUBLIC -g)

target_include_directories(${PROJECT_NAME} PRIVATE ./src)
target_include_directories(${PROJECT_NAME} PUBLIC ./include)
