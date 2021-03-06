project(Chip8)
cmake_minimum_required(VERSION 2.8)

# This file will prepare chip8 to build with SDL2

#compiler


# CXX_FLAGS
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -Wextra -Winline  -std=c++11")

#######################################################################################
#######################################################################################

# BUILD TYPES
if (CMAKE_BUILD_TYPE STREQUAL "Release")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-omit-frame-pointer")

endif()


# ADICIONAR MODULES EXTERNOS
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeInclude)

find_package(SDL2 REQUIRED)
INCLUDE_DIRECTORIES( ${SDL2_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/Chip8/include/ )

# ACHAR OS .CPP E .H
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Chip8/src/*.cpp)
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  Chip8/include/*.h)


# Linkar .cpp para este binário (que tem o nome do projeto)
add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})

# Linkar bibliotecas dinâmicas
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${SDL2_LIBRARY} )

