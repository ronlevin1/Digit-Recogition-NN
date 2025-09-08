# MLP for Handwritten Digit Recognition

This project is a C++ implementation of a Multi-Layer Perceptron (MLP) neural network designed for recognizing handwritten digits. It takes a pre-trained model's weights and biases as input, along with an image file, and predicts the digit shown in the image.

## Core Components

*   **Matrix Class**: A custom `Matrix` class supporting essential operations like addition, multiplication (matrix-matrix, scalar-matrix), transpose, and more.
*   **Activation Functions**: Implements activation functions (ReLU and Softmax) necessary for neural networks.
*   **Dense Layer**: A `Dense` class representing a fully connected layer in the network, which encapsulates weights, biases, and an activation function.
*   **MLP Network**: The `MlpNetwork` class which assembles the dense layers to form the complete network. It handles the forward pass to produce a prediction.
*   **CLI**: A command-line interface (`main.cpp`) for loading the trained model parameters and running inference on user-provided images.

## Project Structure

*   `Matrix.h`, `Matrix.cpp`: Implementation of the Matrix class.
*   `Activation.h`, `Activation.cpp`: Implementation of activation functions.
*   `Dense.h`, `Dense.cpp`: Implementation of a dense layer.
*   `MlpNetwork.h`, `MlpNetwork.cpp`: The main MLP network logic.
*   `main.cpp`: The executable's entry point, handling command-line arguments and user interaction.
*   `parameters/`: Directory containing pre-trained model weights and biases.
*   `images/`: Directory containing sample images for testing.
*   `CMakeLists.txt`, `Makefile`: Build configuration files.

## Building and Running

The project can be built using CMake and Make.

1.  **Navigate to the build directory**:
    ```bash
    cd cmake-build-debug
    ```

2.  **Build the project**:
    ```bash
    make
    ```
    This will create an executable named `mlpnetwork`.

## Usage

To run the network, you must provide the paths to the weight and bias files for each of the 4 layers.

```bash
./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4
```

*   `wi` - path to the i'th layer's weights.
*   `bi` - path to the i'th layer's biases.

For example:
```bash
./mlpnetwork ../parameters/w1 ../parameters/w2 ../parameters/w3 ../parameters/w4 ../parameters/b1 ../parameters/b2 ../parameters/b3 ../parameters/b4
```

After launching, the program will prompt you to enter the path to an image file. The network will then process the image and print the recognized digit and the probability of that prediction.

