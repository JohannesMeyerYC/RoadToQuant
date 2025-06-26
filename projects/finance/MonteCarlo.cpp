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

