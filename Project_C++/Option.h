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

	virtual ~Option() {}

};
#endif // !OPTION_H


