cmake_minimum_required(VERSION 3.16)
project(helloworld
        VERSION 1.0
        LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

add_library(stats StatsBox.cpp StatsBox.hpp)
add_library(mandel MandelBrot.cpp MandelBrot.hpp)
add_library(sfmlhelper SFHelper.hpp)
add_executable(${PROJECT_NAME} main.cpp)

# sfmlhelper is cpp
set_target_properties(sfmlhelper PROPERTIES LINKER_LANGUAGE CXX)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(stats)
set_project_warnings(${PROJECT_NAME})
set_project_warnings(sfmlhelper)

# Add pthreads
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE sfmlhelper)

# Detect and add SFML
find_package(SFML REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC mandel stats)
target_link_libraries(stats PUBLIC sfml::sfml)
target_link_libraries(mandel PUBLIC sfml::sfml)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
else()
        message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()
