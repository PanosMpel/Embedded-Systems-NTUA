# We use the script below to find the pareto optimal solutions 
# based on the results we took from exhaustive search we did previously
# The results of the exhaustive search are saved on this file "simulation_results.csv".

import pandas as pd
from paretoset import paretoset

data = pd.read_csv('simulation_results.csv')

# Afairesi tou kB apo tis stiles
def convert_memory_size(size):
        return int(size.replace('kB', '').strip())

data['L1I_Size'] = data['L1I_Size'].apply(convert_memory_size)
data['L1D_Size'] = data['L1D_Size'].apply(convert_memory_size)
data['L2_Size'] = data['L2_Size'].apply(convert_memory_size)

# Compute the total memory
data['totalMemoryKB'] = data['L1I_Size'] + data['L1D_Size'] + data['L2_Size']

# Define the objectives: minimize both CPU_Cycles and totalMemoryKB
objectives = ['CPU_Cycles', 'totalMemoryKB']

# Find the Pareto frontier
pareto_mask = paretoset(data[objectives], sense=["min", "min"])

pareto_front = data[pareto_mask].sort_values(by=['CPU_Cycles', 'totalMemoryKB'], ascending=[True, True])

print("Pareto-optimal combinations:")
print(pareto_front)
pareto_front.to_csv('pareto_frontier.csv', index=False)
