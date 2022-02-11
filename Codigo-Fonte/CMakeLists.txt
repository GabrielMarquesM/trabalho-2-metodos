cmake_minimum_required(VERSION 3.0.0)
project(trabalho2metodos LANGUAGES CXX VERSION 0.5)

set(CMAKE_CXX_STANDARD 17)

#Adding submodules
add_subdirectory(include)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} OurInclude)
