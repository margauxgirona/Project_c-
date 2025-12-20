#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike): AmericanOption(expiry, strike){}

double AmericanCallOption::payoff(double S) const {
	return std::max(S - getStrike(), 0.0);
}