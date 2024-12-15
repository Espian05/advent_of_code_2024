cmake_minimum_required(VERSION 3.8)
project(advent_of_code_2024)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.cpp)

# Copy asset folder to build folder
add_custom_target(inputs
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/src/inputs ${CMAKE_CURRENT_BINARY_DIR}/inputs
)
add_dependencies(${PROJECT_NAME} inputs)

target_link_libraries(${PROJECT_NAME})
