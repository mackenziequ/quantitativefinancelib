/**
@file  univariatedistribution.hpp
@brief Base class for all univariate distributions
*/

#ifndef QF_UNIVARIATEDISTRIBUTION_HPP
#define QF_UNIVARIATEDISTRIBUTION_HPP

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)

class UnivariateDistribution
{
public:
  /** Initializing ctor */
  UnivariateDistribution() {}
  /*abstract class*/
  /** Probability density function */
  virtual double pdf(double x) const = 0;

  /** Cumulative distribution function */
  virtual double cdf(double x) const = 0;

  /** Inverse cumulative distribution function */
  virtual double invcdf(double p) const = 0;
};

END_NAMESPACE(qf)

#endif  // QF_UNIVARIATEDISTRIBUTION_HPP
