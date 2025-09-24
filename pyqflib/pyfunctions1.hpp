/** 
@file  pyfunctions1.hpp
@brief Implementation of Python callable functions
*/
#include "pycpp.hpp"
#include <qflib/defines.hpp>
#include <qflib/pricers/simplepricers.hpp>
#include <string>

static
PyObject*  pyQfFwdPrice(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pySpot(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OOOO", &pySpot, &pyTimeToExp, &pyIntRate, &pyDivYield))
    return NULL;

  double spot = asDouble(pySpot);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);

  double fwd = qf::fwdPrice(spot, timeToExp, intRate, divYield);

  return asPyScalar(fwd);
PY_END;
}

static
PyObject*  pyQfQuantoFwdPrice(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pySpot(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyAssetVol(NULL);
  PyObject* pyFxVol(NULL);
  PyObject* pyCorr(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pySpot, &pyTimeToExp, &pyIntRate, &pyDivYield, &pyAssetVol, &pyFxVol, &pyCorr))
    return NULL;

  double spot = asDouble(pySpot);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double assetVol = asDouble(pyAssetVol);
  double fxVol = asDouble(pyFxVol);
  double corr = asDouble(pyCorr);

  double fwd = qf::quantoFwdPrice(spot, timeToExp, intRate, divYield, assetVol, fxVol, corr);

  return asPyScalar(fwd);
PY_END; 

}