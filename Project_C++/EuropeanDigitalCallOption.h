#pragma once
#ifndef EUROPEANDIGITALCALLOPTION_H
#define EUROPEANDIGITALCALLOPTION_H

#include "EuropeanDigitalOption.h"
#include <algorithm>

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiracy, double strike);

    double payoff(double S) const override;

    digitalOptionType GetOptionType() const override;
};

#endif