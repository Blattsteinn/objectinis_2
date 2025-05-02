# v2.0
This program is a student grade management system that handles input, random data generation, and file-based operations for processing student records. It computes final grades using both average and median methods while offering functionalities for sorting, grouping, and performance testing.

### Improvements in Version 2.0:
- introduced Doxygen‐based Documentation. Includes a `Doxyfile` configured to generate both HTML and LaTeX outputs
- created Unit Tests for `Studentas` class. 
  
**The class supports multiple input methods:** 
- `operator>>` now prompts users for names, grades, and exam scores
- `operator<<` prints names and calculated final grades

**working with files:**
- function appendingContainerViaFile(string file_name, &student_list) is used to read a text file
- function print_to_file(list_of_students, file_name) is used to write data to a text file

# Installation and Launch Instructions:

- Install [MinGW](http://www.mingw.org/) (or [MinGW-w64](https://mingw-w64.org/doku.php/download)) and [CMake (version 3.25 or higher)](https://cmake.org/download/).
- Download the repository containing the above files.
- Run `run.bat` to configure, build, and install the program.
- Launch the program (`studentai`).

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
  
# V1.1 testing 

### Objective
Measure the efficiency of grouping student records into two distinct groups, and evaluate performance under various optimization levels (-O1, -O2, and -O3).

In this test, a vector containing student records is split into two groups:
- **Top-Performing Students:** Students whose average final score is 5 or above remain in the primary container.
- **Underperforming Students:** Students whose average final score is below 5 are transferred to a separate container.

The procedure involves:
1. Sorting the student records in descending order based on their average final score.
2. Removing students with scores below 5 from the primary container and adding them to a new container.

At the end of the test, only top-performing students remain in the main container, while the underperforming students are in a separate container.

## Test results

Gouping performance using classes
| File      | Average (-o1) | Average (-o2) | Average (-o3) |
|-----------|---------------|---------------|---------------|
| 100,000   | 0.00840548    | 0.0092536     | 0.00834536    |
| 1,000,000 | 0.08980532    | 0.08771468    | 0.0799193     |
| .exe size | 335KB         | 338KB         | 571KB         |

Gouping performance using structs
| File      | Average (-o1) | Average (-o2) | Average (-o3) |
|-----------|---------------|---------------|---------------|
| 100,000   | 0.0155993     | 0.01317164    | 0.01357718    |
| 1,000,000 | 0.1269012     | 0.1168168     | 0.1159462     |
| .exe size | 323KB         | 287KB         | 286KB         |

Full test results can be found here - [Testavimas v1.1.xlsx](https://github.com/user-attachments/files/19428354/Testavimas.v1.1.xlsx)

### Testing system parameters:
- Operating System: Windows 11
- Compiler: g++ 14.2.0 (MinGW)
- Processor: AMD Ryzen 7 8845HS (3.80 GHz, 8 Cores, 16 Threads)
- Memory: 16 GB DDR5
- Storage: 1TB NVMe SSD

# V1.0 testing 

# Container Performance Comparison (Vector, List, Deque)
This analyzes how the choice of container (vector, list, deque)  affects program performance when managing student data under different grouping strategies. Performance metrics considered include memory efficiency and execution time (reading, sorting, grouping). The tests are conducted with varying file sizes, with 1,000; 10,000; 100,000; 1,000,000 & 10,000,000 students data.

Full test results can be found here - [Test results.xlsx](https://github.com/user-attachments/files/19260760/Test.results.xlsx)

 You can change the container by opening my_library.h & editing the code (Look at V1.0). The default container is vector.

 - Average is calculated using the results of 5 different tests
 - Testing uses the same input files

## 1st strategy 
This strategy involves splitting a container of students into two new containers of the same type: one for "good" students and one for "bad" students. 

In this approach, the same student is stored in two containers making it memory inefficient.



## Results
**Deque average**
Memory inefficient, has issues working with large sizes
| Size       | Read Avg (s) | Sort Avg (s) | Group Avg (s) | Total Avg (s) |
|------------|---------------------|---------------------|----------------------|---------------------|
| 1,000      | 0.02844956          | 0.0005178           | 0.00064116           | 0.03019116          |
| 10,000     | 0.10552896          | 0.00517462          | 0.00517562           | 0.1163678           |
| 100,000    | 1.035632            | 0.07265532          | 0.06195668           | 1.171086            |
| 1,000,000  | 10.623              | 0.9315776           | 0.8973906            | 12.45276            |
| 10,000,000 | 192.141             | 16.55702            | 51.33604             | 260.4148            |

**Vector average**
| Size       | Read Avg (s) | Sort Avg (s) | Group Avg (s) | Total Avg (s) |
|------------|------------|------------|------------|------------|
| 1,000      | 0.010337   | 0.00009786 | 0.00017876 | 0.01092928 |
| 10,000     | 0.09128952 | 0.00185314 | 0.00215056 | 0.09576322 |
| 100,000    | 0.8871364  | 0.01464122 | 0.03292928 | 0.93549    |
| 1,000,000  | 8.740884   | 0.186925   | 0.4305424  | 9.359252   |
| 10,000,000 | 90.82808   | 1.769656   | 7.583668   | 100.18238  |

**List average**
| Size       | Read Avg (s) | Sort Avg (s) | Group Avg (s) | Total Avg (s) |
|------------|------------|------------|------------|------------|
| 1,000      | 0.01216484 | 0.00008752 | 0.00058418 | 0.0132518  |
| 10,000     | 0.0998488  | 0.00235064 | 0.00898998 | 0.1117702  |
| 100,000    | 1.0053898  | 0.01892004 | 0.165474   | 1.190548   |
| 1,000,000  | 9.977394   | 0.5905198  | 2.034754   | 12.60358   |
| 10,000,000 | 106.6492   | 13.05704   | 26.07286   | 145.78     |

## 2nd strategy
This strategy involves splitting a student container using only one new container for "bad" students. In this approach, if a student is classified as a worse, we transfer them to the new  container and remove them from the main student container. After this step, only top students remain in the main container thus being more memory efficient.

## Grouping Performance Compared to 1st strategy 
(average results)

## Grouping Performance Compared to 1st strategy 
(average results)

| File       | Deque (S2)  | Deque (S1)   |   | List (S2)  | List (S1)   |   | Vector (S2)  | Vector (S1) |
|------------|-------------|--------------|---|------------|-------------|---|--------------|-------------|
| 1,000      | 0.00025062  | 0.00064116   |   | 0.00020806 | 0.00058418  |   | 0.00008544   | 0.00058418  |
| 10,000     | 0.00310692  | 0.00517562   |   | 0.00283066 | 0.00898998  |   | 0.00070916   | 0.00898998  |
| 100,000    | 0.02776866  | 0.06195668   |   | 0.04780796 | 0.165474    |   | 0.0141482    | 0.165474    |
| 1,000,000  | 0.3512722   | 0.8973906    |   | 0.5217682  | 2.034754    |   | 0.1192752    | 2.034754    |
| 10,000,000 | 29.29084    | 51.33604     |   | 7.631878   | 26.07286    |   | 1.274536     | 26.07286    |


**Key Takeaways:**
- **Deque:** Strategy 2 is **2x faster** than Strategy 1.
- **List:** Strategy 2 is **4x faster** than Strategy 1.
- **Vector:** Strategy 2 is **29x faster**

## 3rd strategy
Uses 2nd strategy, but also utilizes efficient STL methods to optimize container handling when grouping students into two groups. (std::find_if, .assign(), .erase())

## Grouping Performance Comparison to 1st & 2nd strategy
 (average results)

| File       | Deque (S3)  | Deque (S2)  | Deque (S1)  |   | Vector (S3)  | Vector (S2)   | Vector (S1)  |   | List (S3)   | List (S2)   | List (S1)   |
|------------|-------------|-------------|-------------|---|--------------|---------------|--------------|---|-------------|-------------|-------------|
| 1,000      | 0.00011425  | 0.00021374  | 0.00064116  |   | 0.0000599   | 0.00008544    | 0.00017876   |   | 0.00019066  | 0.00020806  | 0.00058418  |
| 10,000     | 0.00287695  | 0.00316602  | 0.00517562  |   | 0.00112366  | 0.00070916    | 0.00215056   |   | 0.00319796  | 0.00283066  | 0.00898998  |
| 100,000    | 0.0266666   | 0.0273609   | 0.06195668  |   | 0.01488562  | 0.0141482     | 0.03292928   |   | 0.0566572   | 0.04780796  | 0.165474    |
| 1,000,000  | 0.2981615   | 0.3290822   | 0.8973906   |   | 0.1729368   | 0.1192752     | 0.4305424    |   | 0.6462056   | 0.5217682   | 2.034754    |
| 10,000,000 | 24.438075   | 28.11586    | 51.33604    |   | 3.128188    | 1.274536      | 7.583668     |   | 8.18736     | 7.631878    | 26.07286    |
