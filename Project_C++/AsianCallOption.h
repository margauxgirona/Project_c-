#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianCallOption : public AsianOption {
private:
    double _strike;
public:
    AsianCallOption(double expiry, double strike, const std::vector<double>& timeSteps)
        : AsianOption(expiry, timeSteps), _strike(strike) {}

    double payoff(double S) const override {
        return std::max(S - _strike, 0.0);
    }
};
