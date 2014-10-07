project(Chip8)
find_package(SDL2 REQUIRED)

INCLUDE_DIRECTORIES( ${SDL2_INCLUDE_DIR} )

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${SDL2_LIBRARY} )

