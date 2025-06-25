#include <iostream>
#include <math.h>

double calculateDCF(double FCF, double growthrate, double discountrate, double terminalgrowthrate, int years){
  double TotalValue = 0;
  for (int t = 1; t < years; t++){
       double projectedFCF = FCF * pow(1 + growthrate, t);
       double discountedFCF = projectedFCF / pow(1 + discountrate, t);
       TotalValue = TotalValue + discountedFCF;
       };

  double FinalFCF = FCF * pow(1 + growthrate, years);
  double terminalValue = (FinalFCF * (1 + terminalgrowthrate)) / (discountrate - terminalgrowthrate);
  double discountedTerminal = terminalValue / pow(1 + discountrate, years);

  return TotalValue + discountedTerminal;
}

double calculatePEValuation(double EPS, double expectedPERatio){
  double valuation = EPS * expectedPERatio;
  return valuation;
}

double CalculateGordonGrowthModel(double currentDividend, double growthRate, double discountRate){
  double NextDividend = currentDividend * (1 + growthRate);
  double intrinsicVal = NextDividend / (discountRate - growthRate);
  return intrinsicVal;
}

int main() {
    std::cout << "=== Equity Valuator ===\n";

    double FCF, growthRate, discountRate, terminalGrowthRate;
    int years;
    double EPS, expectedPERatio;
    double currentDividend;

    std::cout << "\nEnter Free Cash Flow or Earnings per Share (EPS): ";
    std::cout << "\n> Tip: Use recent annual FCF or EPS. You can find this on company financial reports or sites like Yahoo Finance.\n> ";
    std::cin >> FCF;

    std::cout << "\nEnter expected annual growth rate (in decimal, e.g., 0.10 for 10%): ";
    std::cout << "\n> Tip: Look at past 5Y revenue or earnings growth, or analyst projections.\n> ";
    std::cin >> growthRate;

    std::cout << "\nEnter your discount rate (in decimal, e.g., 0.12 for 12%): ";
    std::cout << "\n> Tip: Use your required rate of return, often 8–15%.\n> ";
    std::cin >> discountRate;

    std::cout << "\nEnter number of years to project (e.g., 5 or 10): ";
    std::cout << "\n> Tip: 5–10 years is standard in DCF.\n> ";
    std::cin >> years;

    std::cout << "\nEnter terminal growth rate (in decimal, e.g., 0.02 for 2%): ";
    std::cout << "\n> Tip: Use a modest number like 2–3% to reflect long-term stable growth.\n> ";
    std::cin >> terminalGrowthRate;

    std::cout << "\nEnter expected P/E ratio (e.g., 15 or 20): ";
    std::cout << "\n> Tip: Look at industry average or company's historical P/E.\n> ";
    std::cin >> expectedPERatio;

    std::cout << "\nEnter earnings per share (EPS): ";
    std::cout << "\n> Tip: Use trailing 12-month EPS or average of recent years.\n> ";
    std::cin >> EPS;

    std::cout << "\nEnter current dividend per share (if any): ";
    std::cout << "\n> Tip: Use annual dividend. If none, enter 0.\n> ";
    std::cin >> currentDividend;

    // Calculations
    double dcfVal = calculateDCF(FCF, growthRate, discountRate, terminalGrowthRate, years);
    double peVal = calculatePEValuation(EPS, expectedPERatio);
    double ggmVal = (currentDividend > 0) ? CalculateGordonGrowthModel(currentDividend, growthRate, discountRate) : 0;

    // Results
    std::cout << "\n--- Valuation Results ---\n";
    std::cout << "Discounted Cash Flow (DCF) Valuation: R " << dcfVal << "\n";
    std::cout << "P/E Multiple Valuation:               R " << peVal << "\n";
    if (currentDividend > 0)
        std::cout << "Gordon Growth Model Valuation:       R " << ggmVal << "\n";
    else
        std::cout << "Gordon Growth Model: Not applicable (no dividend)\n";

    return 0;
}
