#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianCallOption : public AsianOption {
private:
    double _strike;
public:
    AsianCallOption(double expiry, double strike, const std::vector<double>& timeSteps);

    double payoff(double S) const override;
};
