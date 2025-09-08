#include "Matrix.h"
#include "MlpNetwork.h"

/**
 * @brief Construct a new MlpNetwork object.
 *
 * Initializes the four Dense layers with provided weights and biases.
 * The first three layers use ReLU activation, the fourth uses Softmax.
 *
 * @param _weights Array of weight matrices for each layer.
 * @param _biases Array of bias matrices for each layer.
 */
MlpNetwork::MlpNetwork (Matrix *_weights, Matrix *_biases) :
    layer1 (_weights[0], _biases[0], activation::relu),
    layer2 (_weights[1], _biases[1], activation::relu),
    layer3 (_weights[2], _biases[2], activation::relu),
    layer4 (_weights[3], _biases[3], activation::softmax)
{}

/**
 * @brief Applies the MLP network to the input image matrix (non-const version).
 *
 * Passes the input through four Dense layers, finds the index of the maximum output,
 * and returns a digit struct containing the index and value.
 *
 * @param img Input image matrix.
 * @return digit Struct containing the predicted digit and its probability.
 */
digit MlpNetwork::operator() (Matrix &img)
{
  // input (x): Matrix of image (actually a vector - img.vectorize()).
  // 1. build array Dense[4]. first 3 use Relu, 4th uses softmax
  //  Dense layers[MLP_SIZE] = {layer1, layer2, layer3, layer4};
  // 2. calculate each layers output: prev output -> next input
  Matrix r1 = layer1 (img);
  Matrix r2 = layer2 (r1);
  Matrix r3 = layer3 (r2);
  Matrix r4 = layer4 (r3);
  // network output: vector of 10 digits
  // 3a. find max in output vector
  unsigned int max_idx = r4.argmax ();
  // 3b. return index and value as digit struct.
  digit result = {max_idx, r4[max_idx]};
  return result;
}

/**
 * @brief Applies the MLP network to the input image matrix (const version).
 *
 * Passes the input through four Dense layers, finds the index of the maximum output,
 * and returns a digit struct containing the index and value.
 *
 * @param img Input image matrix.
 * @return digit Struct containing the predicted digit and its probability.
 */
digit MlpNetwork::operator() (Matrix &img) const
{
  // input (x): Matrix of image (actually a vector - img.vectorize()).
  Matrix r1 = layer1 (img);
  Matrix r2 = layer2 (r1);
  Matrix r3 = layer3 (r2);
  Matrix r4 = layer4 (r3);
  // network output: vector of 10 digits
  // 3a. find max in output vector
  unsigned int max_idx = r4.argmax ();
  // 3b. return index and value as digit struct.
  digit result = {max_idx, r4[max_idx]};
  return result;
}
