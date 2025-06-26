#include <iostream>
#include "../headers/EquityVal.hpp"
#include "../headers/OptionsVal.hpp"

int main() {
    EquityValuator equity;
    OptionsVal options;

    std::cout << "==== Valuation Engine ====\n";
    std::cout << "Choose valuation type:\n";
    std::cout << "1. Equity Valuation\n";
    std::cout << "2. Option Valuation (Black-Scholes)\n";
    std::cout << "3. Option Valuation (Monte Carlo)\n";
    std::cout << "Enter choice (1/2/3): ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        double FCF, growthRate, discountRate, terminalGrowthRate, EPS, expectedPERatio, currentDividend;
        int years;

        std::cout << "\n--- Equity Valuation ---\n";
        std::cout << "Free Cash Flow (FCF): "; std::cin >> FCF;
        std::cout << "Growth rate (decimal): "; std::cin >> growthRate;
        std::cout << "Discount rate (decimal): "; std::cin >> discountRate;
        std::cout << "Terminal growth rate (decimal): "; std::cin >> terminalGrowthRate;
        std::cout << "Projection years: "; std::cin >> years;
        std::cout << "EPS: "; std::cin >> EPS;
        std::cout << "Expected P/E Ratio: "; std::cin >> expectedPERatio;
        std::cout << "Current dividend: "; std::cin >> currentDividend;

        double dcfVal = equity.calculateDCF(FCF, growthRate, discountRate, terminalGrowthRate, years);
        double peVal = equity.calculatePEValuation(EPS, expectedPERatio);
        double ggmVal = (currentDividend > 0) ? equity.CalculateGordonGrowthModel(currentDividend, growthRate, discountRate) : 0;

        std::cout << "\n--- Equity Results ---\n";
        std::cout << "DCF Valuation: R " << dcfVal << "\n";
        std::cout << "P/E Valuation: R " << peVal << "\n";
        if (currentDividend > 0)
            std::cout << "Gordon Growth Valuation: R " << ggmVal << "\n";
        else
            std::cout << "Gordon Growth Model: Not applicable (no dividend)\n";

    } else if (choice == 2) {
        double S, K, r, v, T;

        std::cout << "\n--- Option Valuation (Black-Scholes) ---\n";
        std::cout << "Current Price (S): "; std::cin >> S;
        std::cout << "Strike Price (K): "; std::cin >> K;
        std::cout << "Risk-free Rate (r): "; std::cin >> r;
        std::cout << "Volatility (v): "; std::cin >> v;
        std::cout << "Time to Maturity (T, in years): "; std::cin >> T;

        double call = options.call_price(S, K, r, v, T);
        double put = options.put_price(S, K, r, v, T);

        std::cout << "\n--- Black-Scholes Results ---\n";
        std::cout << "Call Price: " << call << "\n";
        std::cout << "Put Price:  " << put << "\n";

    } else if (choice == 3) {
        double S0, K, T, r, sigma;
        int numSim;

        std::cout << "\n--- Option Valuation (Monte Carlo) ---\n";
        std::cout << "Initial Price (S0): "; std::cin >> S0;
        std::cout << "Strike Price (K): "; std::cin >> K;
        std::cout << "Time to Maturity (T): "; std::cin >> T;
        std::cout << "Risk-free Rate (r): "; std::cin >> r;
        std::cout << "Volatility (sigma): "; std::cin >> sigma;
        std::cout << "Number of Simulations: "; std::cin >> numSim;

        double mcVal = options.MonteCarloOptionPrice(S0, K, T, r, sigma, numSim);
        std::cout << "\n--- Monte Carlo Result ---\n";
        std::cout << "Estimated Call Price: " << mcVal << "\n";

    } else {
        std::cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}
