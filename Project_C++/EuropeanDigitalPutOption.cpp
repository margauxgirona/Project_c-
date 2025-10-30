#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiracy, double strike) : EuropeanDigitalOption(expiracy, strike) {}

double EuropeanDigitalPutOption::payoff(double S) const {
    if(getStrike() >= S)
        return 1.0;
    return 0.0;
}

EuropeanDigitalOption::digitalOptionType
EuropeanDigitalPutOption::GetOptionType() const {
    return EuropeanDigitalOption::digitalOptionType::put;
}