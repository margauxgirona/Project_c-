#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike){}

bool AmericanOption::isAmericanOption() {
	return true;
}

double AmericanOption:: getStrike() const {
	return _strike;
}