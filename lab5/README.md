echo "# 5th Lab Exercise: ARM Processor Assembly Programming

## Environment

This solution was specifically developed and tested in the **QEMU (Quick Emulator)** environment, simulating the ARM architecture.  
The following environments are required for the exercises:

- **Task 1:** ARM Assembly Programming (QEMU, Terminal).
- **Task 2:** Serial Communication Setup (QEMU, Terminal).
- **Task 3:** C and ARM Assembly Integration (QEMU).

The code should be used and tested in the same setup for best results.
---

## QEMU Setup

For setting up QEMU and running the virtual ARM machine, refer to the **QEMU_ARM_Installation_Instructions.pdf** in the repository. This guide provides step-by-step instructions to install QEMU and configure your system to run ARM-based programs in an emulated environment.

---

## Repository Contents

1. **Code:**
   - The initial version of the code before applying the necessary changes. The code is used for **Task 1: String Transformation**, **Task 2: Serial Communication**, and **Task 3: C and Assembly Integration**.

3. **Data:**
   - Contains the input files used for testing the string transformations and serial communication tasks.

5. **[Exercise5.pdf](https://github.com/yourusername/Embedded-Systems-NTUA/blob/main/lab5/Exercise5.pdf):**
   - A detailed document with step-by-step instructions for completing the exercises.

6. **QEMU_ARM_Installation_Instructions.pdf:**
   - A detailed guide for setting up QEMU to emulate the ARM architecture for these exercises.

8. **sources.list:**
   - Contains the configuration file for package sources needed in the virtual environment (vs code).

---

## Task Overview

### Task 1: String Transformation (ARM Assembly)
- This task involves writing an ARM assembly program that reads a string of up to 32 characters from the terminal, transforms uppercase to lowercase (and vice versa), and modifies digits according to a specific mapping.
  
### Task 2: Serial Communication Between Host and Guest
- Implement a serial communication protocol between a **host** and **guest** machine using QEMU's virtual serial port feature. The guest processes a string and identifies the most frequent character (excluding spaces).

### Task 3: Integration of C with ARM Assembly Code
- This task combines C code and ARM assembly code to perform string manipulations (like `strlen`, `strcpy`, `strcmp`, etc.), replacing C standard library functions with custom ARM assembly implementations." > README.md
