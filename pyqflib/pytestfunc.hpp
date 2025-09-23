/**
@file  pytestfunc.hpp
@brief Python callable functions for testing Python to C++ bidirectional type translation
*/

#include "pycpp.hpp"

static PyObject* echoBool(PyObject* dummy, PyObject* arg)
{
  PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  bool b = asBool(obj);
  return asPyScalar(b);
  PY_END;
}

static PyObject* echoInt(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  int i = asInt(obj);
  return asPyScalar(i);
PY_END;
}

static PyObject* echoDouble(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  double d = asDouble(obj);
  return asPyScalar(d);
PY_END;
}

static PyObject* echoString(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::string s = asString(obj);
  return asPyScalar(s);
PY_END;
}

static PyObject* echoIntList(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<int> ivec = asIntVec(obj);
  return asPyList(ivec);
PY_END;
}

static PyObject* echoDblList(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<double> dvec = asDblVec(obj);
  return asPyList(dvec);
PY_END;
}

static PyObject* echoStrList(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<std::string> svec = asStrVec(obj);
  return asPyList(svec);
PY_END;
}

static PyObject* echoIntArray(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<int> ivec = asIntVec(obj);
  return asPyArray(ivec);
PY_END;
}

static PyObject* echoDblArray(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<double> dvec = asDblVec(obj);
  return asPyArray(dvec);
PY_END;
}

static PyObject* echoStrArray(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<std::string> svec = asStrVec(obj);
  return asPyArray(svec);
PY_END;
}

static PyObject* echoDblArray2D(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  if (!PyArg_ParseTuple(arg, "O", &obj))
    return NULL;
  std::vector<std::vector<double>> dvecvec = asDblVecVec(obj);
  return asPyArray(dvecvec);
PY_END;
}

static PyObject* echoDblVecField(PyObject* dummy, PyObject* arg)
{
PY_BEGIN;
  PyObject* obj = NULL;
  char* cfld = NULL;
  if (!PyArg_ParseTuple(arg, "Os", &obj, &cfld))
    return NULL;

  std::string sfld = cfld;
  std::vector<double> dvec = asDblVec(obj, sfld);
  return asPyArray(dvec);
PY_END;
}