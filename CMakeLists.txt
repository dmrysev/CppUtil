cmake_minimum_required(VERSION 3.6)
project(CppUtil LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
find_package(GTest REQUIRED)

file(GLOB_RECURSE SRC_LIST src/*.cpp src/*.h include/*.h)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_include_directories(${PROJECT_NAME}${SUBPROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}${SUBPROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE TEST_SRC_LIST test/*.cpp)
add_executable(${PROJECT_NAME}Test ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}Test
    PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        ${GMOCK_BOTH_LIBRARIES}
        ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}Test
    PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS})
