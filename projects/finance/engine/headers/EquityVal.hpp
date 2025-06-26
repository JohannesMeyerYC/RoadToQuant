#ifndef EQUITYVAL
#define EQUITYVAL

class EquityValuator{
    public:
        double calculateDCF(double FCF, double growthrate, double discountrate, double terminalgrowthrate, int years);
        double calculatePEValuation(double EPS, double expectedPERatio);
        double CalculateGordonGrowthModel(double currentDividend, double growthRate, double discountRate);
};

#endif