/*  This program contains the following:
1. Portfolio Input and Structure
2. Daily returns (Simple returns and Log Return)
3. Value at Risk (VaR): Historical Simulation
4. Sharpe Ratio
5. Maximum drawdown
*/

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

struct Asset {
  std::string name;
  std::vector<double> returns;
  double weight;
};

class Portfolio {
private:
  std::vector<Asset> Assets;

public:
  std::vector<double> PortfolioReturns() {
    std::vector<double> portfolioReturns;
    size_t numDays = Assets[0].returns.size();
    portfolioReturns.resize(numDays);
    double totalReturns = 0.0;
    for (int i = 0; i < Assets.size(); i++) {
      for (int j = 0; j < Assets[i].returns.size(); j++) {
        portfolioReturns[j] += (Assets[i].returns[j] * Assets[i].weight);
      }
    };
    return portfolioReturns;
  };

  auto const LogReturns(int DaysAgo) {
    // computed by day
    double returns = 0.0;
    int Day = Assets[0].returns.size() - DaysAgo;
    for (int i = 0; i < Assets.size(); i++) {
      returns = returns + (Assets[i].returns[Day] * Assets[i].weight);
    };
    return std::log(returns);
  }

  double TotalPortfolioReturns() {
    double totalReturns = 0.0;
    for (int i = 0; i < Assets.size(); i++) {
      for (int j = 0; j < Assets[i].returns.size(); j++) {
        totalReturns += (Assets[i].returns[j] * Assets[i].weight);
      }
    }
    return totalReturns;
  };

  double StandardDeviationReturns(const std::vector<double> portfolio) {
    if (portfolio.empty()) {
      return 0.0;
    }

    double mean = std::accumulate(portfolio.begin(), portfolio.end(), 0) /
                  portfolio.size();
    double variance = 0.0;

    for (double r : portfolio) {
      variance += (r - mean) * (r - mean);
    }
    variance /= portfolio.size();

    return std::sqrt(variance);
  }

  auto const SharpeRatio(const std::vector<double> portfolio) {
    double SARiskFreeRate = 9.96;
    double ReturnOfPort = TotalPortfolioReturns();
    double StandardDeviation = StandardDeviationReturns(portfolio);
    return (ReturnOfPort - SARiskFreeRate) / StandardDeviation;
  };

  auto const VaR(double a) {
    std::vector<double> PortDailyReturn = PortfolioReturns();
    std::sort(PortDailyReturn.begin(), PortDailyReturn.end());

    size_t index = static_cast<size_t>((1.0 - a) * PortDailyReturn.size());
    return -PortDailyReturn[index];
  };
  auto const MaxDrawdown(int t) {
    std::vector<double> returns = PortfolioReturns();
    std::vector<double> cumulative(t);
    cumulative[0] = 1.0;

    for (int i = 1; i < t; i++) {
      cumulative[i] = cumulative[i - 1] * (1 + returns[i]);
    }
    double maxSoFar = cumulative[0];
    double maxDrawdown = 0.0;

    for (int i = 1; i < t; i++) {
      if (cumulative[i] > maxSoFar)
        maxSoFar = cumulative[i];
      double drawdown = (maxSoFar - cumulative[i]) / maxSoFar;
      if (drawdown > maxDrawdown)
        maxDrawdown = drawdown;
    }
    return maxDrawdown;
  };
  auto const LoadAsset() { return Assets; };
  auto const AddAsset(Asset asset) { Assets.push_back(asset); };
};

int main() {
  Portfolio pf;
  int numAssets, numDays;

  std::cout << "Enter number of assets: ";
  std::cin >> numAssets;

  std::cout << "Enter number of return days: ";
  std::cin >> numDays;

  for (int i = 0; i < numAssets; ++i) {
    Asset asset;
    std::cout << "\nAsset " << i + 1 << " name: ";
    std::cin >> asset.name;

    std::cout << "Weight (0 to 1): ";
    std::cin >> asset.weight;

    std::cout << "Enter " << numDays << " daily returns:\n";
    for (int j = 0; j < numDays; ++j) {
      double r;
      std::cin >> r;
      asset.returns.push_back(r);
    }

    pf.AddAsset(asset);
  }

  std::vector<double> portReturns = pf.PortfolioReturns();

  std::cout << "\n--- Portfolio Metrics ---\n";
  std::cout << "Total Return: " << pf.TotalPortfolioReturns() << "\n";
  std::cout << "Sharpe Ratio: " << pf.SharpeRatio(portReturns) << "\n";
  std::cout << "Historical VaR (95%): " << pf.VaR(0.95) << "\n";
  std::cout << "Max Drawdown: " << pf.MaxDrawdown(portReturns.size()) << "\n";
  std::cout << "Log Return (most recent): " << pf.LogReturns(1) << "\n";

  return 0;
}
