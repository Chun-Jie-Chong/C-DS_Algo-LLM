import matplotlib.pyplot as plt
import numpy as np

def parse_file(filename):
    with open(filename, 'r') as file:
        data = file.read()

    entries = data.strip().split('---------------------------------------------')
    parsed_data = []

    for entry in entries:
        lines = entry.strip().split('\n')
        entry_data = {}
        for line in lines:
            if line:
                key, value = line.split(': ')
                entry_data[key] = value
        parsed_data.append(entry_data)

    # print(parsed_data)
    return parsed_data

def plot_histogram(data):
    afl_banners = [entry['afl_banner'] for entry in data]
    unique_crashes = [int(entry['unique_crashes']) for entry in data]
    unique_hangs = [int(entry['unique_hangs']) for entry in data]

    x = np.arange(len(afl_banners))
    width = 0.35

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width/2, unique_crashes, width, label='Unique Crashes')
    rects2 = ax.bar(x + width/2, unique_hangs, width, label='Unique Hangs')

    ax.set_xlabel('Files')
    ax.set_ylabel('Count')
    ax.set_title('AFL Fuzzer Stats (LLM)')
    ax.set_xticks(x)
    ax.set_xticklabels(afl_banners, rotation=45, ha='right')
    ax.legend()
    autolabel(rects1, ax)
    autolabel(rects2, ax)
    plt.tight_layout()
    plt.show()
    
# Add values on top of the bars
def autolabel(rects, ax):
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')



if __name__ == "__main__":
    filename = 'extracted_fuzzer_stats.txt'
    data = parse_file(filename)
    plot_histogram(data)
