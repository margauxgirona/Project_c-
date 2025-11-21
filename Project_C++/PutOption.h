#pragma once
#ifndef PUTOPTION_H
#define PUTOPTION_H
#include "EuropeanVanillaOption.h"
#include <algorithm>


class PutOption : public EuropeanVanillaOption {
public :
	PutOption(double expiry, double strike);

	double payoff(double S) const override;

	optionType GetOptionType() const override;

};
#endif // !PUTOPTION_H

