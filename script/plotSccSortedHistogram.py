# First argument: metric to plot (complexity or complexity/code)
# Second argument: input file
# Third argument: legend to show (ChatGPT or Human)
# Examples:
# python3 plotSortedComplexityCode.py complexity/code ../src/output.txt ChatGPT
# python3 plotSortedComplexityCode.py complexity ../src/output2.txt Human

import matplotlib.pyplot as plt
import numpy as np
import argparse

# Function to parse the input text
def parse_input(input_text):
    entries = [x.strip() for x in input_text.split("----------------------------------------------------------------------------------------------------------------------------------------------------------------")]
    file_data = []

    for entry in entries:
        if "Processing" in entry:
            lines = entry.splitlines()
            file_name = lines[0].split("Processing ")[1].split("...")[0].strip()
            for line in lines:
                if line.strip().startswith("Total"):
                    parts = line.split()
                    code = int(parts[-2])
                    complexity = int(parts[-1])
                    complexity_per_code = round (complexity / code, 2)
                    file_data.append((file_name, complexity, complexity_per_code))
    return file_data

# Function to plot the data
def plot_data(file_data, metric, legend):
    # Sort the first file data by the selected metric
    if metric == 'complexity':
        file_data.sort(key=lambda x: x[1])
        y_index = 1
    elif metric == 'complexity/code':
        file_data.sort(key=lambda x: x[2])
        y_index = 2
        
    if legend == 'ChatGPT':
        color = 'royalblue'
    elif legend == 'Human':
        color = 'sandybrown'
    


    # Prepare data for plotting
    file_names = [data[0] for data in file_data]
    y_values = [data[y_index] for data in file_data]

    # Plotting the histogram
    x = np.arange(len(file_names))
    width = 0.4 # Width of the bars

    # Set figure size for A4 paper in double column format
    # fig_width = 8.27 / 2  # A4 width in inches (8.27) divided by 2 for double column
    # fig_height = 11.69 / 3  # A4 height in inches (11.69) divided by 3 for suitable aspect ratio
    # fig, ax = plt.subplots(figsize=(fig_width, fig_height))
    fig, ax = plt.subplots(figsize=(14, 8))  # Width: 14, Height: 8

    # Plotting complexity/code as a histogram
    rects = ax.bar(x - width/2, y_values, width, color=color)

    # Add labels, title, and custom x-axis tick labels
    ax.set_xlabel('File Names')
    ax.set_ylabel(metric)
    ax.set_title(f'{metric} by file ({legend})')
    ax.set_xticks(x)
    ax.set_xticklabels(file_names, rotation=45, ha='right')
    # ax.tick_params(axis='y', labelcolor=color)
    # ax.legend(loc='upper left')

    # Add values on top of the bars
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

    autolabel(rects)

    fig.tight_layout()

    plt.show()

# Main function to handle arguments and plot
def main():
    parser = argparse.ArgumentParser(description='Plot complexity or complexity/code from two input files.')
    parser.add_argument('metric', choices=['complexity', 'complexity/code'], help='Metric to plot: complexity or complexity/code')
    parser.add_argument('input', help='Input file')
    parser.add_argument('legend', choices=['ChatGPT', 'Human'], help='Legend to show: ChatGPT or Human')

    args = parser.parse_args()

    # Read the input from the first file
    with open(args.input, 'r') as file:
        input_text = file.read()

    # Extract data from the input texts
    file_data = parse_input(input_text)

    # Plot the data based on the selected metric
    plot_data(file_data, args.metric, args.legend)

if __name__ == "__main__":
    main()
