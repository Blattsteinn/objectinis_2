cmake -G "MinGW Makefiles" CMakeLists.txt
cmake --install .
cmake --build .
copy src\studentai.txt Debug\studentai.txt
cd Debug\
student.exe
pause
