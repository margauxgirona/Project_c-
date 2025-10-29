#pragma once
#ifndef CALLOPTION_H
#define CALLOPTION_H

#include "EuropeanVanillaOption.h"
#include <algorithm>

class CallOption : public EuropeanVanillaOption {
public :
	CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

	double payoff(double S) const override {
		return std::max(S - getStrike(), 0.0);
	}

	optionType GetOptionType() const override {
		return optionType::call;
	}	
};
#endif // !CALLOPTION_H
