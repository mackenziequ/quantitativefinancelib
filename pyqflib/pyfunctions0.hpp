/** 
@file  pyfunctions0.hpp
@brief Implementation of Python callable functions
*/
#include "pycpp.hpp"
#include <qflib/defines.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

static 
PyObject*  pyQfVersion(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  return asPyScalar(std::string(QF_VERSION_STRING));
PY_END;
}

static 
PyObject* pyQfSayHello(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyArg1(NULL);
  if (!PyArg_ParseTuple(pyArgs, "O", &pyArg1))
    return NULL;
  std::string name = asString(pyArg1);        // read in the name
  std::string greet = "Hello " + name + "!";  // compose the greeting  
  return asPyScalar(greet);
PY_END;
}



static 
PyObject* pyQfOuterProd(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyArg1(NULL);
  PyObject* pyArg2(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyArg1, &pyArg2))
    return NULL;

  std::vector<double> vec1 = asDblVec(pyArg1);
  std::vector<double> vec2 = asDblVec(pyArg2);
  size_t nrow = vec1.size();
  size_t ncol = vec2.size();
  
  // allocate and compute the answer
  std::vector<std::vector<double>> outprod(nrow);
  for (size_t i = 0; i < nrow; ++i) {
	  outprod[i].resize(ncol);
	  for (size_t j = 0; j < ncol; ++j) {
		  outprod[i][j] = vec1[i] * vec2[j];
	  };
  };
	
  return asPyArray(outprod);

PY_END;
}

static 
PyObject* pyQfPolyProd(PyObject* pyDummy, PyObject* pyArgs)
{
  PY_BEGIN; 
  PyObject* pyArg1(NULL);
  PyObject* pyArg2(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyArg1, &pyArg2))
    return NULL;

  std::vector<double> vec1 = asDblVec(pyArg1);
  std::vector<double> vec2 = asDblVec(pyArg2);

  if (vec1.empty() || vec2.empty()){
    throw std::invalid_argument("Input vectors may not be empty");
  }
  size_t size1 = vec1.size();
  size_t size2 = vec2.size();

  std::vector<double> polydeg(size1 + size2 - 1);
  for (size_t i = 0; i < size1; i++){
    for (size_t j = 0; j < size2; j ++){
      polydeg[i+j] += vec1[i]*vec2[j];
    }
  }

  while (!polydeg.empty() && polydeg.back() == 0){
    polydeg.pop_back();
  }

  if (polydeg.empty()){
    polydeg.push_back(0);
  }
  
  // std::cout << "polydeg size: " << polydeg.size() << std::endl;

  return asPyList(polydeg);
PY_END;
}

