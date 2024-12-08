import matplotlib.pyplot as plt
import numpy as np

# Data for speedup
labels = ['Without Optimization', 'Unrolling 4-2', 'Partial Pip', 'Full Pip', 'Full Pip Unrol 4', 
          'Full Pip Unrol 4 Array Part 4', 'Full Pip Unrol 4 Array Part 16', 'Full Pip Unrol 4 Array Part 2',
          'Full Pip Unrol 8 Array Part 16', 'Full Pip Unrol 32 Array Part 32', 'Full Pip Array Part 2', 
          'Full Unrol 2 dists_hw[0:1024]']

speedup_values = [0.42, 0.76, 1.34, 0, 0, 2.76, 2.76, 2.7, 0, 2.76, 2.77, 3.97]

# Set positions for the bars
x = np.arange(len(labels))

# Create figure and axes
fig, ax1 = plt.subplots(figsize=(12, 6))

# Plot the first set of bars (speedup)
bar_width = 0.35
bars1 = ax1.bar(x, speedup_values, bar_width, color='b', alpha=0.6, label='Speedup')

# Set axis labels
ax1.set_xlabel('Configurations')
ax1.set_ylabel('Speedup', color='b')

# Set x-axis labels and title
ax1.set_xticks(x)
ax1.set_xticklabels(labels, rotation=45, ha='right')  # Rotate x labels for better readability
plt.title('Speedup  for Different Optimizations')

# Add legends
ax1.legend(loc='upper left')

# Adjust y-axis limits for speedup to increase visual distinction
ax1.set_ylim(0, 4)

# Add annotations for speedup
for bar in bars1:
    height = bar.get_height()
    ax1.text(bar.get_x() + bar.get_width() / 2, height, f'{height:.2f}', 
             ha='center', va='bottom', color='b', fontsize=10)

# Show plot
plt.tight_layout()
plt.show()
