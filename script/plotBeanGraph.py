# plot two bean graphs side by side (chatgpt vs human)
# first argument: complexity or complexity/code
# second argument: chatgpt output file
# third argument: human output file

# Example usage:
# python3 script_name.py complexity scc_chatgpt.txt scc_human.txt

import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd
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
                    complexity_per_code = complexity / code
                    file_data.append((file_name, complexity, complexity_per_code, code))
    return file_data

def parse_ternary_operator(input_text):
    entries = [x.strip() for x in input_text.splitlines()]
    file_data = []

    for entry in entries:
        parts = entry.split(':')
        file_name = parts[0]
        complexity = int(parts[1])
        file_data.append((file_name, complexity))
    return file_data

# Function to plot the data
def plot_data(file_data1, file_data2, ternary_1, ternary_2, metric):
    # Match file name in file_data1 with ternary_1 and add complexity from ternary_1 to file_data1
    for i, data in enumerate(file_data1):
        file_name = data[0]
        for data2 in ternary_1:
            if data2[0] == file_name:
                newComplexity = data2[1] + data[1]
                newComplexityPerCode = round(newComplexity / data[3], 2)
                file_data1[i] = (file_name, newComplexity, newComplexityPerCode, data[3])
                break
    # Match file name in file_data2 with ternary_2 and add complexity from ternary_2 to file_data2
    for i, data in enumerate(file_data2):
        file_name = data[0]
        for data2 in ternary_2:
            if data2[0] == file_name:
                newComplexity = data2[1] + data[1]
                newComplexityPerCode = round(newComplexity / data[3], 2)
                file_data2[i] = (file_name, newComplexity, newComplexityPerCode, data[3])
                break
    if metric == 'complexity':
        y_index = 1
    elif metric == 'complexity/code':
        y_index = 2
    
    # Actual data arrays
    group_a = [data[y_index] for data in file_data1]
    group_b = [data[y_index] for data in file_data2]

    # Combine the data into a DataFrame
    data = pd.DataFrame({
        'Value': group_a + group_b,
        'Group': ['ChatGPT-4o'] * len(group_a) + ['Human'] * len(group_b)
    })

    # Create the bean plot (violin plot)
    plt.figure(figsize=(8, 6))
    sns.violinplot(x='Group', y='Value', data=data, inner="point", density_norm="width", bw_adjust=0.5, hue="Group", palette={'ChatGPT-4o': 'royalblue', 'Human': 'sandybrown'})

    # Add labels and title
    plt.xlabel('Group')
    plt.ylabel('Value')
    plt.title(f'DS & Algo {metric} by group'.capitalize())

    # Display the plot
    plt.show()


# Main function to handle arguments and plot
def main():
    parser = argparse.ArgumentParser(description='Plot complexity or complexity/code from two input files.')
    parser.add_argument('metric', choices=['complexity', 'complexity/code'], help='Metric to plot: complexity or complexity/code')
    parser.add_argument('input1', help='First input file')
    parser.add_argument('input2', help='Second input file')
    parser.add_argument('input3', help='Third input file')
    parser.add_argument('input4', help='Forth input file')

    args = parser.parse_args()

    # Read the input from the first file
    with open(args.input1, 'r') as file1:
        input_text1 = file1.read()

    # Read the input from the second file
    with open(args.input2, 'r') as file2:
        input_text2 = file2.read()
        
    # Read the input from the third file
    with open(args.input3, 'r') as file3:
        input_text3 = file3.read()
    
    # Read the input from the forth file
    with open(args.input4, 'r') as file4:
        input_text4 = file4.read()

    # Extract data from the input texts
    file_data1 = parse_input(input_text1)
    file_data2 = parse_input(input_text2)
    ternary_1 = parse_ternary_operator(input_text3)
    ternary_2 = parse_ternary_operator(input_text4)

    # Plot the data based on the selected metric
    plot_data(file_data1, file_data2, ternary_1, ternary_2, args.metric)

if __name__ == "__main__":
    main()

