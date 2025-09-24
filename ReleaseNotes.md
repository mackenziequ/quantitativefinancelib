QFLIB Release Notes
====================

VERSION 0.2.0
-------------

### Additions

1. New file `qflib/exception.hpp`.  
    Definition of qf::Exception class and the QF_ASSERT macro.

2. New folder `qflib/math/stats` to contain statistics related source files.

3. New files `qflib/math/stats/errorfunction.hpp` and `errorfunction.cpp`.  
    Definition of class ErrorFunction.

4. New files `qflib/math/stats/univariatedistribution.hpp` and `normaldistribution.hpp`.  
    Definition of `UnivariateDistribution` and `NormalDistribution` classes.

5. New folder `qflib/math/pricers` to contain pricing related source files.

6. New files `qflib/mathorf/pricers/simplepricers.hpp` and `simplepricers.cpp`.  
    Definition of the function fwdPrice.

7. In file `pyqflib/pyfunctions0.cpp`.  
    Added definition of the following functions:  
    pyQrfErf, pyQrfInvErf, pyQrfNormalCdf, pyQrfNormalInvCdf

8. New file `pyqrflib/xlfunctions1.cpp`.  
    Added definition of functions pyQfFwdPrice.

9. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`   
    Added registration for functions:  
    qf.erf, qf.invErf, qf.normalCdf, qf.normalInvCdf, qf.fwdPrice

10. In files `examples/Python/qflib-examples.py` and `examples/Python/qflib-examples.ipynb`   
    Added example calls to qf.erf, qf.invErf, qf.normalCdf, qf.normalInvCdf, qf.fwdPrice

### Modifications

1. Removed unnecessary file `qflib/empty.cpp`


VERSION 0.1.0
-------------

### Additions

1. Top level CMakeLists.txt file with projet-wide settings

2. New folder `qflib` with CMakeLists.txt and start-up code for the core library.

3. New folder `pyqflib` with CMakeLists.txt and start-up code for the Python interface.

4. This release notes file.

5. `.gitignore` file for managing which files to keep under revision control.
