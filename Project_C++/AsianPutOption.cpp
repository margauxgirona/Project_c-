#include "AsianPutOption.h"
#include <algorithm> 
#include <vector>    

AsianPutOption::AsianPutOption(double expiry, double strike, const std::vector<double>& timeSteps)
    : AsianOption(expiry, timeSteps), _strike(strike) {
}

double AsianPutOption::payoff(double S) const {
    return std::max(_strike - S, 0.0);
}
