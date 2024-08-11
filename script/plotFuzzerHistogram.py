import matplotlib.pyplot as plt
import numpy as np
import argparse

def parse_file(input_text):
    entries = input_text.strip().split('---------------------------------------------')
    parsed_data = []

    for entry in entries:
        lines = entry.strip().split('\n')
        entry_data = {}
        for line in lines:
            if line:
                key, value = line.split(': ')
                if key in ["unique_crashes", "unique_hangs", "afl_banner"]:
                    entry_data[key] = value
        parsed_data.append(entry_data)

    # print(parsed_data)
    return parsed_data

def plot_histogram(chatgpt_data, human_data, metric):
    chatgpt_data.sort(key=lambda x: x[metric])
    
    file_names1 = [data['afl_banner'] for data in chatgpt_data]
    y1_values = [int(data[metric]) for data in chatgpt_data]
    
    # Create a dictionary for the second file data for easy lookup
    human_data_dict = {data['afl_banner']: int(data[metric]) for data in human_data}
    
    # Align the second file data to the sorted file names of the first file
    y2_values = [human_data_dict.get(file_name, 0) for file_name in file_names1]

    # Plotting the histograms
    x = np.arange(len(file_names1))
    width = 0.4

    fig, ax = plt.subplots(figsize=(14, 8))  # Width: 14, Height: 8
    rects1 = ax.bar(x - width/2, y1_values, width, color='royalblue', label='ChatGPT')
    rects2 = ax.bar(x + width/2, y2_values, width, color='sandybrown', label='Human')

    ax.set_xlabel('File Names')
    ax.set_ylabel('Count')
    ax.set_title(f'{metric} (sorted based on ChatGPT)')
    ax.set_xticks(x)
    ax.set_xticklabels(file_names1, rotation=45, ha='right')
    ax.legend(loc='upper left')
    
    
    # Add values on top of the bars
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')
            
    autolabel(rects1)
    autolabel(rects2)
    
    fig.tight_layout()
    plt.show()
def main():
    parser = argparse.ArgumentParser(description='Plot fuzzer from two input files.')
    parser.add_argument('metric', choices=['unique_crashes', 'unique_hangs'], help='Metric to plot: unique crashes or unique hangs')
    parser.add_argument('input1', help='First input file')
    parser.add_argument('input2', help='Second input file')

    args = parser.parse_args()

    # Read the input from the first file
    with open(args.input1, 'r') as file1:
        input_text1 = file1.read()

    # Read the input from the second file
    with open(args.input2, 'r') as file2:
        input_text2 = file2.read()

    # Extract data from the input texts
    file_data1 = parse_file(input_text1)
    file_data2 = parse_file(input_text2)

    # Plot the data based on the selected metric
    plot_histogram(file_data1, file_data2, args.metric)


if __name__ == "__main__":
    main()
