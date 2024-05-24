# Building extensions

## Development environment

Python 3.10.12, NumPy 2.0.0b1, GCC 13.2 from Ubuntu 24.04 

## C extension

```sh
gcc -O3 -shared -fPIC $(python3-config --includes) -I$(python -c "import numpy as np; print(np.get_include())") -DNPY_NO_DEPRECATED_API ext.c _aux.c -o itemsize.so
```

The extension defines a function `get_itemsize(arr)` that calls `PyArray_ITEMSIZE` underneath in two different ways.

First, it calls `c_get_itemsize` function declared in `_aux.h` and defined in `_aux.c` and then, it calls `PyArray_ITEMSIZE`
directly. Obtained values are returned as a `tuple[int, int]`.


# Observed behavior with NumPy 2.0

```python
import numpy as np, itemsize as c_ext

dt = np.dtype("float64")
x = np.ones(8, dtype=dt)

c_ext.get_itemsize(x), x.itemsize
# outputs (0, 8), 8
```

# Observed behavior with NumPy 1.26.4

Extension compiled agains NumPy 1.26.4 outputs `(8, 8), 8` as expected.

# Question

What am I doing wrong? How can I fix it?

# Answer based on help from NumPy mailing list

The issue was caused by improper importing of NumPy C-API.
The `_aux.c` requires pre-processing variable `NO_IMPORT_ARRAY` to be defined,
as well `PY_ARRAY_UNIQUE_SYMBOL` to influence linkage of PyArray_API symbol.

https://numpy.org/devdocs/reference/c-api/array.html#including-and-importing-the-c-api

Apply `fix.patch` and recompile to resolve the problem.