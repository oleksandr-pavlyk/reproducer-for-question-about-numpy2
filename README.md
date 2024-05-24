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


# Observed behavior

```python
import numpy as np, itemsize as c_ext

dt = np.dtype("float64")
x = np.ones(8, dtype=dt)

c_ext.get_itemsize(x), x.itemsize
# outputs (0, 8), 8
```

The question is what am I doing wrong?