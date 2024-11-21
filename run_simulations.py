# The script below does an exhaustive search to find the all the run times for every 
# possible combination of L1I_size,L1D_size,L2_size,Unroll_factor)
# specifically for the tables.c file. The script takes ~3hours to run so be patient!
# When the script ends it saves the results in a .csv file named simulation_results.csv


import subprocess
import csv
import os

# Define cache sizes and unrolling factors
L1I_SIZES = ["2kB", "4kB", "8kB", "16kB", "32kB", "64kB"]
L1D_SIZES = ["2kB", "4kB", "8kB", "16kB", "32kB", "64kB"]
L2_SIZES = ["128kB", "256kB", "512kB", "1024kB"]
UNROLL_FACTORS = [2, 4, 8, 16, 32]

# Output CSV file in the /gem5 directory
OUTPUT_FILE = "/gem5/simulation_results.csv"

# Write the header of the CSV
with open(OUTPUT_FILE, mode="w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["L1I_Size", "L1D_Size", "L2_Size", "Unrolling_Factor", "CPU_Cycles"])

# Function to run the simulation and extract CPU cycles from stats.txt
def run_simulation(L1I_SIZE, L1D_SIZE, L2_SIZE, UNROLL_FACTOR):
    command = [
        "build/X86/gem5.opt",
        "configs/learning_gem5/part1/two_level.py",
        f"/gem5/tables_UF/tables_uf{UNROLL_FACTOR}.exe",
        f"--l1i_size={L1I_SIZE}",
        f"--l1d_size={L1D_SIZE}",
        f"--l2_size={L2_SIZE}"
    ]

    try:
        subprocess.run(command, capture_output=True, text=True, check=True)
        stats_file = "/gem5/m5out/stats.txt"

        # Check if the stats.txt file exists after running the simulation
        if os.path.isfile(stats_file):
            with open(stats_file, "r") as file:
                for line in file:
                    if "system.cpu.numCycles" in line:
                        # Extract CPU cycles from the line
                        cpu_cycles = int(line.split()[1])
                        return cpu_cycles
        else:
            print("Error: stats.txt not found in m5out directory.")
            return None

    except subprocess.CalledProcessError as e:
        print(f"Error running simulation for {L1I_SIZE}, {L1D_SIZE}, {L2_SIZE}, {UNROLL_FACTOR}: {e}")
        return None

# Loop through all combinations of cache sizes and unrolling factors
for L1I_SIZE in L1I_SIZES:
    for L1D_SIZE in L1D_SIZES:
        for L2_SIZE in L2_SIZES:
            for UNROLL_FACTOR in UNROLL_FACTORS:
                print(f"Running simulation for L1I: {L1I_SIZE}, L1D: {L1D_SIZE}, L2: {L2_SIZE}, Unroll: {UNROLL_FACTOR}")

                cpu_cycles = run_simulation(L1I_SIZE, L1D_SIZE, L2_SIZE, UNROLL_FACTOR)

if cpu_cycles is not None:
                    with open(OUTPUT_FILE, mode="a", newline="") as file:
                        writer = csv.writer(file)
                        writer.writerow([L1I_SIZE, L1D_SIZE, L2_SIZE, UNROLL_FACTOR, cpu_cycles])

print("Simulation complete. Results saved to", OUTPUT_FILE)

