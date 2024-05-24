#include "Python.h"
#include "numpy/arrayobject.h"
#include "_aux.h"

npy_intp c_get_itemsize(PyArrayObject *arr) {
  return PyArray_ITEMSIZE(arr);
}
