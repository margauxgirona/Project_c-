#pragma once
#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H

#include "Option.h"


class AmericanOption : public Option {
private:
	double _strike;

public:
	AmericanOption(double expiry, double strike);

	bool isAmericanOption() override;

	double getStrike() const;

	virtual double payoff(double S) const = 0;
};



#endif // !AMERICANOPTION_H

