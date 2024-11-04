# String Processing Test Suite

## Project Overview
This project is a comprehensive test suite for a string processing library implemented in C. The main focus is to create, manipulate, and test the behavior of different operations on linked lists of string processing nodes. These nodes apply reversible and irreversible transformations to input strings, enabling complex encoding and decoding workflows. The project demonstrates key aspects of software testing, modular programming, and handling complex data structures.

## Technologies Used
- **Programming Language**: C
- **Libraries**:
  - Standard C Libraries (`stdlib.h`, `string.h`, `stdio.h`, etc.)
  - Custom header files (`string_processor.h`, `string_processor_utils.h`)

## Key Functionalities
### Test Implementations
The project includes detailed test cases for various string processing operations:
1. **Basic Operations**:
   - **Create and Destroy List**: Tests the creation and proper memory cleanup of string processing lists.
   - **Create and Destroy Node**: Ensures that nodes are created with correct function pointers and types and are properly destroyed.
   - **Create and Destroy Key**: Verifies the instantiation and destruction of string processing keys.

2. **Processing Tests**:
   - **Shift Operations (`shift_2`, `unshift_2`)**: Encodes and decodes strings using reversible shifting logic and outputs results.
   - **Position-Based Shifts (`shift_position`, `unshift_position`)**: Tests position-based encoding and decoding for robust string transformations.
   - **Saturation Tests (`saturate_2`, `unsaturate_2`)**: Applies irreversible transformations and verifies output consistency.

3. **Complex Test Combinations**:
   - **Reversible and Irreversible Combinations**: Creates and tests lists with mixed node types, ensuring that encoding and decoding respect node properties.
   - **Inverted and Filtered Lists**: Tests the functionality of copying lists, inverting the node order, and filtering nodes based on reversibility.

4. **Additional Utilities**:
   - **List Length**: Measures the length of a list with varied node counts.
   - **Add and Remove Nodes**: Tests adding and removing nodes at specific positions and validates the resulting list integrity.
   - **Trace Application**: Applies transformations and prints the state of the list during the process for detailed inspection.

## Skills Demonstrated
### 1. **Memory Management**
- Implemented and tested proper allocation and deallocation of dynamic memory.
- Ensured no memory leaks or dangling pointers during list and node operations.

### 2. **Modular Programming**
- Structured the codebase into distinct modules to promote readability and maintainability.
- Employed custom utility functions to support primary operations, showcasing code reusability.

### 3. **Data Structures**
- Developed and managed linked lists containing function pointers and associated metadata.
- Manipulated complex structures with nested operations, verifying the integrity after multiple transformations.

### 4. **Testing and Debugging**
- Built comprehensive test cases that validate individual functions as well as their integration.
- Applied detailed print statements and trace functions to inspect intermediate states and outputs.

---
