#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianPutOption : public AsianOption {
private:
    double _strike;
public:
    AsianPutOption(double expiry, double strike, const std::vector<double>& timeSteps)
        : AsianOption(expiry, timeSteps), _strike(strike) {}

    double payoff(double S) const override {
        return std::max(_strike - S, 0.0);
    }
};
