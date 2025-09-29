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

/** Price of a European digital option in the Black-Scholes model*/
double digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d2 = log(fwd / strike) / sigT - 0.5 * sigT;
  NormalDistribution normal;

  double price = exp(-intRate * timeToExp) * normal.cdf(phi * d2);

  return price;
}

/** Price of a European option in the Black-Scholes model*/
double europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = exp(-intRate * timeToExp);
  double price = fwd * normal.cdf(phi * d1) - strike * normal.cdf(phi * d2);
  price *= phi * df;

  return price;
}

/** Price of a kockout forward*/

double knockoutFwd(double spot, double strike, double KOlevel, double timeToExp, double timeToKO, double IntRate, double DivYield, double Vol){
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(Vol >= 0.0, "volatility must be non-negative");
  QF_ASSERT(KOlevel >= 0.0, "KOlevel must be non-negative");
  QF_ASSERT(timeToKO <= timeToExp, "time to knockout must before expiration");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(IntRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(DivYield >= 0.0, "dividend yield must be non-negative");

  double callOptionPrice = europeanOptionBS(1, spot, KOlevel, timeToKO, IntRate, DivYield, Vol);
  double digitalOptionPrice = digitalOptionBS(1, spot, KOlevel, timeToKO, IntRate, DivYield, Vol);
  double timeDiff = timeToExp - timeToKO;
  double price = exp( -DivYield*timeDiff) * callOptionPrice + exp(-IntRate * timeDiff)*(KOlevel * exp((IntRate-DivYield) * timeDiff) - strike) * digitalOptionPrice;
  // double price = exp((IntRate -DivYield)*timeDiff) * callOptionPrice + (KOlevel - strike) * digitalOptionPrice;

  return price;
}
 
END_NAMESPACE(qf)
