/**
@file  pymodule.cpp
@brief Python callable function registration and module definition
*/

#include "qflib/defines.hpp"
#include "pytestfunc.hpp"
#include "pyfunctions0.hpp"
#include "pyfunctions1.hpp"

static PyMethodDef PyQflibMethods[] = 
{
// test functions
  { "__echoBool__", echoBool, METH_VARARGS, "echoes a boolean" },
  { "__echoInt__", echoInt, METH_VARARGS, "echoes an integer" },
  { "__echoDouble__", echoDouble, METH_VARARGS, "echoes a double" },
  { "__echoString__", echoString, METH_VARARGS, "echoes a string" },
  { "__echoIntList__", echoIntList, METH_VARARGS, "echoes a list of integers" },
  { "__echoDblList__", echoDblList, METH_VARARGS, "echoes a list of doubles" },
  { "__echoStrList__", echoStrList, METH_VARARGS, "echoes a list of strings" },
  { "__echoIntArray__", echoIntArray, METH_VARARGS, "echoes an 1D array of integers" },
  { "__echoDblArray__", echoDblArray, METH_VARARGS, "echoes an 1D array of doubles" },
  { "__echoStrArray__", echoStrArray, METH_VARARGS, "echoes an 1D array of strings" },
  { "__echoDblArray2D__", echoDblArray2D, METH_VARARGS, "echoes a 2D array of doubles" },
  { "__echoDblVecField__", echoDblVecField, METH_VARARGS, "echoes an 1D array of doubnles in an object field" },
// functions 0
  { "version", pyQfVersion, METH_VARARGS, "qflib library version"},
  { "sayHello", pyQfSayHello, METH_VARARGS, "says hello"},
  { "outerProd", pyQfOuterProd, METH_VARARGS, "outproduct of two vectors"},
  { "erf", pyQfErf, METH_VARARGS, "the value of the error function." },
  { "invErf", pyQfInvErf, METH_VARARGS, "the value of the inverse error function." },
  { "normalCdf", pyQfNormalCdf, METH_VARARGS, "the value of the standard normal cumulative distribution." },
  { "normalInvCdf", pyQfNormalInvCdf, METH_VARARGS, "the value of the inverse standard normal cumulative distribution." },
  { "echoMatrix", pyQfEchoMatrix, METH_VARARGS, "echoes a matrix" },
// functions 1
  { "fwdPrice", pyQfFwdPrice, METH_VARARGS, "the forward price of an asset" },
  { "digiBS", pyQfDigiBS, METH_VARARGS, "price of a digital option in the Black-Scholes model." },
  { "euroBS", pyQfEuroBS, METH_VARARGS, "price of a European option in the Black-Scholes model." },
  {NULL, NULL, 0, NULL}
};

// Definition of module
static struct PyModuleDef modef =
{
  PyModuleDef_HEAD_INIT,
  "qflib",
  "Python interface to the qflib library",
  -1,
  PyQflibMethods
};

// Creation of module
PyMODINIT_FUNC
PyInit_pyqflib(void)
{
  PyObject* m = PyModule_Create(&modef);
  if (m == NULL)
    return NULL;
  import_array();
  return m;
}
