#pragma once
#include "EuropeanDigitalOption.h"
#include <algorithm>

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiracy, double strike);

    double payoff(double S) const override;

    digitalOptionType GetOptionType() const override;
};