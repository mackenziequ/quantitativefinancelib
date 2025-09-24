/** 
@file  exception.hpp
@brief Definition of the qf::Exception class and the QF_ASSERT macro
*/

#ifndef QF_EXCEPTION_HPP
#define QF_EXCEPTION_HPP

#include <exception>
#include <sstream>
#include <string>

BEGIN_NAMESPACE(qf)

class Exception;

/** Streaming operator */
template <typename T> Exception & operator<<(Exception & ex, T const & msg);

/** The qflib Exception class; error messages can be streamed into it.
*/
class Exception : public std::exception 
{
public:
  /** initializing ctor */
  explicit Exception(std::string const & errmsg) : what_(errmsg) {}
  /** Returns the error message */
  virtual const char* what() const noexcept { return what_.c_str(); }
  /** dtor */
  virtual ~Exception() {}	

protected:
  mutable std::string what_;

  template <typename T>
  friend Exception & operator<<(Exception & ex, T const & msg);
};

// Implementation of the streaming operator
template <typename T>
Exception & operator<<(Exception & ex, T const & msg)
{
  std::ostringstream s;
  s << msg;
  ex.what_ += s.str();
  return ex;
}

/** @def    QF_ASSERT
 *  @brief  Convenience macro for throwing an Exception if 'condition' evaluates to false;
 *          'errmsg' is the error message string.
 */

#define QF_ASSERT(condition, errmsg) \
if (!(condition)) { \
  if ((std::string(errmsg)).empty()) \
  throw qf::Exception("error: " #condition); \
  else \
  throw qf::Exception(errmsg); \
}
/*
define on macro level
preprocessor 
 */
END_NAMESPACE(qf)

#endif // QF_EXCEPTION_HPP
