/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <qflib/pricers/simplepricers.hpp>
#include <qflib/math/stats/normaldistribution.hpp>

#include <cmath>

BEGIN_NAMESPACE(qf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield)
{
  QF_ASSERT(spot >= 0.0, "spot must be non-negative");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");

  return spot * exp((intRate - divYield) * timeToExp);
}

double quantoFwdPrice(double spot, double timeToExp, double intRate, double divYield, double assetVol, double fxVol, double corr){
  QF_ASSERT(spot >= 0.0, "spot must be non-negative");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(assetVol >= 0.0, "asset volstility must be non-negative");
  QF_ASSERT(fxVol >= 0.0, "fx volatility must be non-negative");
  double price = fwdPrice(spot, timeToExp, intRate, divYield);
  return exp(corr*assetVol*fxVol*timeToExp) * price;
}

END_NAMESPACE(qf)
