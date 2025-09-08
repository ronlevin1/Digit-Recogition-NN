#include "Matrix.h"
#include <cmath>

// todo: documentation.

/** ------------------------ GETTERS ------------------------ */

/**
 * @brief Get the number of rows in the matrix.
 * @return Number of rows.
 */
int Matrix::get_rows () const
{
  return rows;
}

/**
 * @brief Get the number of columns in the matrix.
 * @return Number of columns.
 */
int Matrix::get_cols () const
{
  return cols;
}

/** ------------------------ CONSTRUCTORS ------------------------ */

/**
 * @brief Construct a new Matrix object with given dimensions.
 * @param _rows Number of rows.
 * @param _cols Number of columns.
 * @throws std::exception if dimensions are not positive.
 */
Matrix::Matrix (int _rows, int _cols)
{
  if (_rows <= 0 || _cols <= 0)
  {
    throw std::exception ();
  }
  rows = _rows;
  cols = _cols;
//  float *temp = new float[_rows * _cols] ();
  mat = new float[_rows * _cols] ();
}

/**
 * @brief Copy constructor for Matrix.
 * @param other Matrix to copy from.
 */
Matrix::Matrix (const Matrix &other)
{
  rows = other.get_rows ();
  cols = other.get_cols ();
  delete[] mat;
  mat = new float[rows * cols] ();
  for (int i = 0; i < rows * cols; ++i)
  {
    mat[i] = other.mat[i];
  }
}

/**
 * @brief Destructor for Matrix. Frees allocated memory.
 */
Matrix::~Matrix ()
{
  delete[] this->mat;
}

/** ------------------------ METHODS ------------------------ */

/**
 * @brief Transpose the matrix in place.
 * @return Reference to the transposed matrix.
 */
Matrix &Matrix::transpose ()
{
  float *t_mat = new float[rows * cols];
  Matrix copy_mat = Matrix (*this);
  std::swap (rows, cols);
  // Copy data from the original matrix to the transposed matrix
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      // rows = output_matrix cols (after swap).
      t_mat[i * cols + j] = copy_mat (j, i); //mat[j * rows + i];
    }
  }
  delete[] mat;
  mat = t_mat;
  return *this;
}

/**
 * @brief Vectorize the matrix (reshape to a column vector).
 * @return Reference to the vectorized matrix.
 */
Matrix &Matrix::vectorize ()
{
  int temp = rows;
  rows = temp * cols;
  cols = 1;
  return *this;
//  std::swap (rows, cols);
}

/**
 * @brief Print the matrix in plain format.
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Element-wise multiplication (Hadamard product) with another matrix.
 * @param other Matrix to multiply with.
 * @return Resulting matrix.
 * @throws std::exception if dimensions do not match.
 */
Matrix Matrix::dot (Matrix &other)
{
  if (rows != other.get_rows () || cols != other.get_cols ())
  {
    throw std::exception ();
  }
//  float *result_mat = new float[rows * cols];
  Matrix result_mat (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      result_mat (i, j) = (*this) (i, j) * other (i, j);
    }
  }
  return result_mat;
}

/**
 * @brief Compute the Frobenius norm of the matrix.
 * @return Norm value.
 */
float Matrix::norm () const
{
  float norm = 0;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      norm += (*this) (i, j) * (*this) (i, j);
    }
  }
  return sqrt (norm);
}

/**
 * @brief Compute the Reduced Row Echelon Form (RREF) of the matrix.
 * @return Matrix in RREF.
 */
Matrix Matrix::rref () const
{
  Matrix rref_matrix (*this); // Make a copy of the current matrix
  int lead = 0;
  struct matrix_dims mtx_dims = {rref_matrix.rows, rref_matrix.cols};
  for (int row = 0; row < mtx_dims.rows; ++row)
  {
    if (mtx_dims.cols <= lead)
    {
      break;
    }
    int i = row;
    while (rref_matrix (i, lead) == 0)
    {
      ++i;
      if (mtx_dims.rows == i)
      {
        i = row;
        ++lead;
        if (mtx_dims.cols == lead)
        {
          return rref_matrix;
        }
      }
    }
    if (i != row) // Swap rows i and row
    {
      for (int j = 0; j < mtx_dims.cols; ++j)
      {
        std::swap (rref_matrix (i, j), rref_matrix (row, j));
      }
    }
    float div = rref_matrix (row, lead);// Scale the row so that lead is 1
    for (int j = 0; j < mtx_dims.cols; ++j)
    {
      rref_matrix (row, j) /= div;
    }
    for (i = 0; i < mtx_dims.rows; ++i)
    {                  // Eliminate non-zero elements above and below the lead
      if (i != row)
      {
        float factor = rref_matrix (i, lead);
        for (int j = 0; j < mtx_dims.cols; ++j)
        {
          rref_matrix (i, j) -= factor * rref_matrix (row, j);
        }
      }
    }
    ++lead;
  }
  return rref_matrix;
}

/**
 * @brief Get the index of the maximum element in the matrix.
 * @return Index of the maximum element.
 */
int Matrix::argmax () const
{
  float max = mat[0];
  int idx = 0;
  for (int i = 0; i < rows * cols; ++i)
  {
    if (mat[i] > max)
    {
      max = mat[i];
      idx = i;
    }
  }
  return idx;
}

/**
 * @brief Compute the sum of all elements in the matrix.
 * @return Sum of elements.
 */
float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < rows * cols; ++i)
  {
    sum += mat[i];
  }
  return sum;
}

/** ------------------------ OPERATORS ------------------------ */

/**
 * @brief Add another matrix to this matrix (in place).
 * @param other Matrix to add.
 * @return Reference to this matrix.
 * @throws std::exception if dimensions do not match.
 */
Matrix &Matrix::operator+= (const Matrix &other)
{
  if (cols != other.cols || rows != other.rows)
  {
    throw std::exception ();
  }

  for (int i = 0; i < rows * cols; ++i)
  {
    (*this)[i] += other[i];
  }
  return *this;
}

/**
 * @brief Add two matrices.
 * @param other Matrix to add.
 * @return New matrix as the sum.
 * @throws std::exception if dimensions do not match.
 */
Matrix Matrix::operator+ (const Matrix &other) const
{
  if (cols != other.cols || rows != other.rows)
  {
    throw std::exception ();
  }

  Matrix new_mat = Matrix (*this);
  new_mat += other;
  return new_mat;
}

/**
 * @brief Assignment operator.
 * @param other Matrix to assign from.
 * @return Reference to this matrix.
 */
Matrix &Matrix::operator= (const Matrix &other)
{
  if (this == &other)
  {
    return *this;
  }
  rows = other.rows;
  cols = other.cols;

  delete[] mat;
  mat = new float[rows * cols];
  std::copy (other.mat, other.mat + rows * cols, mat);

  return *this;
}

/**
 * @brief Matrix multiplication.
 * @param other Matrix to multiply with.
 * @return Resulting matrix.
 * @throws std::exception if dimensions do not match for multiplication.
 */
Matrix Matrix::operator* (const Matrix &other) const
{
  if (cols != other.rows)
  {
    throw std::exception ();
  }

  Matrix result_mat (rows, other.cols);
  for (int i = 0; i < result_mat.rows; ++i)
  {
    for (int j = 0; j < result_mat.cols; ++j)
    {
      for (int k = 0; k < other.rows; ++k)
      {
        result_mat (i, j) += (*this) (i, k) * other (k, j);
      }
    }
  }
  return result_mat;
}

/**
 * @brief Scalar multiplication (prefix).
 * @param c Scalar value.
 * @return New matrix after multiplication.
 */
Matrix Matrix::operator* (float c) const // prefix
{
  Matrix res = Matrix (*this);
  for (int i = 0; i < res.rows * res.cols; ++i)
  {
    res[i] *= c;
  }
  return res;
//  for (int i = 0; i < rows * cols; ++i)
//  {
//    mat[i] *= c;
//  }
//  return *this;
}

/**
 * @brief Scalar multiplication (postfix).
 * @param c Scalar value.
 * @param m Matrix to multiply.
 * @return New matrix after multiplication.
 */
Matrix operator* (float c, const Matrix &m) // postfix
{
  Matrix res = Matrix (m);
  for (int i = 0; i < m.rows * m.cols; ++i)
  {
    res[i] *= c;
  }
  return res;
}

/**
 * @brief Access matrix element (read-only).
 * @param i Row index.
 * @param j Column index.
 * @return Value at (i, j).
 * @throws std::exception if indices are out of bounds.
 */
float Matrix::operator() (int i, int j) const
{ // for reading purpose only.
  if (i < 0 || i > rows || j < 0 || j > cols)
  {
    throw std::exception ();
  }
  return mat[i * cols + j];
}

/**
 * @brief Access matrix element (read/write).
 * @param i Row index.
 * @param j Column index.
 * @return Reference to value at (i, j).
 * @throws std::exception if indices are out of bounds.
 */
float &Matrix::operator() (int i, int j)
{ // for reading & writing too.
  if (i < 0 || i >= rows || j < 0 || j >= cols)
  {
    throw std::exception ();
  }
  return mat[i * cols + j];
}

/**
 * @brief Access matrix element by linear index (read-only).
 * @param k Linear index.
 * @return Value at index k.
 * @throws std::exception if index is out of bounds.
 */
float Matrix::operator[] (int k) const
{
  if (k < 0 || k >= rows * cols)
  {
    throw std::exception ();
  }
  return mat[k];
}

/**
 * @brief Access matrix element by linear index (read/write).
 * @param k Linear index.
 * @return Reference to value at index k.
 * @throws std::exception if index is out of bounds.
 */
float &Matrix::operator[] (int k)
{
  if (k < 0 || k >= rows * cols)
  {
    throw std::exception ();
  }
  return mat[k];
}

/**
 * @brief Output stream operator for Matrix.
 * @param output_stream Output stream.
 * @param m Matrix to print.
 * @return Reference to output stream.
 */
std::ostream &operator<< (std::ostream &output_stream, const Matrix &m)
{
  for (int i = 0; i < m.rows; ++i)
  {
    for (int j = 0; j < m.cols; ++j)
    {
      if (m (i, j) > N_ZERO_DOT1)
      {
        output_stream << "**";
      }
      else
      {
        output_stream << "  ";
      }
    }
    output_stream << std::endl;
  }
  return output_stream;
}

/**
 * @brief Input stream operator for Matrix.
 * @param input_stream Input stream.
 * @param m Matrix to read into.
 * @return Reference to input stream.
 * @throws std::exception if file is too short or read fails.
 */
std::istream &operator>> (std::istream &input_stream, Matrix &m)
{
  /** NEW version   */
  // get length of file
  input_stream.seekg (0, std::istream::end);
  int file_length = (int) input_stream.tellg ();
  input_stream.seekg (0, std::istream::beg);

  int req_length = m.get_rows () * m.get_cols () * sizeof (float);
  if(file_length < req_length)
  {
    throw std::exception();
  }

  char *buffer = new char[req_length];
  input_stream.read (buffer, req_length);
  if (!input_stream)
  {
    delete[] buffer;
    throw std::exception();
  }
  delete[] m.mat;
  m.mat=(float*) buffer;
  return input_stream;
}
/** Prev version   */
// Read data from input stream into the matrix
//  input_stream.read (reinterpret_cast<char *>(m.mat),
//                     m.get_rows () * m.get_cols () * sizeof (float));
//  // Get the number of characters extracted
//  std::streamsize count = input_stream.gcount ();
//  if (count < m.get_rows () * m.get_cols ())
//  {
//    m = Matrix (m.get_rows (), m.get_cols ()); // reset data
//  }