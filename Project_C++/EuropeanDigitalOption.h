#pragma once
#include "Option.h"
#include <stdexcept> 

class EuropeanDigitalOption : public Option {
private :
	double _strike;
public:
	enum digitalOptionType {call, put};

	EuropeanDigitalOption(double expiry, double strike);

	double getStrike() const;
	
	virtual digitalOptionType GetOptionType() const = 0;

    virtual double payoff(double S) const = 0;

    virtual ~EuropeanDigitalOption() = default; 
};
