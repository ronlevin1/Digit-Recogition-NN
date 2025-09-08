#include "Matrix.h"
#include "Dense.h"

/**
 * @brief Get the weights matrix of the Dense layer.
 * @return Reference to the weights matrix.
 */
const Matrix &Dense::get_weights () const
{
  return weights;
}

/**
 * @brief Get the bias matrix of the Dense layer.
 * @return Reference to the bias matrix.
 */
const Matrix &Dense::get_bias () const
{
  return bias;
}

/**
 * @brief Get the activation function of the Dense layer.
 * @return The activation function.
 */
activation_func Dense::get_activation () const
{
  return activation_f;
}

/**
 * @brief Apply the Dense layer to the input matrix (non-const version).
 *
 * Computes weights * x + bias, then applies the activation function.
 * @param x Input matrix.
 * @return Output matrix after applying the layer.
 */
Matrix Dense::operator() (Matrix &x)
{
  Matrix input_mat = (weights * x) + bias;
  return activation_f (input_mat);
}

/**
 * @brief Apply the Dense layer to the input matrix (const version).
 *
 * Computes weights * x + bias, then applies the activation function.
 * @param x Input matrix.
 * @return Output matrix after applying the layer.
 */
Matrix Dense::operator() (Matrix &x) const
{
  Matrix input_mat = (weights * x) + bias;
  return activation_f (input_mat);
}

/**
 * @brief Construct a new Dense layer.
 * @param _weights Weights matrix.
 * @param _bias Bias matrix.
 * @param _activation_f Activation function.
 */
Dense::Dense (const Matrix &_weights, const Matrix &_bias,
              activation_func _activation_f)
        : weights (_weights), bias (_bias), activation_f (_activation_f)
{}
