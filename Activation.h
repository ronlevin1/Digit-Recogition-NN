// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>

typedef Matrix (*activation_func)(const Matrix&);

namespace activation
{
    Matrix relu (const Matrix &x);
    Matrix softmax (const Matrix &x);
}

#endif //ACTIVATION_H