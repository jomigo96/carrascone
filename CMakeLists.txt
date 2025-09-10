cmake_minimum_required(VERSION 4.0)
project(carrascone LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)

find_package(SFML 3 REQUIRED COMPONENTS Window Graphics System)
find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(src)

