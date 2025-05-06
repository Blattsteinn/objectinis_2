# v3.0
This program is a student grade management system that handles input, random data generation, and file-based operations for processing student records. It computes final grades using both average and median methods while offering functionalities for sorting, grouping, and performance testing.

# Installation and Launch Instructions:
- to install the program that uses `Vector<T>` run `Setup_cvector.msi`
- to install the program that uses `std::vector<T>` run `Setup_vector.msi`\

- Both installers deploy to `C:\Program Files\VU\User` and create a Desktop shortcut named **StudentApp**.

## Improvements in Version 3.0:
- introduced a custom implementation `Vector<T>` of `std::vector<T>`

# `Vector<T>`
Can be found in `vector.h` folder.\
**Key Features:**
- **Contiguous storage**: Elements live in a single dynamically allocated block—fast random access via `operator[]` or `at()`.
- **Automatic growth**: Capacity doubles whenever more space is needed.

- **Standard-like interface**: Supports all common `std::vector` member functions:
- Construction: default, fill, range, initializer list
- Capacity: `size()`, `capacity()`, `reserve()`, `shrink_to_fit()`, `empty()`
- Element access: `operator[]`, `at()`, `front()`, `back()`, `data()`
- Modifiers: `clear()`, `insert()`, `emplace()`, `erase()`, `push_back()`, `emplace_back()`, `pop_back()`, `resize()`, `swap()`
- Assignments and comparisons: copy/move constructors, copy/move assignment, equality and comparison operators

## Usage Examples

```cpp
#include <iostream>
#include "vector.h/Vector.h"

using namespace std;

int main() {
    Vector<int> v{10, 20, 30};

    // 1) Element access: at()
    try {
        cout << "v.at(1) = " << v.at(1) << endl; // prints 20
    } catch (const std::out_of_range& e) {
        cerr << e.what() << std::endl;
    }

    // 2) Modifiers: push_back()
    v.push_back(40);
    cout << "After push_back(40): " << v << endl; // [10, 20, 30, 40]

    // 3) Modifiers: insert()
    auto it = v.insert(v.begin() + 2, 25);
    cout << "After insert 25 at pos 2: " << v << endl; // [10, 20, 25, 30, 40]
    cout << "Inserted element = " << *it << endl;       // prints 25

    // 4) Capacity control: reserve()
    v.reserve(10);
    cout << "Capacity after reserve(10): " << v.capacity() << std::endl;

    // 5) Operators: copy assignment
    Vector<int> u;
    u = v;
    cout << "Copied vector u: " << u << endl; // [10, 20, 25, 30, 40]

    // 6) Element access: operator[]
    cout << "v[0] = " << v[0] << endl;  // prints 10

    // 7) Element access: front() and back()
    cout << "front() = " << v.front() << ", back() = " << v.back() << endl;  
    // prints front() = 10, back() = 40

    // 8) Modifiers: pop_back()
    v.pop_back();
    cout << "After pop_back(): " << v << endl;  // [10, 20, 25, 30]

    // 9) Modifiers: erase() (remove element at position 1)
    v.erase(v.begin() + 1);
    cout << "After erase at pos 1: " << v << endl;  // [10, 25, 30]

    // 10) Capacity control: shrink_to_fit()
    cout << "Capacity before shrink_to_fit() = " << v.capacity() << endl;
    v.shrink_to_fit();
    cout << "Size = " << v.size() << ", Capacity after shrink_to_fit() = " << v.capacity() << endl;

    return 0;
}
```
# `class Studentas`
## Overridden methods:
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

Full results can be found here - [Testavimas v3.xlsx](https://github.com/user-attachments/files/20068551/Testavimas.v3.xlsx)

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





