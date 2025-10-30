#pragma once
#ifndef EUROPEANDIGITALOPTION_H
#define EUROPEANDIGITALOPTION_H

#include "Option.h"
#include <stdexcept> // to throw execptions

class EuropeanDigitalOption : public Option {
private :
	double _strike;
public:
	enum digitalOptionType { call, put };

	EuropeanDigitalOption(double expiry, double strike);

	double getStrike() const;
	
	virtual digitalOptionType GetOptionType() const = 0;

    virtual double payoff(double S) const = 0;

    virtual ~EuropeanDigitalOption() = default;
};

#endif
