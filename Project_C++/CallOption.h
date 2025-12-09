#pragma once

#include "EuropeanVanillaOption.h"
#include <algorithm>

class CallOption : public EuropeanVanillaOption {
public :
	CallOption(double expiry, double strike);

	double payoff(double S) const override;

	optionType GetOptionType() const override;
};
