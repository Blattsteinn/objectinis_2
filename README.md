# Installation and Launch Instructions:

- Install MinGW and CMake (version 3.25 or higher).
- Download the repository containing the above files.
- Run run.bat to configure, build, install, and launch the program.



# Container Performance Comparison (Vector, List, Deque)
This document analyzes how the choice of container (vector, list, deque) affects program performance when managing student data under different grouping strategies. Performance metrics considered include memory efficiency and execution time (reading, sorting, grouping).

Full test results can be found here - [Test results.xlsx](https://github.com/user-attachments/files/19260760/Test.results.xlsx)

System parameters: ....

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

| File       | Deque (S2)  | Deque (S1)  |        | List (S2)  | List (S1)  |        | Vector (S2)  |
|------------|------------|------------|--------|------------|------------|--------|------------|
| 1,000      | 0.00025062 | 0.00064116  |        | 0.00020806 | 0.00058418  |        | 0.0025787  |
| 10,000     | 0.00310692 | 0.00517562  |        | 0.00283066 | 0.00898998  |        | 0.257335   |
| 100,000    | 0.02776866 | 0.06195668  |        | 0.04780796 | 0.165474    |        | 34.0452    |
| 1,000,000  | 0.3512722  | 0.8973906   |        | 0.5217682  | 2.034754    |        | too long.. |
| 10,000,000 | 29.29084   | 51.33604    |        | 7.631878   | 26.07286    |        | -          |

**Key Takeaways:**
- **Deque:** Strategy 2 is **2x faster** than Strategy 1.
- **List:** Strategy 2 is **4x faster** than Strategy 1.
- **Vector:** Becomes **unusable beyond 100,000 objects**.

## 3rd strategy
This strategy tilizes efficient STL methods to optimize container handling when grouping students into two groups.



## Grouping Performance Comparison to 1st & 2nd strategy
 (average results)

| File       | Deque (S3)  | Deque (S2)  | Deque (S1)  |   | Vector (S3)  | Vector (S2)  | Vector (S1)  |   | List (S3)   | List (S2)   | List (S1)   |
|------------|------------|------------|------------|---|-------------|-------------|-------------|---|------------|------------|------------|
| 1,000      | 0.00011425 | 0.00021374 | 0.00064116 |   | 0.0000599   | 0.0025787   | 0.00017876  |   | 0.00019066 | 0.00020806 | 0.00058418 |
| 10,000     | 0.00287695 | 0.00316602 | 0.00517562 |   | 0.00112366  | 0.257335    | 0.00215056  |   | 0.00319796 | 0.00283066 | 0.00898998 |
| 100,000    | 0.0266666  | 0.0273609  | 0.06195668 |   | 0.01488562  | 34.0452     | 0.03292928  |   | 0.0566572  | 0.04780796 | 0.165474   |
| 1,000,000  | 0.2981615  | 0.3290822  | 0.8973906  |   | 0.1729368   | -           | 0.4305424   |   | 0.6462056  | 0.5217682  | 2.034754   |
| 10,000,000 | 24.438075  | 28.11586   | 51.33604   |   | 3.128188    | -           | 7.583668    |   | 8.18736    | 7.631878   | 26.07286   |
