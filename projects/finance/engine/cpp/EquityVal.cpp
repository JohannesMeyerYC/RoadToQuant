#include "../headers/EquityVal.hpp"
#include <cmath>

double EquityValuator::calculateDCF(double FCF, double growthrate, double discountrate, double terminalgrowthrate, int years) {
    double TotalValue = 0;
    for (int t = 1; t < years; t++) {
        double projectedFCF = FCF * std::pow(1 + growthrate, t);
        double discountedFCF = projectedFCF / std::pow(1 + discountrate, t);
        TotalValue += discountedFCF;
    }

    double FinalFCF = FCF * std::pow(1 + growthrate, years);
    double terminalValue = (FinalFCF * (1 + terminalgrowthrate)) / (discountrate - terminalgrowthrate);
    double discountedTerminal = terminalValue / std::pow(1 + discountrate, years);

    return TotalValue + discountedTerminal;
}

double EquityValuator::calculatePEValuation(double EPS, double expectedPERatio) {
    return EPS * expectedPERatio;
}

double EquityValuator::CalculateGordonGrowthModel(double currentDividend, double growthRate, double discountRate) {
    double NextDividend = currentDividend * (1 + growthRate);
    return NextDividend / (discountRate - growthRate);
}
