cmake_minimum_required(VERSION 3.10)
project(UnitTests)

set(CMAKE_CXX_STANDARD 17)

# Найти GoogleTest
find_package(GTest REQUIRED)

# Исходные файлы тестов
set(TEST_SOURCES
    unittests.cpp
    ${CMAKE_SOURCE_DIR}/mfuncs.cpp
    ${CMAKE_SOURCE_DIR}/ffuncs.cpp
    ${CMAKE_SOURCE_DIR}/lfuncs.cpp
    ${CMAKE_SOURCE_DIR}/qfuncs.cpp
    ${CMAKE_SOURCE_DIR}/sfuncs.cpp
    ${CMAKE_SOURCE_DIR}/tfuncs.cpp
    ${CMAKE_SOURCE_DIR}/hfuncs.cpp
)

# Включаемые директории
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${GTEST_INCLUDE_DIRS}
)

# Создать исполняемый файл тестов
add_executable(runTests ${TEST_SOURCES})

# Связать с GoogleTest
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Включить покрытие кода
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(runTests PRIVATE --coverage)
    target_link_libraries(runTests --coverage)
endif()