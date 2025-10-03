/**
@file  pyutils.hpp
@brief Utility functions for Python to qflib bidirectional type translation.
*/

#ifndef PYORFLIB_PYUTILS_HPP
#define PYORFLIB_PYUTILS_HPP

#include <qflib/math/matrix.hpp>
#include <pyqflib/pycpp.hpp>   // NOTE: include the python headers last (before armadillo)

/** Converts a numpy 1-D array to an qf::Vector.
*/
static qf::Vector asVector(PyObject* pyVec)
{
  return qf::Vector(asDblVec(pyVec));
}

/** Converts an qf::Vector to a numpy vector
*/
static PyObject* asNumpy(qf::Vector const & vec)
{
  return asPyArray(arma::conv_to<std::vector<double>>::from(vec));
}

/** Converts a numpy 2-D array to an qf::Matrix.
*/
static qf::Matrix asMatrix(PyObject* pyMat)
{
  std::vector<std::vector<double>> dvecvec = asDblVecVec(pyMat);
  size_t nrows = dvecvec.size();
  size_t ncols = dvecvec.front().size();
  qf::Matrix mat(nrows, ncols);
  for (size_t i = 0; i < nrows; ++i)
    for (size_t j = 0; j < ncols; ++j)
      mat(i, j) = dvecvec[i][j];
  return mat;
}

/** Converts an qf::Matrix to numpy
*/
static PyObject* asNumpy(qf::Matrix const & mat)
{
  size_t nrows = mat.n_rows;
  size_t ncols = mat.n_cols;
  std::vector<std::vector<double>> dvecvec(nrows);
  for (size_t i = 0; i < nrows; ++i) {
    dvecvec[i].resize(ncols);
    for (size_t j = 0; j < ncols; ++j)
      dvecvec[i][j] = mat(i, j);
  }
  return asPyArray(dvecvec);
}

#endif // PYORFLIB_PYUTILS_HPP
