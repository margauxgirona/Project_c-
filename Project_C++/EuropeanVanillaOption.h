#pragma once
#ifndef EUROPEANVANILLAOPTION_h
#define EUROPEANVANILLAOPTION_h

#include "Option.h"
#include <stdexcept> // pour lancer les exeptions
class EuropeanVanillaOption : public Option {
private :
	double _strike;
public:
	enum optionType { call, put };
	EuropeanVanillaOption(double expiry, double strike);

	double getStrike() const {
		return _strike;
	}
	virtual optionType GetOptionType() const = 0;

	virtual ~EuropeanVanillaOption() {}
};


#endif // !EUROPEANVANILLAOPTION.h

