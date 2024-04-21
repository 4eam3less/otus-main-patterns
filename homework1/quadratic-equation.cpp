#include "quadratic-equation.hpp"
#include <limits>
#include <cmath>

 std::array<double, 2> solve(double a, double b, double c){
    const double epsilon = std::numeric_limits<double>::epsilon() * 100;
    if(std::fabs(a) < epsilon)
        throw std::invalid_argument("coefficient A mustn't be 0");
    if(std::isnan(a) || std::isnan(b) || std::isnan(c))
        throw std::invalid_argument("coefficients mustn't be NaN");
    if(std::isinf(a) || std::isinf(b) || std::isinf(c))
        throw std::invalid_argument("coefficients mustn't be infinity");

    if(const double D = (b*b) - (4 * a * c); D > epsilon){
        return {(-b+std::sqrt(D))/(2 * a), (-b-std::sqrt(D))/(2 * a)};
    } else if(D < -epsilon){
        return {};
    } else{
        return {(-b)/(2 * a), (-b)/(2 * a)};
    }
}
