#include "AsianPutOption.h"
#include <algorithm> 
#include <vector>    

AsianPutOption::AsianPutOption(const std::vector<double>& timeSteps, double strike) : AsianOption(timeSteps), _strike(strike) {}

double AsianPutOption::payoff(double S_mean) const {
    return std::max(_strike - S_mean, 0.0);
}
