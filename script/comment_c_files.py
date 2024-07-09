import os

def comment_c_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    in_comment_block = True
    output_lines = []

    for line in lines:
        stripped_line = line.strip()
        if stripped_line == "```c":
            in_comment_block = False
            output_lines.append(f"/* {stripped_line} */\n")
        elif stripped_line == "```":
            in_comment_block = True
            output_lines.append(f"/* {stripped_line} */\n")
        elif in_comment_block:
            output_lines.append(f"/* {line.rstrip()} */\n")
        else:
            output_lines.append(line)

    with open(file_path, 'w') as file:
        file.writelines(output_lines)

def process_directory(directory_path):
    for root, _, files in os.walk(directory_path):
        for file in files:
            if file.endswith(".c"):
                file_path = os.path.join(root, file)
                comment_c_file(file_path)

# Replace 'your_directory_path' with the actual path to your directory
directory_path = '../src'
process_directory(directory_path)
