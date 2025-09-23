/**
@file  pycpp.hpp
@brief Utility functions for Python to C++ bidirectional type conversion, including numpy types.
       These are generic utilities, depending only on std and Python headers.
*/

#ifndef PYCPP_HPP
#define PYCPP_HPP

#include <vector>
#include <string>
#include <stdexcept>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include <numpy/numpyconfig.h>
#include <numpy/arrayobject.h>

#define CASSERT(condition, errmsg) \
if (!(condition)) { \
    if (std::string(errmsg).empty()) \
    throw std::runtime_error("pyqflib error: " #condition); \
    else \
    throw std::runtime_error(errmsg); \
}

#define PY_BEGIN try {

#define PY_END } \
    catch(std::exception& ex) { \
        PyErr_Clear(); \
        PyErr_SetString(PyExc_RuntimeError, ex.what()); \
            return nullptr; \
    }

static bool isNone(PyObject* p)
{
  return p == Py_None;
}


static bool asBool(PyObject* p)
{
  CASSERT(PyLong_Check(p), "asBool: arg not convertible to bool");
  long ret = PyLong_AsLong(p);
  return ret == 0 ? false : true;
}

static PyObject* asPyScalar(bool b)
{
  if (b)
    Py_RETURN_TRUE;
  else
    Py_RETURN_FALSE;
}

static bool isInteger(PyObject* p)
{
  int ret = PyLong_Check(p);
  return ret == 0 ? false : true;
}

static int asInt(PyObject* p)
{
    int ret = (int) PyLong_AsLong(p);
    CASSERT(!PyErr_Occurred(), "asInt: arg not convertible to int");
    return ret;
}

static PyObject* asPyScalar(int d) 
{
    return Py_BuildValue("i", d);
}

static long asLong(PyObject* p)
{
    long ret =  PyLong_AsLong(p);
    CASSERT(!PyErr_Occurred(), "asLong: arg not convertible to long");
    return ret;
}

static PyObject* asPyScalar(long d) 
{
    return Py_BuildValue("l", d);
}

static bool isDouble(PyObject* p)
{
  int ret = PyFloat_Check(p);
  return ret == 0 ? false : true;
}

static bool isReal(PyObject* p)
{
  return isInteger(p) || isDouble(p);
}

static double asDouble(PyObject* p)
{
    double ret =  PyFloat_AsDouble(p);
    CASSERT(!PyErr_Occurred(), "asDouble: arg not convertible to double");
    return ret;
}

static PyObject* asPyScalar(double d) 
{
    return Py_BuildValue("d", d);
}

static bool isString(PyObject* p)
{
  int ret = PyUnicode_Check(p);
  return ret == 0 ? false : true;
}

static std::string asString(PyObject* p)
{
    PyObject* pyRep = PyObject_Str(p);
    PyObject* pyStr = PyUnicode_AsEncodedString(pyRep, "ascii", "asString: error encoding string");
    std::string str = PyBytes_AS_STRING(pyStr);
    Py_XDECREF(pyRep);
    Py_XDECREF(pyStr);
    CASSERT(!PyErr_Occurred(), "asString: arg not convertible to std::string");
    return str;
}

static PyObject* asPyScalar(std::string const& s)
{
    return Py_BuildValue("s", s.data());
}

static PyObject* asPyScalar(const char* s)
{
  return Py_BuildValue("s", s);
}

static std::vector<int> asIntVec(PyObject* pobj)
{
    PyObject* arr = PyArray_FROM_OTF(pobj, NPY_LONG, NPY_IN_ARRAY);
    if (arr == nullptr)
        return std::vector<int>();
    try {
        int ndim = PyArray_NDIM((PyArrayObject*) arr);    // number of dimensions
        CASSERT(ndim ==1, "asIntVec: input object is not one dimensional");
        npy_intp* dims = PyArray_SHAPE((PyArrayObject*) arr);  // array of length ndim, showing the length of each dim
        int* dptr = (int*)  PyArray_DATA((PyArrayObject*) arr);  // pointer to data
        std::vector<int> ivec(dptr, dptr + dims[0]);
        Py_DECREF(arr);
        return ivec;
    }
    catch (std::exception& ex) {
        Py_DECREF(arr);
        throw(ex);
    }
}

static std::vector<long> asLongVec(PyObject* pobj)
{
    PyObject* arr = PyArray_FROM_OTF(pobj, NPY_LONG, NPY_IN_ARRAY);
    if (arr == nullptr)
        return std::vector<long>();
    try {
        int ndim = PyArray_NDIM((PyArrayObject*) arr);    // number of dimensions
        CASSERT(ndim ==1, "asLongVec: input object is not one dimensional");
        npy_intp* dims = PyArray_SHAPE((PyArrayObject*) arr);  // array of length ndim, showing the length of each dim
        long* dptr = (long*)  PyArray_DATA((PyArrayObject*) arr);  // pointer to data
        std::vector<long> lvec(dptr, dptr + dims[0]);
        Py_DECREF(arr);
        return lvec;
    }
    catch (std::exception& ex) {
        Py_DECREF(arr);
        throw(ex);
    }
}

static std::vector<double> asDblVec(PyObject* pobj)
{
    PyObject* arr = PyArray_FROM_OTF(pobj, NPY_DOUBLE, NPY_IN_ARRAY);
    if (arr == nullptr)
        return std::vector<double>();
    try {
        int ndim = PyArray_NDIM((PyArrayObject*) arr);    // number of dimensions
        CASSERT(ndim ==1, "asDblVec: input object is not one dimensional");
        npy_intp* dims = PyArray_SHAPE((PyArrayObject*) arr);  // array of length ndim, showing the length of each dim
        double* dptr = (double*)  PyArray_DATA((PyArrayObject*) arr);  // pointer to data
        std::vector<double> dvec(dptr, dptr + dims[0]);
        Py_DECREF(arr);
        return dvec;
    }
    catch (std::exception& ex) {
        Py_DECREF(arr);
        throw(ex);
    }
}

static PyObject* asPyArray(std::vector<int> const& ivec)
{
    npy_intp dims[1];
    dims[0] = ivec.size();

    PyArrayObject* pvec = (PyArrayObject*) PyArray_SimpleNew(1, dims, NPY_INT32);
    memcpy(PyArray_DATA(pvec), ivec.data(), sizeof(int) * dims[0]);
    return (PyObject*) pvec;
}

static PyObject* asPyList(std::vector<int> const& ivec)
{
    size_t nels = ivec.size();
    PyObject* plist = PyList_New(nels);
    for (size_t i = 0; i < nels; ++i) {
        PyList_SET_ITEM(plist, i, asPyScalar(ivec[i]));
    }
    return plist;
}

static PyObject* asPyArray(std::vector<double> const& dvec)
{
    npy_intp dims[1];
    dims[0] = dvec.size();

    PyArrayObject* pvec = (PyArrayObject*) PyArray_SimpleNew(1, dims, NPY_FLOAT64);
    memcpy(PyArray_DATA(pvec), dvec.data(), sizeof(double) * dims[0]);
    return (PyObject*) pvec;
}

static PyObject* asPyList(std::vector<double> const& dvec)
{
    size_t nels = dvec.size();
    PyObject* plist = PyList_New(nels);
    for (size_t i = 0; i < nels; ++i) {
        PyList_SET_ITEM(plist, i, asPyScalar(dvec[i]));
    }
    return plist;
}

static std::vector<std::vector<double>> asDblVecVec(PyObject* pobj)
{
    PyObject* arr = PyArray_FROM_OTF(pobj, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);
    if (arr == nullptr)
        return std::vector<std::vector<double>> ();

    try {
        int ndim = PyArray_NDIM((PyArrayObject*) arr);   // number of dimensions
        CASSERT(ndim == 2, "asDblVecVec: input object is not two dimensional");
        npy_intp* dims = PyArray_DIMS((PyArrayObject*) arr);  // array of length ndim, showing the length of each dim
        size_t nrow = dims[0];
        size_t ncol = dims[1];
        std::vector<std::vector<double>> dvec(nrow);
        double* dptr = (double*) PyArray_DATA((PyArrayObject*) arr);
        for (size_t i = 0; i < nrow; ++i) {
            dvec[i].resize(ncol);
            for (size_t j = 0; j < ncol; ++j) {
                dvec[i][j] = *(dptr + i * ncol + j);
            }
        }
        Py_DECREF(arr);
        return dvec;
    }
    catch (std::exception& ex) {
        Py_DECREF(arr);
        throw(ex);
    }
}

static PyObject* asPyList(std::vector<std::vector<double>> const& dvecvec)
{
    size_t nrow = dvecvec.size();
    PyObject* plist = PyList_New(nrow);
    for (size_t i = 0; i < nrow; ++i) {
        PyList_SET_ITEM(plist, i, asPyList(dvecvec[i]));
    }
    return plist;
}

static PyObject* asPyArray(std::vector<std::vector<double>> const& dvecvec)
{
    PyObject* plist = asPyList(dvecvec);
    PyObject* parr = PyArray_FROM_OTF(plist, NPY_DOUBLE, NPY_IN_ARRAY);
    Py_DECREF(plist);
    return parr;
}

static std::vector<std::string> asStrVec(PyObject* pobj)
{
    // The NPY_ARRAY_FORCECAST flag handles casting from UTF-* and Unicode characters
    PyObject* arr = PyArray_FROM_OTF(pobj, NPY_STRING, NPY_IN_ARRAY | NPY_ARRAY_FORCECAST);

    try {
        int ndim = PyArray_NDIM((PyArrayObject*) arr);    // number of dimensions, only the first one will be processed
        CASSERT(ndim == 1, "asStrVec: input object is not one dimensional");
        npy_intp* dims = PyArray_SHAPE((PyArrayObject*) arr); // array of lenght ndim with nels in ech dim
        npy_intp* strides = PyArray_STRIDES((PyArrayObject*) arr);  // array of length ndim showing data length in each dim
        size_t nels = (size_t) dims[0];

        char* sptr = (char*) PyArray_DATA((PyArrayObject*) arr);  // pointer to data
        std::vector<std::string> svec(nels);
        for (int i = 0; i < nels; ++i) {
            svec[i] = std::string(sptr + i * strides[0], sptr + (i + 1) * strides[0]);
        }
        Py_DECREF(arr);
        return svec;
    }
    catch (std::exception& ex) {
        Py_DECREF(arr);
        throw(ex);
    }
}

static PyObject* asPyList(std::vector<std::string> const& svec)
{
    npy_intp nels = svec.size();
    PyObject* plist = PyList_New(nels);
    for (size_t i = 0; i < (size_t) nels; ++i) {
        PyList_SET_ITEM(plist, i, asPyScalar(svec[i]));
    }
    return plist;
} 

static PyObject* asPyArray(std::vector<std::string> const& svec)
{
  PyObject* plist = asPyList(svec);
  PyObject* parr = PyArray_FROM_OTF(plist, NPY_UNICODE, NPY_IN_ARRAY);
  Py_DECREF(plist);
  return parr;
}

static PyObject* getField(PyObject* pobj, char const* field)
{
  PyObject* pattr = nullptr;
    if (PyDict_Check(pobj))
      pattr = PyDict_GetItemString(pobj, field);
    else
      pattr = PyObject_GetAttrString(pobj, field);
    if (pattr == nullptr) {
        std::string errmsg = std::string("getField: no field ") + std::string(field);
        throw std::runtime_error(errmsg.c_str());
    }
    return pattr;
}

static int asInt(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    int d = asInt(pattr);
    Py_DECREF(pattr);
    return d;
}

static long asLong(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    long d = asLong(pattr);
    Py_DECREF(pattr);
    return d;
}

static double asDouble(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    double d = asDouble(pattr);
    Py_DECREF(pattr);
    return d;
}

static std::vector<int> asIntVec(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::vector<int> ivec = asIntVec(pattr);
    Py_DECREF(pattr);
    return ivec;
}

static std::vector<long> asLongVec(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::vector<long> lvec = asLongVec(pattr);
    Py_DECREF(pattr);
    return lvec;
}

static std::vector<double> asDblVec(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::vector<double> dvec = asDblVec(pattr);
    Py_DECREF(pattr);
    return dvec;
}

static std::vector<std::vector<double>> asDblVecVec(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::vector<std::vector<double>> dvecvec = asDblVecVec(pattr);
    Py_DECREF(pattr);
    return dvecvec;
}

static std::string asString(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::string s = asString(pattr);
    Py_DECREF(pattr);
    return s;
}

static std::vector<std::string> asStrVec(PyObject* pobj, std::string const& fieldName) 
{
    PyObject* pattr = getField(pobj, fieldName.c_str());
    std::vector<std::string> svec = asStrVec(pattr);
    Py_DECREF(pattr);
    return svec;
}

/** Calls the module.className(args) constructor and returns the new object
    The 'args' must be a valid tuple
*/
static PyObject* newPyObject(std::string const& moduleName, std::string const& className, PyObject* args)
{
    PyObject* mod = PyImport_Import(asPyScalar(moduleName));  // new reference
    PyObject* mdict = PyModule_GetDict(mod);  // borrowed reference
    PyObject* func = PyDict_GetItemString(mdict, className.c_str());  // borrowed reference
    PyObject* pynewobj = nullptr;
    if (PyCallable_Check(func))
        pynewobj = PyObject_CallObject(func, args);
    else
        PyErr_Print();
    // clean up
    Py_XDECREF(mod);
    return pynewobj;
}

#endif // PYCPP_HPP
