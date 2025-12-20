#pragma once
#include "EuropeanDigitalOption.h"
#include <algorithm>

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiracy, double strike);

    double payoff(double S) const override;

    digitalOptionType GetOptionType() const override;
};
