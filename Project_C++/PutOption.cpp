#include "PutOption.h"


PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

double PutOption::payoff(double S) const {
	return std::max(getStrike() - S, 0.0);
}

EuropeanVanillaOption::optionType PutOption::GetOptionType() const {
	return optionType::put;
}