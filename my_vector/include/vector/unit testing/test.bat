@echo off
REM Developer helper: build & run unit tests only

REM 1) Move into the tests folder
pushd tests

REM 2) Ensure a private build directory exists
if not exist build (
    mkdir build
)

REM 3) Configure the tests CMakeLists.txt
cmake -G "MinGW Makefiles" -S . -B build

REM 4) Build the runTests target
cmake --build build --config Debug

REM 5) Run all tests and show failures
pushd build
ctest -C Debug --output-on-failure
popd

REM 6) Return to project root
popd

pause
