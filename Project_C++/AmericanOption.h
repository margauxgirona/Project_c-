#pragma once
#include "Option.h"


class AmericanOption : public Option {
private:
	double _strike;

public:
	AmericanOption(double expiry, double strike);

	bool isAmericanOption() const override;

	double getStrike() const;

	virtual double payoff(double S) const = 0;
};


