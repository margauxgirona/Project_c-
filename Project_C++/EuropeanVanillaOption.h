#pragma once
#ifndef EUROPEANVANILLAOPTION_h
#define EUROPEANVANILLAOPTION_h

#include "Option.h"
#include <stdexcept> // pour lancer les exeptions

class BlackScholesPricer;

class EuropeanVanillaOption : public Option {
	private:
		double _strike;

	public:
		enum optionType
		{
			call,
			put
		};
		EuropeanVanillaOption(double expiry, double strike);

		double getStrike() const;
		virtual optionType GetOptionType() const = 0;

		friend class BlackScholesPricer;

		virtual ~EuropeanVanillaOption() {}
};

#endif // !EUROPEANVANILLAOPTION.h
