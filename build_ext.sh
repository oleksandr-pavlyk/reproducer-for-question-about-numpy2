gcc -O3 -shared -fPIC $(python3-config --includes) -I$(python -c "import numpy as np; print(np.get_include())") -DNPY_NO_DEPRECATED_API ext.c _aux.c -o itemsize.so
