#pragma once
#include "AsianOption.h"
#include <vector>

class AsianPutOption : public AsianOption {
private:
    double _strike;

public:
    AsianPutOption(const std::vector<double>& timeSteps, double strike);

    double payoff(double S_mean) const override;
};

