// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
 public:
  Dense(const Matrix& _weights, const Matrix& _bias, activation_func
  _activation_f);

  const Matrix &get_weights () const;
  const Matrix &get_bias () const;
  activation_func get_activation () const;

  Matrix operator()(Matrix& x);
  Matrix operator()(Matrix& x) const;


 private:
  const Matrix weights;
  const Matrix bias;
  activation_func activation_f;
};

#endif //DENSE_H