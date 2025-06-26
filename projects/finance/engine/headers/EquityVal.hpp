#define EQUITYVAL
#ifndef EQUITYVAL

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

class EquityValuator{
    double calculateDCF(double FCF, double growthrate, double discountrate, double terminalgrowthrate, int years);
    double calculatePEValuation(double EPS, double expectedPERatio);
    double CalculateGordonGrowthModel(double currentDividend, double growthRate, double discountRate);
}

#endif