# v3.0
This program is a student grade management system that handles input, random data generation, and file-based operations for processing student records. It computes final grades using both average and median methods while offering functionalities for sorting, grouping, and performance testing.

## Improvements in Version 3.0:

[...]

# Installation and Launch Instructions:
1) Install [MinGW](http://www.mingw.org/) (or [MinGW-w64](https://mingw-w64.org/doku.php/download)) and [CMake (version 3.25 or higher)](https://cmake.org/download/).
2) Download the repository containing the above files.
3) Run `run.bat` to configure, build, and install the program.
4) Launch the executable (`studentai`).

# Documentation and Testing Instructions

## 1) Generating Doxygen Documentation
1. Install [Doxygen](https://www.doxygen.nl/download.html)  
2. Open a command prompt in the project root (where `Doxyfile` is).
3. Run `doxygen Doxyfile` to create 'Doxygen documentation' folder

## 2) Running Unit Tests
1. Open a command prompt in the **Unit testing** folder  
2. Run `test.bat`. This will create a build folder, configure and compile the tests into `runTests.exe`.
3. Run `runTests.exe` or open command prompt where `runTests.exe` is and run `runTests.exe -s` for more detailed tests.
   
# Overridden methods:
### I/O methods for class `Studentas`:
- `operator>>` prompts users for names, grades, and exam scores
- `operator<<` prints names and calculated final grades

**Working with files:**
- function appendingContainerViaFile(string file_name, &student_list) is used to read a text file and add students to a container
- function print_to_file(list_of_students, file_name) is used to write data to a text file

 ## Previous releases
- v.pradine-release – Initial release. The program accepts user input, generates random grades and names, and calculates the final score using both the arithmetic mean and median.
- v0.1 – Introduced an additional C++ file that implements functionality using C arrays instead of std::vector.
- v0.2 – Added a sorting function, along with capabilities to read from and write to text files.
- v0.3 – Refactored the code by dividing functions across multiple .cpp and .h files for improved organization. Implemented exception handling for file reading errors and user input validation.
- v0.4 – Integrated file generation and performance testing features that evaluate the efficiency of reading data, sorting students into groups, and writing each group to a separate file.
- v1.0-pre-release – Enhanced the program to support three different container types (vector, deque, and list) based on user selection.
- v1.0 - includes performance testing with 3 different strategies (vector, deque, and list).
- v1.1 - transitioned from using structs to classes for better encapsulation and maintainability.
- v1.2 - implementing the 'Rule of Five'. File handling logic, such as reading student records from files and exporting results, was encapsulated within the class. Added support for I/O methods via overloaded `>>` and `<<` operators.
- v1.5- introduced an abstract class `Human` (pure virtual), encapsulating common attributes for people. `Studentas` now inherits from `Human`. No Human objects can be instantiated.
- v2.0 - generated doxygen Documentation, created unit tests
  
# V3.0 testing 

### Testing system parameters:
- Operating System: Windows 11
- Compiler: g++ 14.2.0 (MinGW)
- Processor: AMD Ryzen 7 8845HS (3.80 GHz, 8 Cores, 16 Threads)
- Memory: 16 GB DDR5
- Storage: 1TB NVMe SSD

Full test results can be found here - excel file...
# Test 1
### Objective
Measure and compare the performance of element insertion (`push_back`) into `std::vector<int>` versus a custom `Vector<int>` implementation across exponentially increasing sizes (from 10⁴ to 10⁹), in order to quantify overhead and scalability differences.

## Test results (average)
| sz            | avg std::vector time (s) | avg Vector<T> time (s) | avg difference (s)   |
|--------------:|-------------------------:|-----------------------:|---------------------:|
|      10,000   |                0.0002125 |              0.0000734 |            -0.0001391 |
|     100,000   |                0.0004679 |              0.0003474 |            -0.0001205 |
|   1,000,000   |                0.0031003 |              0.0028508 |            -0.0002495 |
|  10,000,000   |                0.0305887 |              0.0320830 |             0.0014943 |
| 100,000,000   |                0.2358850 |              0.2446802 |             0.0087951 |
|1,000,000,000  |                2.0946560 |              2.3812340 |             0.2865781 |


# Test 2
