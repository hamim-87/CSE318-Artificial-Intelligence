import matplotlib.pyplot as plt
import pandas as pd
from io import StringIO

# Reading the CSV data
csv_data = """criterion,depth,accuracy,nodes
IG,0,0.810216,52067
IG,1,0.758061,3
IG,2,0.822670,7
IG,3,0.841671,15
IGR,0,0.809694,52062
IGR,1,0.760572,3
IGR,2,0.821626,7
IGR,3,0.840396,15
NWIG,0,814471,52059
NWIG,1,0.760563,3
NWIG,2,0.824574,7
NWIG,3,0.840258,15"""

# Loading CSV data into a DataFrame
df = pd.read_csv(StringIO(csv_data))

# Preparing data for plotting
criteria = df['criterion'].unique()  # IG, IGR, NWIG
depths = sorted(df['depth'].unique())  # 0, 1, 2, 3
bar_width = 0.25  # Width of each bar
x = range(len(depths))  # X-axis positions for depths

# Setting up the plot
plt.figure(figsize=(10, 6))

# Plotting bars for each criterion
for i, criterion in enumerate(criteria):
    # Filtering data for the current criterion
    criterion_data = df[df['criterion'] == criterion]
    nodes = [criterion_data[criterion_data['depth'] == depth]['nodes'].values[0] for depth in depths]
    
    # Plotting bars with offset for each criterion
    plt.bar([pos + i * bar_width for pos in x], nodes, bar_width, label=criterion)

# Customizing the plot
plt.xlabel('Depth')
plt.ylabel('Number of Nodes')
plt.title('Number of Nodes vs Depth for Iris Dataset')
plt.xticks([pos + bar_width for pos in x], depths)  # Center ticks under grouped bars
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

# Adjusting layout to prevent label cutoff
plt.tight_layout()

# Displaying the plot
plt.show()