#pragma once
#ifndef BLACKSCHOLESPRICER_H
#define BLACKSCHOLESPRICER_H

#include "EuropeanVanillaOption.h"
#include <cmath>
#include <iostream>

class BlackScholesPricer 
{
private:
	EuropeanVanillaOption* option;
	double asset_price;
	double interest_rate;
	double volatility;

	//Fonction auxiliaire
	double N(double x) const {
		return 0.5 * erfc(-x * sqrt(2.0));
	}
public:
	BlackScholesPricer(EuropeanVanillaOption* o, double a, double i, double v) : option(o), asset_price(a), interest_rate(i), volatility(v) {}
	
	//prix
	double operator()() const;
	//delta
	double delta() const;
};

#endif // !BLACKSCHOLESPRICER_H

