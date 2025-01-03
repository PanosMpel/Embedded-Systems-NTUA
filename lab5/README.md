echo "# 5th Lab Exercise: ARM Processor Assembly Programming

## Environment

This solution was specifically developed and tested in the **QEMU (Quick Emulator)** environment, simulating the ARM architecture.  
The following environments are required for the exercises:

- **Task 1:** ARM Assembly Programming (QEMU, Terminal).
- **Task 2:** Serial Communication Setup (QEMU, Terminal).
- **Task 3:** C and ARM Assembly Integration (QEMU).

The code should be used and tested in the same setup for best results.

## Repository Contents

1. **Original Code:**
   - The initial version of the code before applying the necessary changes. The original code is used for **Task 1: String Transformation**, **Task 2: Serial Communication**, and **Task 3: C and Assembly Integration**.

2. **Modified Code:**
   - This version includes the necessary improvements and optimizations. This updated version is used for all the tasks mentioned.

3. **Data:**
   - Contains the input files used for testing the string transformations and serial communication tasks.

4. **Outputs:**
   - Contains the output files generated from the different runs of the exercises.

5. **[Exercise5.pdf](https://github.com/yourusername/Embedded-Systems-NTUA/blob/main/lab5/Exercise5.pdf):**
   - A detailed document with step-by-step instructions for completing the exercises.

6. **QEMU_ARM_Installation_Instructions.pdf:**
   - A detailed guide for setting up QEMU to emulate the ARM architecture for these exercises.

7. **`bin` Folder:**
   - Contains the compiled executables for both the host and guest programs used in Task 1 and Task 2.

8. **sources.list:**
   - Contains the configuration file for package sources needed in the virtual environment (guest system).

---

## Task Overview

### Task 1: String Transformation (ARM Assembly)
- This task involves writing an ARM assembly program that reads a string of up to 32 characters from the terminal, transforms uppercase to lowercase (and vice versa), and modifies digits according to a specific mapping.
  
### Task 2: Serial Communication Between Host and Guest
- Implement a serial communication protocol between a **host** and **guest** machine using QEMU's virtual serial port feature. The guest processes a string and identifies the most frequent character (excluding spaces).

### Task 3: Integration of C with ARM Assembly Code
- This task combines C code and ARM assembly code to perform string manipulations (like `strlen`, `strcpy`, `strcmp`, etc.), replacing C standard library functions with custom ARM assembly implementations.

---

## QEMU Setup

For setting up QEMU and running the virtual ARM machine, refer to the **QEMU_ARM_Installation_Instructions.pdf** in the repository. This guide provides step-by-step instructions to install QEMU and configure your system to run ARM-based programs in an emulated environment.

---

## Compilation and Execution

1. **Compile the Code:**
   - To compile the C and ARM assembly programs, use the following commands:

   ```bash
   gcc -o host_program host_program.c
   gcc -o guest_program guest_program.s
