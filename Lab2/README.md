# 2nd Lab Exercise: Dynamic Data Type Refinement (DDTR)

## Lab Overview

The goal of this lab is to optimize the dynamic data structures used in two network applications: the **Deficit Round Robin (DRR)** algorithm and **Dijkstra’s algorithm**, using the **Dynamic Data Type Refinement (DDTR)** methodology. The optimizations focus on:

- **Memory Accesses:** Reducing the number of times memory is accessed.
- **Memory Footprint:** Minimizing the memory required to store data.

This will be achieved by testing and optimizing different data structures, such as **Single Linked List (SLL)**, **Double Linked List (DLL)**, and **Dynamic Array (DYN_ARR)**.

## Environment

This solution was developed and tested in the following environment:

- **Linux – GCC – Pthreads (e.g., GCC 4.8):** Required for compiling and executing the provided code.
- **Valgrind:** A dynamic profiling tool used for memory and threading analysis. It helps evaluate memory usage and memory accesses. More details on installation can be found in [Exercise2.pdf](https://github.com/PanosMpel/Embedded-Systems-NTUA/blob/main/Lab2/Exercise2.pdf).


## Task Overview

### Task 1: Optimizing DRR’s Data Structures

- **a)** Test with all 9 combinations of data structures for the packet and node lists. Record the results for memory accesses and memory footprint.
- **b)** Find the combination with the minimum memory accesses.
- **c)** Find the combination with the smallest memory footprint.

### Task 2: Optimizing Dijkstra’s Data Structures

- **a)** Run the application and record results.
- **b)** Integrate the DDTR library and compare results with the previous step.
- **c)** Test with SLL, DLL, and DYN_ARR. Record memory accesses and footprint.
- **d)** Find the data structure with the lowest memory accesses.
- **e)** Find the data structure with the lowest memory footprint.

---


