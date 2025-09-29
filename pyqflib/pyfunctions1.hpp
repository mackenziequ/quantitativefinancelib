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
PyObject*  pyQfDigiBS(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyPayoffType(NULL);
  PyObject* pySpot(NULL);
  PyObject* pyStrike(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyVolatility(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
    &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility))
    return NULL;

  int payoffType = asInt(pyPayoffType);
  double spot = asDouble(pySpot);
  double strike = asDouble(pyStrike);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double vol = asDouble(pyVolatility);

  double price = qf::digitalOptionBS(payoffType, spot, strike, timeToExp, intRate, divYield, vol);

  return asPyScalar(price);
PY_END;
}

static
PyObject*  pyQfEuroBS(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyPayoffType(NULL);
  PyObject* pySpot(NULL);
  PyObject* pyStrike(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyVolatility(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
    &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility))
    return NULL;


  int payoffType = asInt(pyPayoffType);
  double spot = asDouble(pySpot);
  double strike = asDouble(pyStrike);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double vol = asDouble(pyVolatility);

  double price = qf::europeanOptionBS(payoffType, spot, strike, timeToExp,
    intRate, divYield, vol);

  return asPyScalar(price);

PY_END;
}

static
PyObject*  pyQfKnockoutForward(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pySpot(NULL);
  PyObject* pyStrike(NULL);
  PyObject* pyKOlevel(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyTimeToKO(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyVol(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOOO", &pySpot, &pyStrike, &pyKOlevel,
    &pyTimeToExp, &pyTimeToKO, &pyIntRate, &pyDivYield, &pyVol))
    return NULL;

  double spot = asDouble(pySpot);
  double strike = asDouble(pyStrike);
  double KOlevel = asDouble(pyKOlevel);
  double timeToExp = asDouble(pyTimeToExp);
  double timeToKO = asDouble(pyTimeToKO);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double vol = asDouble(pyVol);
  
  double price = qf::knockoutFwd(spot, strike, KOlevel, timeToExp, timeToKO, intRate, divYield, vol);

  return asPyScalar(price);

PY_END;
}