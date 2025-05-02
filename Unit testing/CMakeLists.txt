enable_testing()

cmake_minimum_required(VERSION 3.25)
project(student_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell the compiler where to find your headers:
include_directories(
    ${PROJECT_SOURCE_DIR}/../Include  # your library headers
    ${PROJECT_SOURCE_DIR}              # catch.hpp lives here
)

# Collect all .cpp files from src/
file(GLOB LIB_SOURCES
    ${PROJECT_SOURCE_DIR}/../src/*.cpp
)

# Exclude the user‐app main() from these sources:
list(REMOVE_ITEM LIB_SOURCES
    ${PROJECT_SOURCE_DIR}/../src/main.cpp
)

# Build the test runner
add_executable(runTests
    ${LIB_SOURCES}                  # all implementation files except main.cpp
    ${PROJECT_SOURCE_DIR}/test_student.cpp
)
