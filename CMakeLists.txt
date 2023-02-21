cmake_minimum_required(VERSION 3.0.0)
project(serialization VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(serialization main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

set(CUSTOM_COMPILE_FLAGS "-stdlib=libstdc++")
set(CUSTOM_LINK_FLAGS    "-stdlib=libstdc++")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINK_FLAGS}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
