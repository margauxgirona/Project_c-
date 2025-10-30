#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiracy, double strike) : EuropeanDigitalOption(expiracy, strike) {}

double EuropeanDigitalCallOption::payoff(double S) const {
    if (S >= getStrike())
        return 1.0;
    return 0.0;
}

EuropeanDigitalOption::digitalOptionType
EuropeanDigitalCallOption::GetOptionType() const {
    return EuropeanDigitalOption::digitalOptionType::call;
}