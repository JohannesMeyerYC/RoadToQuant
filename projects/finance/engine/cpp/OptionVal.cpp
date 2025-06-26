#include "../headers/OptionsVal.hpp"
#include <cmath>
#include <random>
#include <algorithm>

double OptionsVal::norm_pdf(const double& x) {
    return (1.0 / std::sqrt(2 * M_PI)) * std::exp(-0.5 * x * x);
}

double OptionsVal::norm_cdf(const double& x) {
    double k = 1.0 / (1.0 + 0.2316419 * std::abs(x));
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 +
                    k * (-1.821255978 + 1.330274429 * k))));
    double cdf = 1.0 - norm_pdf(x) * k_sum;
    return x >= 0.0 ? cdf : 1.0 - cdf;
}

double OptionsVal::d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
    return (std::log(S / K) + (r + std::pow(-1, j - 1) * 0.5 * v * v) * T) / (v * std::sqrt(T));
}

double OptionsVal::call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * std::exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double OptionsVal::put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return -S * norm_cdf(-d_j(1, S, K, r, v, T)) + K * std::exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

double OptionsVal::MonteCarloOptionPrice(double S0, double K, double T, double r, double sigma, int numSimulations) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    double totalPayoff = 0.0;

    for (int i = 0; i < numSimulations; i++) {
        double Z = dist(gen);
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
        double payoff = std::max(ST - K, 0.0);  // European call payoff
        totalPayoff += payoff;
    }

    double averagePayoff = totalPayoff / numSimulations;
    return std::exp(-r * T) * averagePayoff;
}
