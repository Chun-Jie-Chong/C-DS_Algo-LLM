import os

def extract_fuzzer_stats(directory):
    fuzzer_stats = {
        "unique_crashes": "N/A",
        "unique_hangs": "N/A",
        "afl_banner": "N/A"
    }
    fuzzer_stats_path = os.path.join(directory, "findings", "fuzzer_stats")
    if os.path.exists(fuzzer_stats_path):
        with open(fuzzer_stats_path, 'r') as file:
            for line in file:
                key, value = line.strip().split(":", 1)
                key = key.strip()
                value = value.strip()
                if key in ["unique_crashes", "unique_hangs", "afl_banner"]:
                    fuzzer_stats[key] = value
    return fuzzer_stats

def process_directory_of_folders(root_directory):
    all_stats = []
    for folder_name in os.listdir(root_directory):
        folder_path = os.path.join(root_directory, folder_name)
        if os.path.isdir(folder_path):
            fuzzer_stats = extract_fuzzer_stats(folder_path)
            all_stats.append(fuzzer_stats)
    return all_stats

def write_stats_to_file(stats, output_file):
    with open(output_file, 'w') as file:
        for stat in stats:
            file.write(f"afl_banner: {stat['afl_banner']}\n")
            file.write(f"unique_crashes: {stat['unique_crashes']}\n")
            file.write(f"unique_hangs: {stat['unique_hangs']}\n")
            file.write("---------------------------------------------\n")

def main():
    root_directory = "../AFL"  # Replace with the path to your root directory
    output_file = "extracted_fuzzer_stats.txt"
    all_stats = process_directory_of_folders(root_directory)
    write_stats_to_file(all_stats, output_file)

if __name__ == "__main__":
    main()
