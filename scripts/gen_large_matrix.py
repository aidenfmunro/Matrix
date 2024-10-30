import numpy as np

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

def save_matrix_with_size(matrix, filename):
    size = matrix.shape[0]
    flattened_matrix = matrix.flatten()

    with open(filename, 'w') as f:
        flattened_matrix = matrix.flatten()
        f.write(" ".join(f"{value:.9f}" for value in flattened_matrix))

    # Read the matrix data we just saved
    with open(filename, 'r+') as f:
        content = f.read()
        # Move to the beginning of the file and write the size, then the content
        f.seek(0, 0)
        f.write(f"{size} " + content)

def save_determinant_result(det, filename):
    with open(filename, 'w') as f:
        f.write(f"{det:.5f}\n")
# Example usage
size = 10
target_det = 10  # Set target determinant
matrix = generate_matrix_with_determinant(size, target_det)

# Optional: Save matrix to a file if needed
file_path = f"tests/data/matrix_{size}x{size}"

save_matrix_with_size(matrix, file_path + ".dat")
save_determinant_result(target_det, file_path + ".ans")

