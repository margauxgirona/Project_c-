#include "AsianCallOption.h"
#include <algorithm> 
#include <vector>

AsianCallOption::AsianCallOption(const std::vector<double>& timeSteps, double strike)
    : AsianOption(timeSteps), _strike(strike) {
}

double AsianCallOption::payoff(double S) const {
    return std::max(S - _strike, 0.0);
}