import matplotlib.pyplot as plt
import numpy as np

# Data for speedup and estimation
labels = ['Without Optimization', 'Unrolling 4-2', 'Partial Pip', 'Full Pip', 'Full Pip Unrol 4', 
          'Full Pip Unrol 4 Array Part 4', 'Full Pip Unrol 4 Array Part 16', 'Full Pip Unrol 4 Array Part 2',
          'Full Pip Unrol 8 Array Part 16', 'Full Pip Unrol 32 Array Part 32']

speedup_values = [0.42, 0.76, 1.34, 0, 0, 2.76, 2.76, 2.7, 0, 2.76]
estimation_values = [3264697, 1806341, 1014225, 482590, 482486, 482408, 482382, 482538, 482492, 482486]



# Set positions for the bars
x = np.arange(len(labels))

# Create figure and axes
fig, ax1 = plt.subplots(figsize=(12, 6))

# Plot the first set of bars (speedup)
bar_width = 0.35
bars1 = ax1.bar(x - bar_width / 2, speedup_values, bar_width, color='b', alpha=0.6, label='Speedup')

# Create second axis for estimation values
ax2 = ax1.twinx()
bars2 = ax2.bar(x + bar_width / 2, estimation_values, bar_width, color='r', alpha=0.6, label='Estimation (CC)')

# Set axis labels
ax1.set_xlabel('Configurations')
ax1.set_ylabel('Speedup', color='b')
ax2.set_ylabel('Estimation (CC)', color='r')

# Set x-axis labels and title
ax1.set_xticks(x)
ax1.set_xticklabels(labels, rotation=45, ha='right')  # Rotate x labels for better readability
plt.title('Speedup and Estimation Comparison for Different Optimizations')

# Add legends
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')

# Add annotations for speedup
for bar in bars1:
    height = bar.get_height()
    ax1.text(bar.get_x() + bar.get_width() / 2, height, f'{height:.2f}', 
             ha='center', va='bottom', color='b', fontsize=10)

# Add annotations for estimation
for bar in bars2:
    height = bar.get_height()
    ax2.text(bar.get_x() + bar.get_width() / 2, height, f'{height:.0f}', 
             ha='center', va='bottom', color='r', fontsize=10)

# Show plot
plt.tight_layout()
plt.show()
