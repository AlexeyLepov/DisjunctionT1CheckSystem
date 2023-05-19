import time

def read_input_file(file_name):
    arr_var = []
    with open(file_name, 'r') as file:
        current_group = None
        for line in file:
            line = line.strip()
            if line.startswith('#'):
                current_group = [line]
                arr_var.append(current_group)
            else:
                current_group.append(line)
    return arr_var

def check_t1(arr_var):
    for group in arr_var:
        for i in range(1, len(group)):
            expression_parts = group[i].split()
            disjuncts = expression_parts[:-1]
            negations = expression_parts[-1]
            modified_expression = ' '.join(['0' * len(disjunct) for disjunct in disjuncts]) + ' ' + '0' * len(negations)
            group[i] = modified_expression
    return arr_var

def write_output_file(arr_var, file_name):
    with open(file_name, 'w') as file:
        for group in arr_var:
            for line in group:
                file.write(line + '\n')

def calculate_running_time(func, *args):
    start_time = time.time()
    result = func(*args)
    end_time = time.time()
    running_time = end_time - start_time
    return result, running_time

# Main program
input_file = 'disjunctions_input.txt'
output_file = 'disjunctions_result.txt'

# Read from input file
arr_var = read_input_file(input_file)

# Calculate the running time of check_t1 function
result, running_time = calculate_running_time(check_t1, arr_var)
print(f"Running time of check_t1 function: {running_time} seconds")

# Write the result to output file
write_output_file(result, output_file)
