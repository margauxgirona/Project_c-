#include "AsianPutOption.h"
#include <algorithm> 
#include <vector>    

AsianPutOption::AsianPutOption(const std::vector<double>& timeSteps, double strike)
    : AsianOption(timeSteps), _strike(strike) {
}

double AsianPutOption::payoff(double S) const {
    return std::max(_strike - S, 0.0);
}
