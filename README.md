The Lab1 folder are 2 Lab exercises with the topic: 
Optimizing algorithms for low power consumption and high performance
========================================================================================
In the 1st exersice
The Parallel Hierarchical algorithm will be analyzed 
One Dimensional Search (PHODS), an algorithm belonging to 
media area. The algorithm for PHODS will be in the phods.c file.

We run the programm on the board Renesas S7G2 Microcontroller
We slightly change the given code (phods.c) using some well known transformations 
(Loop Fusion, Loop Unrolling, etc) in order to achieve less clock cycles to run the 
same algorithm. We want to find the best transformations. Also we apply Design Space 
Exploration in order to find the best block size Bx By for which we achieve the best 
performance.

---------------------------------------------------------------------------------------

In the 2nd exersice
We optimize the tables.c file of which 
the operation concerns simple accesses and operations with arrays. The operation of 
tables.c application will run on two different x86 architectures with the help of 
Gem5 simulator. The first architecture concerns a system which it consists of the 
processor and the main memory while the second one has been increased with
L1 Instruction, Data and L2 caches.

We try to find the Pareto Optimal solution for using many different L1I,L1D,L2 caches 
(by changing the architecture of the machine that we run the programm on) and different 
loop unrolling factors on the programm (by 'changing' the loop on the main programm (tables.c))

========================================================================================

To find more information about the research, read --> lab1embedded-report.pdf

Panagiotis Belsis, ECE-NTUA student
