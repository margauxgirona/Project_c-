#pragma once
#ifndef PUTOPTION_H
#define PUTOPTION_H
#include "EuropeanVanillaOption.h"
#include <algorithm>


class PutOption : public EuropeanVanillaOption {
public :
	PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

	double payoff(double S) const override {
		return std::max(getStrike() - S, 0.0);
	}

	optionType GetOptionType() const override {
		return optionType::put;
	}
};
#endif // !PUTOPTION_H

