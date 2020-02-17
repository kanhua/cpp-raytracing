//
// Created by Kan-Hua Lee on 2020/02/17.
//

#include "gtest/gtest.h"

#include <boost/math/tools/roots.hpp>
//using boost::math::policies::policy;
//using boost::math::tools::newton_raphson_iterate;
//using boost::math::tools::halley_iterate; //
//using boost::math::tools::eps_tolerance; // Binary functor for specified number of bits.
//using boost::math::tools::bracket_and_solve_root;
//using boost::math::tools::toms748_solve;

#include <boost/math/special_functions/next.hpp> // For float_distance.
#include <tuple> // for std::tuple and std::make_tuple.
#include <boost/math/special_functions/cbrt.hpp> // For boost::math::cbrt.


template <class T>
struct cbrt_functor_deriv
{ // Functor also returning 1st derivative.
  cbrt_functor_deriv(T const& to_find_root_of) : a(to_find_root_of)
  { // Constructor stores value a to find root of,
    // for example: calling cbrt_functor_deriv<T>(a) to use to get cube root of a.
  }
  std::pair<T, T> operator()(T const& x)
  {
    // Return both f(x) and f'(x).
    T fx = x*x*x - a;                // Difference (estimate x^3 - value).
    T dx =  3 * x*x;                 // 1st derivative = 3x^2.
    return std::make_pair(fx, dx);   // 'return' both fx and dx.
  }
 private:
  T a;                               // Store value to be 'cube_rooted'.
};

template <class T>
T cbrt_deriv(T x)
{
  // return cube root of x using 1st derivative and Newton_Raphson.
  using namespace boost::math::tools;
  int exponent;
  frexp(x, &exponent);                                // Get exponent of z (ignore mantissa).
  T guess = ldexp(1., exponent/3);                    // Rough guess is to divide the exponent by three.
  T min = ldexp(0.5, exponent/3);                     // Minimum possible value is half our guess.
  T max = ldexp(2., exponent/3);                      // Maximum possible value is twice our guess.
  const int digits = std::numeric_limits<T>::digits;  // Maximum possible binary digits accuracy for type T.
  int get_digits = static_cast<int>(digits * 0.6);    // Accuracy doubles with each step, so stop when we have
  // just over half the digits correct.
  const boost::uintmax_t maxit = 20;
  boost::uintmax_t it = maxit;
  T result = newton_raphson_iterate(cbrt_functor_deriv<T>(x), guess, min, max, get_digits, it);
  return result;
}



TEST(newton,case1)
{
EXPECT_EQ(1.0, 1.0);
double result=cbrt_deriv(1.0);
std::cout<<result<<std::endl;
}