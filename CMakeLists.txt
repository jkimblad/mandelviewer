cmake_minimum_required(VERSION 3.16)
project(helloworld
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

add_library(stats StatsEntry.cpp StatsBox.cpp StatsEntry.hpp StatsBox.hpp)
add_library(mandel MandelBrot.cpp MandelBrot.hpp)
add_executable(mandelbin main.cpp)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(stats)
set_project_warnings(mandel)
set_project_warnings(mandelbin)

target_link_libraries(mandel PUBLIC stats)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
target_link_libraries(mandelbin
        ${SFML_LIBRARIES} 
        ${SFML_DEPENDENCIES}
        mandel)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
else()
        message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()
