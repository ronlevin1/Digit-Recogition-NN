// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#define N_ZERO_DOT1 0.1

#include <iostream>

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims
{
    int rows, cols;
};

class Matrix
{
 public:
  // Constructors
  Matrix () : rows (1), cols (1), mat (new float[1] ())
  {};
  Matrix (int _rows, int _cols);
  Matrix (const Matrix &other); // Copy constructor
  ~Matrix (); // destructor

  // Methods & Funcs
  int get_rows () const;
  int get_cols () const;
  Matrix &transpose ();
  Matrix& vectorize ();
  void plain_print () const;
  Matrix dot (Matrix &other);
  float norm () const;
  Matrix rref () const;
  int argmax () const;
  float sum () const;

  // Operators
  Matrix &operator+= (const Matrix &other);
  Matrix operator+ (const Matrix &other) const;
  Matrix &operator= (const Matrix &other);
  Matrix operator* (const Matrix &other) const;
  Matrix operator* (float c) const; // prefix
  friend Matrix operator* (float c, const Matrix &m); // postfix
  float &operator() (int i, int j);
  float operator() (int i, int j) const;
  float &operator[] (int k);
  float operator[] (int k) const;
  friend std::ostream &operator<< (std::ostream &output_stream, const Matrix &
  m);
  friend std::istream &operator>> (std::istream &input_stream, Matrix &m);

 private:
  int rows{}, cols{};
  float *mat{};
//  void set_rows (int rows);
//  void set_cols (int cols);
};

#endif //MATRIX_H