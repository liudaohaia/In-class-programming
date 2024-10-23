import numpy as np

# Step 1: String Mapping Conversion
def string_to_numbers(s, mapping):
    return [mapping[char.lower()] for char in s if char.isalpha()]  # Only include letters

# Step 2: Create matrices
def create_matrices(numbers):
    matrices = []
    for i in range(0, len(numbers), 4):
        chunk = numbers[i:i + 4]
        if len(chunk) == 4:
            matrices.append(np.array(chunk).reshape(4, 1))
        else:
            padded_chunk = np.pad(chunk, (0, 4 - len(chunk)), 'constant')
            matrices.append(np.array(padded_chunk).reshape(4, 1))
    return matrices

# Step 3: Matrix multiplication and addition
def matrix_operations(M, A, B):
    return (np.dot(A, M) + B) % 26

# Step 4: Result mapping back to letters
def numbers_to_string(numbers, reverse_mapping):
    return ''.join(reverse_mapping[num] for num in numbers)

# Mapping setup
mapping = {chr(i + 97): i for i in range(26)}  # 'a' to 'z'
reverse_mapping = {i: chr(i + 97) for i in range(26)}  # Reverse mapping

# Input string and matrix definitions
input_string = "PLEASESENDMETHEBOOKMYCREDITCARDNOISSIXONETWOONETHREEEIGHTSIXZEROONESIXEIGHTFOURNINESEVENZEROTWO"
A = np.array([[3, 13, 21, 9], [15, 10, 6, 25], [10, 17, 4, 8], [1, 23, 7, 2]])  # Example 4x4 matrix
B = np.array([[1], [21], [8], [17]])  # Example 4x1 matrix

# Process input
numbers = string_to_numbers(input_string, mapping)
matrices = create_matrices(numbers)

# Calculate and print each result matrix Ci
miweng=''
for M in matrices:
    print("Mi:")
    print(M)

    C = matrix_operations(M, A, B)

    print("Ci:")
    print(C)
    # Map result matrix C back to letters
    letter_string = numbers_to_string(C.flatten().astype(int), reverse_mapping)
    miweng=miweng+letter_string
    print("对应的字母字符串:", letter_string)

print('密文：',miweng)