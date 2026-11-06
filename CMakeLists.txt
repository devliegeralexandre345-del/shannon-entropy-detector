cmake_minimum_required(VERSION 3.16)
project(shannon_entropy_detector LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# Exécutable principal
add_executable(shannon_entropy_detector src/main.cpp src/entropy_calculator.cpp)

# Tests unitaires
enable_testing()
add_executable(unit_tests tests/test.cpp src/entropy_calculator.cpp)
add_test(NAME AllTests COMMAND unit_tests)