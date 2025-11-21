#pragma once
#ifndef CALLOPTION_H
#define CALLOPTION_H

#include "EuropeanVanillaOption.h"
#include <algorithm>

class CallOption : public EuropeanVanillaOption {
public :
	CallOption(double expiry, double strike);

	double payoff(double S) const override;

	optionType GetOptionType() const override;
};
#endif // !CALLOPTION_H
