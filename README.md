# v3.0
This program is a student grade management system that handles input, random data generation, and file-based operations for processing student records. It computes final grades using both average and median methods while offering functionalities for sorting, grouping, and performance testing.

## Improvements in Version 3.0:
- introduced a custom implementation `Vector<T>` of `std::vector<T>`

# Installation and Launch Instructions:
1) Install [MinGW](http://www.mingw.org/) (or [MinGW-w64](https://mingw-w64.org/doku.php/download)) and [CMake (version 3.25 or higher)](https://cmake.org/download/).
2) Download the repository containing the above files.
3) Run `run.bat` to configure, build, and install the program.
4) Launch the executable (`studentai`).

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
  
# V3.0 benchmarks 

### System parameters:
- Operating System: Windows 11
- Compiler: g++ 14.2.0 (MinGW)
- Processor: AMD Ryzen 7 8845HS (3.80 GHz, 8 Cores, 16 Threads)
- Memory: 16 GB DDR5
- Storage: 1TB NVMe SSD

Full results can be found here - excel file...

# Benchmark test 1
Compares the time to push_back() integers from 10⁴ to 10⁹ into `std::vector<int>` vs a custom `Vector<int>`

## Results (average)
| sz            | avg std::vector time (s) | avg Vector<T> time (s) | avg difference (s)   |
|--------------:|-------------------------:|-----------------------:|---------------------:|
|      10,000   |                0.0002125 |              0.0000734 |            -0.0001391 |
|     100,000   |                0.0004679 |              0.0003474 |            -0.0001205 |
|   1,000,000   |                0.0031003 |              0.0028508 |            -0.0002495 |
|  10,000,000   |                0.0305887 |              0.0320830 |             0.0014943 |
| 100,000,000   |                0.2358850 |              0.2446802 |             0.0087951 |
|1,000,000,000  |                2.0946560 |              2.3812340 |             0.2865781 |


# Benchmark test 2
Measure (s) the time taken by `std::vector` vs `Vector<T>` to read student records from a .txt file, sort them (calculate median and average), and write the results to an output file.

## Average test results of Vector<T> (done 5x times)
| Filename   | Reading   | Sorting    | Printing to file | Overall time (s) |
|------------|-----------|------------|------------------|------------------|
| 100 000    | 1.325898  | 0.00923818 | 0.09424762       | 1.4293838        |
| 1 000 000  | 13.58962  | 0.04733822 | 0.9282586        | 14.56521682      |
| 10 000 000 | 143.4926  | 0.4389946  | 10.38386         | 154.3154546      |

## Average test results of std::vector<T> (done 5x times)
| Filename   | Reading   | Sorting     | Printing to file | Overall time (s) |
|------------|-----------|-------------|------------------|------------------|
| 100 000    | 1.292616  | 0.00446054  | 0.1227304        | 1.41980694       |
| 1 000 000  | 13.70252  | 0.03302834  | 1.273494         | 15.00904234      |
| 10 000 000 | 141.0708  | 0.4732446   | 14.51076         | 156.0548046      |

# Reallocation
When comparing how many times the containers (`std::vector` and `Vector<T>`) reallocate in version V1.5, we see that Vector<T> matches std::vector
Function: `void testing3__2()`

| Size       | `std::vector` growths | `Vector<T>` growths | Difference |
|------------|-----------------------:|---------------------:|-----------:|
| 100,000,000 |                     30 |                  30 |          30|


![image](https://github.com/user-attachments/assets/397800c3-2dbf-467f-bc10-5e5f75f3e003)





