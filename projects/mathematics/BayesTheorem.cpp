#include <iostream>
#include <cmath>

double bayes_theorem(double prior_A, double likelihood_B_given_A, double evidence_B){
    if (evidence_B == 0){
        throw "Evidence B cannot be zero";
    }

    double posterior_A_given_B = (likelihood_B_given_A * prior_A) / evidence_B;
    return posterior_A_given_B;
}

int main(){
    double prior, likelihood, evidence;
    std::cout << "What is the P(A): ";
    std::cin >> prior;
    std::cout << "What is the P(B|A): ";
    std::cin >> likelihood;
    std::cout << "What is the P(B): ";
    std::cin >> evidence;

    double result = bayes_theorem(prior, likelihood, evidence);
    std::cout << "P(A|B): " << result << std::endl;
    return 0;
}