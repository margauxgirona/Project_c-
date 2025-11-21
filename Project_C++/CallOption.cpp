#include "CallOption.h"

CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

double CallOption::payoff(double S) const {
		return std::max(S - getStrike(), 0.0);
	}

EuropeanVanillaOption::optionType CallOption::GetOptionType() const {
		return optionType::call;   
	}