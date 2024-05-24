#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "numpy/arrayobject.h"
#include "_aux.h"

static
PyObject *
py_get_itemsize(
   PyObject * self,
   PyObject * args)
{
   PyObject *arg0 = NULL;
   if(!PyArg_ParseTuple(args, "O", &arg0))
        return NULL;

   if (!PyObject_TypeCheck(arg0, &PyArray_Type))
       return NULL;

   PyArrayObject *arr = (PyArrayObject *)arg0;

   npy_intp sz = c_get_itemsize(arr);
   npy_intp sz1 = PyArray_ITEMSIZE(arr);


   PyObject *res1 = PyLong_FromSsize_t(sz);
   PyObject *res2 = PyLong_FromSsize_t(sz1);

   PyObject *res_tup = PyTuple_Pack(2, res1, res2);

   return res_tup;
}


static char itemsize_docstring[] =
    "Accessor for PyArray's itemsize";

static PyMethodDef itemsize_methods[] = {
  {"get_itemsize", &py_get_itemsize, METH_VARARGS, itemsize_docstring},
  {NULL, NULL, 0, NULL}
};


static char docstring[] =
    "Module to test working of PyArray_ITEMSIZE";
    
static struct PyModuleDef itemsize_module =
{
    PyModuleDef_HEAD_INIT, "itemsize", docstring, -1, itemsize_methods
};

PyMODINIT_FUNC
PyInit_itemsize(void)
{
  import_array();
  return PyModule_Create(&itemsize_module);
}

