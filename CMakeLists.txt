cmake_minimum_required(VERSION 4.0)
project(carrascone LANGUAGES CXX)

option(BUILD_TESTING "Build CXX tests" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 REQUIRED COMPONENTS Window Graphics System)
find_package(Boost REQUIRED COMPONENTS program_options)
if (BUILD_TESTING)
  find_package(Catch2 3 REQUIRED)
endif()

add_subdirectory(src)
add_subdirectory(test)

