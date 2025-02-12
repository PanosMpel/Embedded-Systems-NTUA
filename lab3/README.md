# 3rd Lab Exercise: Introduction to High Level Synthesis

## Lab Overview

The goal of this lab is to introduce Field Programmable Gate Arrays (FPGA) programming using **High Level Synthesis (HLS)**. The lab focuses on optimizing the execution time of a **Recommendation System (RS)** based on the **K Nearest Neighbors (KNN)** algorithm using a subset of the MovieLens dataset. The system will be accelerated using **SDSoC 2016.4**, targeting the **Zynq-7000 ARM/FPGA SoC (Zybo)** platform. The application will compare software (SW) and hardware (HW) implementations, aiming to maximize speedup with HLS optimizations in the HW implementation.

### Main Objectives:
- Accelerate the KNN-based recommendation system using HLS.
- Optimize the computationally intensive part (Euclidean distance calculation) for hardware execution.
- Measure the speedup between software and hardware implementations on the Zybo board.

## Environment

This solution was specifically developed and tested in the **Xilinx SDSoC 2016.4** environment. For best results, the code should be used and tested in the same version of SDSoC.

### Required Tools:
- **Xilinx SDSoC 2016.4:** Development environment for FPGA programming with HLS. It includes tools for writing C/C++ code, designing hardware accelerators, and generating bitstreams for FPGA execution.
- **Zynq-7000 ARM/FPGA SoC (Zybo):** The hardware platform used to run the accelerated system.
  
You can find more details about the installation and setup in the following guides:
- [Exercise3.pdf](https://github.com/PanosMpel/Embedded-Systems-NTUA/blob/main/lab3/Exercise3.pdf)
- [SDSoC_Installation_Guide.pdf](https://github.com/PanosMpel/Embedded-Systems-NTUA/blob/main/lab3/SDSoC_Installation_Guide.pdf)

## Task Overview

### Task 1: Optimizing `calcDistancesHW` Function

- **a)** Implement the `calcDistancesHW` function as a HW function and estimate performance without any optimizations. Record the report showing estimated resources and clock cycles, and identify the loops that require the most cycles.
- **b)** Generate the SD card with the bitstream and load it onto the Zybo. Reboot the system and run the application. Compare the cycle count with the estimation and check if there is speedup relative to the software (SW) execution.
- **c)** Apply HLS optimizations to improve the performance of the `calcDistancesHW` function. Aim for a pipelined design. Compare the results with the unoptimized version in terms of cycle count and speedup.

### Task 2: Using `ap_fixed` Library for Custom Datatypes

- **a)** Modify the `calcDist.h` file to optimize the `DTYPE1` datatype by adjusting the integer and fractional bits (INT_BITS and DEC_BITS). Estimate performance with these new settings and apply the previous HLS optimizations.
- **b)** Generate the SD card with the updated bitstream and execute the application on the FPGA. Compare this optimized version with the previous version.

### Task 3: Further Optimization and Speedup Analysis

- **a)** Further optimize the design from Task 2 to achieve an even better speedup. Ensure that the design is pipelined, and compare the performance after the optimizations.
- **b)** Generate the SD card with the final bitstream and test the application on the Zybo. Record the speedup and compare it with previous versions to analyze performance improvement.

---

