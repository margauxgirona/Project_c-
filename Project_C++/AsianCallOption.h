#pragma once
#include "AsianOption.h"
#include <algorithm>

class AsianCallOption : public AsianOption {
private:
    double _strike;
public:
    AsianCallOption(const std::vector<double>& timeSteps, double strike);

    double payoff(double S_mean) const override;
};
