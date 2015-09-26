project(Chip8)
cmake_minimum_required(VERSION 2.8)

# CXX_FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

# ADICIONAR MODULES EXTERNOS
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeInclude)

find_package(SDL2 REQUIRED)
INCLUDE_DIRECTORIES( ${SDL2_INCLUDE_DIR} )

# ACHAR OS .CPP E .H
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  src/*.h)


# Linkar .cpp para este binário (que tem o nome do projeto)
add_executable(${PROJECT_NAME} ${SRCS})

# Linkar bibliotecas dinâmicas
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${SDL2_LIBRARY} )

