#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <cmath>
#include <iostream>

class BlackScholesPricer 
{
private:
	const EuropeanVanillaOption* vanilla = nullptr;
    const EuropeanDigitalOption* digital = nullptr;
	double asset_price;
	double interest_rate;
	double volatility;

	// Auxiliary function
	double N(double x) const {
		return 0.5 * erfc(-x /sqrt(2.0));
	}

public:
	BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility);
	
	BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility);

	// price
	double operator()() const;
	// delta
	double delta() const;
};


