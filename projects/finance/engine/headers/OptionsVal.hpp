#define OPTIONSVAL
#ifndef OPTIONSVAL

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

class OptionsVal{

    double norm_pdf(const double& x);
    double norm_cdf(const double& x);
    double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T);
    double call_price(const double& S, const double& K, const double& r, const double& v, const double& T);
    double put_price(const double& S, const double& K, const double& r, const double& v, const double& T);

    double MonteCarloOptionPrice(double S0, double K, double T, double r, double sigma, int numSimulations);
}

#endif