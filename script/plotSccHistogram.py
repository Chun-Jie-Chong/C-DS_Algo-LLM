import matplotlib.pyplot as plt
import numpy as np

# Function to parse the input text
def parse_input(input_text):
    entries = [x.strip() for x in input_text.split("----------------------------------------------------------------------------------------------------------------------------------------------------------------")]
    print(entries)
    file_data = []

    for entry in entries:
        if "Processing" in entry:
            entry.strip()
            lines = entry.splitlines()
            file_name = lines[0].split("Processing ")[1].split("...")[0].strip()
            for line in lines:
                if line.strip().startswith("Total"):
                    parts = line.split()
                    code = int(parts[-2])
                    complexity = int(parts[-1])
                    complexity_per_code = round (complexity / code, 2)
                    print(file_name, complexity, complexity_per_code)
                    file_data.append((file_name, complexity, complexity_per_code))
    return file_data

# Read the input from a file
with open('../src/output.txt', 'r') as file:
    input_text = file.read()

# Extract data from the input text
file_data = parse_input(input_text)

# Prepare data for plotting
file_names = [data[0] for data in file_data]
complexities = [data[1] for data in file_data]
complexity_per_code = [data[2] for data in file_data]

# Plotting the histogram
x = np.arange(len(file_names))
width = 0.35

fig, ax1 = plt.subplots(figsize=(14, 8))  # Width: 14, Height: 8
#fig, ax1 = plt.subplots()
# Plotting complexities on the primary y-axis (left side)
rects1 = ax1.bar(x - width/2, complexities, width, label='Complexity', color='royalblue')
ax1.set_xlabel('File Names')
ax1.set_ylabel('Complexity', color='royalblue')
ax1.set_title('Code Complexity (LLM)')
ax1.set_xticks(x)
ax1.tick_params(axis='x', rotation=70)
ax1.set_xticklabels(file_names)
ax1.legend(loc='upper left')

# Creating a secondary y-axis (right side) for complexity/code
ax2 = ax1.twinx()
rects2 = ax2.bar(x + width/2, complexity_per_code, width, label='Complexity/Code', color='sandybrown')
ax2.set_ylabel('Complexity/LOC', color='sandybrown')
ax2.legend(loc='upper right')

# Add values on top of the bars
def autolabel(rects, ax):
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1, ax1)
autolabel(rects2, ax2)

fig.tight_layout()

plt.show()
