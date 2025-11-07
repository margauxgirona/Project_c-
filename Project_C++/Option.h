#pragma once
#ifndef OPTION_H
#define OPTION_H

#include <iostream>
class Option
{
private:
	double _expiry;
public:
	Option(double expiry) : _expiry(expiry) {}

	double getExpiry() const {
		return _expiry;
	}
	virtual double payoff(double S) const = 0;
	virtual double payoffPath(const std::vector<double>& spots) const
	{
		if (spots.empty()) {
			return 0.0;
		}
		return payoff(spots.back());
	}

	virtual bool isAsianOption() const { return false; }


	virtual ~Option() {}

	//Ajout MF
	virtual bool isAmericanOption();

};
#endif // !OPTION_H


