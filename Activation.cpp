#include "Activation.h"

/**
 * @namespace activation
 * @brief Contains activation functions for neural networks.
 */
namespace activation
{
// todo: modify x instead of copying new matrix?

    /**
     * @brief Applies the ReLU activation function to each element of the input matrix.
     *
     * For each element, if it is greater than or equal to zero, it is kept;
     * otherwise, it is set to zero.
     *
     * @param x The input matrix.
     * @return Matrix The result matrix after applying ReLU.
     */
    Matrix relu (const Matrix &x)
    {
      Matrix result_mat (x.get_rows (), x.get_cols ());
      for (int i = 0; i < x.get_rows () * x.get_cols (); ++i)
      {
        if (x[i] >= 0)
        {
          result_mat[i] = x[i];
        }
        // else: leave it as 0.
      }
      return result_mat;
    }

    /**
     * @brief Applies the Softmax activation function to the input matrix.
     *
     * Calculates the exponential of each element, normalizes by the sum of all exponentials.
     *
     * @param x The input matrix.
     * @return Matrix The result matrix after applying Softmax.
     */
    Matrix softmax (const Matrix &x)
    {
      Matrix vector_exp (x.get_rows (), x.get_cols ());
      for (int k = 0; k < x.get_rows () * x.get_cols (); ++k)
      {
        vector_exp[k] = exp (x[k]);
      }
      float c = 1 / vector_exp.sum ();
      return vector_exp * c;
    }
}