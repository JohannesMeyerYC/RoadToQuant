#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

double MonteCarloOptionPrice(double S0, double K, double T, double r, double sigma, int numSimulations) {
    std::random_device rd;
    std::mt19937 gen(rd());  
    std::normal_distribution<> dist(0.0, 1.0); 

    double totalPayoff = 0.0;

    for (int i = 0; i < numSimulations; i++) {
        double Z = dist(gen); 
        double ST = S0 * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z); 
        double payoff = std::max(ST - K, 0.0);
        totalPayoff += payoff;
    }

    double averagePayoff = totalPayoff / numSimulations;
    double discountedPayoff = exp(-r * T) * averagePayoff;

    return discountedPayoff;
}

double norm_pdf(const double& x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

double norm_cdf(const double& x) {
    
  double k = 1.0/(1.0 + 0.2316419*x);
    
  double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    
  if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } 
  else {
        return 1.0 - norm_cdf(-x);
    }
}

double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {

    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
  
    return S * norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));

}

double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {

    return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));

}

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
    std::cout << "Select Model to run:\n";
    std::cout << "1. Monte Carlo Option Pricing\n";
    std::cout << "2. Black-Scholes Option Pricing\n";
    std::cout << "3. Equity Valuation Engine\n";
    std::cout << "Enter choice (1-3): ";

    int choice;
    std::cin >> choice;

    switch(choice) {
        case 1: {
            double S0, K, T, r, sigma;
            int simulations;
            std::cout << "Monte Carlo Option Pricing\n";
            std::cout << "Enter current asset price (S0): ";
            std::cin >> S0;
            std::cout << "Enter strike price (K): ";
            std::cin >> K;
            std::cout << "Enter time to maturity in years (T): ";
            std::cin >> T;
            std::cout << "Enter risk-free rate (r) [e.g., 0.05]: ";
            std::cin >> r;
            std::cout << "Enter volatility (sigma) [e.g., 0.2]: ";
            std::cin >> sigma;
            std::cout << "Enter number of simulations (e.g., 100000): ";
            std::cin >> simulations;

            double price = MonteCarloOptionPrice(S0, K, T, r, sigma, simulations);
            std::cout << "Monte Carlo Call Option Price: " << price << "\n";
            break;
        }
        case 2: {
            double S, K, r, v, T;
            std::cout << "Black-Scholes Option Pricing\n";
            std::cout << "Enter current asset price (S): ";
            std::cin >> S;
            std::cout << "Enter strike price (K): ";
            std::cin >> K;
            std::cout << "Enter risk-free rate (r) [e.g., 0.05]: ";
            std::cin >> r;
            std::cout << "Enter volatility (v) [e.g., 0.2]: ";
            std::cin >> v;
            std::cout << "Enter time to expiry in years (T): ";
            std::cin >> T;

            double call = call_price(S, K, r, v, T);
            double put = put_price(S, K, r, v, T);
            std::cout << "Call Price: " << call << "\n";
            std::cout << "Put Price: " << put << "\n";
            break;
        }
        case 3: {
            std::cout << "Equity Valuation Engine\n";

            double FCF, growthRate, discountRate, terminalGrowthRate;
            int years;
            double EPS, expectedPERatio;
            double currentDividend;

            std::cout << "Enter Free Cash Flow: ";
            std::cin >> FCF;
            std::cout << "Enter expected annual growth rate (decimal): ";
            std::cin >> growthRate;
            std::cout << "Enter discount rate (decimal): ";
            std::cin >> discountRate;
            std::cout << "Enter projection years: ";
            std::cin >> years;
            std::cout << "Enter terminal growth rate (decimal): ";
            std::cin >> terminalGrowthRate;
            std::cout << "Enter expected P/E ratio: ";
            std::cin >> expectedPERatio;
            std::cout << "Enter earnings per share (EPS): ";
            std::cin >> EPS;
            std::cout << "Enter current dividend per share: ";
            std::cin >> currentDividend;

            double dcfVal = calculateDCF(FCF, growthRate, discountRate, terminalGrowthRate, years);
            double peVal = calculatePEValuation(EPS, expectedPERatio);
            double ggmVal = (currentDividend > 0) ? CalculateGordonGrowthModel(currentDividend, growthRate, discountRate) : 0;

            std::cout << "DCF Valuation: " << dcfVal << "\n";
            std::cout << "P/E Valuation: " << peVal << "\n";
            if (currentDividend > 0)
                std::cout << "Gordon Growth Model Valuation: " << ggmVal << "\n";
            else
                std::cout << "Gordon Growth Model: Not applicable (no dividend)\n";

            break;
        }
        default:
            std::cout << "Invalid choice\n";
    }

    return 0;
}

