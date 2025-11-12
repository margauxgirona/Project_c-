#pragma once
#include "AsianOption.h"
#include <vector>

class AsianPutOption : public AsianOption {
private:
    double _strike;

public:
    AsianPutOption(double expiry, double strike, const std::vector<double>& timeSteps);

    double payoff(double S) const override;
};

