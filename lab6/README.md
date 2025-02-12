# 6th Lab Exercise: Cross-compiling Programs for ARM Architecture

## Lab Overview

The goal of this lab is to introduce cross-compiling for the **ARM architecture** and the process of setting up a cross-compilation environment. This includes tasks such as **creating a custom cross-compiler**, **installing pre-compiled toolchains**, and **building a custom kernel** for ARM-based systems.

### Main Objectives:
-   Setting up and configuring a virtual ARM machine with QEMU.
-   Installing and configuring a custom cross-compiling toolchain using `crosstool-ng`.
-   Using a pre-compiled Linaro cross-compiler toolchain for ARM.
-   Building a custom Linux kernel for an ARM-based system.

This lab will provide hands-on experience in configuring and using cross-compilation tools and kernel building for embedded systems.

---

## Environment

This solution is designed to work with **QEMU** (Quick Emulator) for simulating ARM-based environments. The tasks in this lab should be executed in the following environment:

- **QEMU**: Virtual machine to simulate ARM architecture.
- **Linux OS**: Used as the host machine for cross-compiling and kernel building.

Ensure that you have QEMU set up and ready before proceeding with the tasks.

---

## QEMU Setup

To set up QEMU and create a virtual ARM machine, follow the instructions provided in the **QEMU_ARM_Installation_Instructions.pdf**. This document contains all the necessary steps to download the required disk images, set up the virtual machine, and launch it properly.

---

## Repository Contents

1. **final_image_kernel**:
   - Contains the final kernel image after the build process.
   
2. **question3_programm**:
   - Contains the source code for the third question of the exercise.

3. **source_files_changed_kernel**:
   - Contains the modified kernel source files used during the cross-compilation process.

4. **[Exercise6.pdf](#)**:
   - A detailed document with step-by-step instructions for completing the exercises.

5. **builddeb_hf.patch**:
   - A patch file used to build the Debian image with the `hf` architecture.

6. **kernel_config**:
   - A pre-configured kernel configuration file to be used for building the kernel.

7. **[lab6-report-1.pdf](#)**:
   - A report document providing details of the progress and results from the exercise.

8. **phods.c**:
   - Contains the C source code for the `phods` program, used in the exercises.

9. **sources.list**:
   - Contains the package repository configuration used in the virtual machine environment.


## Task Overview

### Task 1: Setting Up QEMU for ARM
Set up an ARM virtual machine with QEMU to simulate an ARM environment, allowing you to test cross-compiled software on a virtual ARM system.

### Task 2: Installing the Custom Cross-Compiler Toolchain with crosstool-ng
Build and configure a custom cross-compiling toolchain using crosstool-ng for ARM to create executable binaries on a different architecture.
