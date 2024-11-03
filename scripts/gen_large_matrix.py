import numpy as np
import sys

def generate_matrix_with_determinant(size, target_det):
    # Step 1: Initialize diagonal matrix with values that produce the target determinant
    diag_values = np.ones(size)
    diag_values[0] = target_det  # Set the first value to target_det
    matrix = np.diag(diag_values)

    # Step 2: Randomize with determinant-preserving operations
    for _ in range(size * 10):  # Repeat enough times to randomize the matrix
        row1, row2 = np.random.randint(0, size, 2)
        col1, col2 = np.random.randint(0, size, 2)
        
        if row1 != row2:
            factor = np.random.uniform(-1, 1)
            matrix[row1] += factor * matrix[row2]
        
        if col1 != col2:
            factor = np.random.uniform(-1, 1)
            matrix[:, col1] += factor * matrix[:, col2]

    # Check if the determinant is close to the target (for verification)
    det = np.linalg.det(matrix)
    print(f"Generated matrix determinant: {det:.5f} (target: {target_det})")
    
    return matrix

def generate_large_integer_matrix(size, min_value=1, max_value=2):
    # Create a diagonal matrix filled with a mix of ones and twos
    diagonal_values = np.random.choice([1, 1], size=size)
    matrix = np.diag(diagonal_values)

    # Randomly add rows to each other to make the matrix appear more random
    for _ in range(size * 5):  # Perform a number of random additions
        row1, row2 = np.random.choice(size, 2, replace=False)
        matrix[row1] += matrix[row2]  # Add row2 to row1

    return matrix

def save_matrix_with_size(matrix, filename):
    size = matrix.shape[0]
    flattened_matrix = matrix.flatten()

    with open(filename, 'w') as f:
        flattened_matrix = matrix.flatten()
        f.write(" ".join(f"{value}" for value in flattened_matrix))

    # Read the matrix data we just saved
    with open(filename, 'r+') as f:
        content = f.read()
        # Move to the beginning of the file and write the size, then the content
        f.seek(0, 0)
        f.write(f"{size} " + content)

def save_determinant_result(det, filename):
    with open(filename, 'w') as f:
        f.write(f"{det:.5f}\n")

if __name__ == "__main__":
    # Check for the correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python script.py <size> <target_det>")
        sys.exit(1)

    # Get the size and target determinant from command-line arguments
    size = int(sys.argv[1])
    target_det = int(sys.argv[2])

    # Generate the matrix
    matrix = generate_large_integer_matrix(size)

    # Optional: Save matrix to a file if needed
    file_path = f"tests/data/matrix_{size}x{size}"

    save_matrix_with_size(matrix, file_path + ".dat")
    save_determinant_result(np.linalg.det(matrix), file_path + ".ans")
