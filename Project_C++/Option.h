#pragma once
#include <iostream>
#include <vector>

class Option
{
private:
	double _expiry;

public:

	Option(double expiry);

	double getExpiry() const;

	virtual double payoff(double S) const = 0;
	virtual double payoffPath(const std::vector<double>& spots) const;
	virtual bool isAsianOption() const;
	virtual bool isAmericanOption() const;

	virtual ~Option();
};