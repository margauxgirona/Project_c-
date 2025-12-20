#include "Option.h"

Option::Option(double expiry) : _expiry(expiry) {}

double Option::getExpiry() const {
	return _expiry;
}

double Option::payoffPath(const std::vector<double>& spots) const {
	if (spots.empty()) {
		return 0.0;
	}
	return payoff(spots.back());
}

bool Option::isAsianOption() const { 
	return false; 
}

bool Option:: isAmericanOption() const {
	return false;
}

Option::~Option() = default;