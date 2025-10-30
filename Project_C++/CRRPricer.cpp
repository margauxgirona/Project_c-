#include <iostream>
#include "CRRPricer.h"

CRRPricer::CRRPricer(Option * option, int depth, double asset_price, double up, double down, double interest_rate) :
    _option(option), _depth(depth), _S0(asset_price), _u(up), _d(down), _r(interest_rate) {
        // check for arbitrage
        if (!(down < interest_rate && interest_rate < up))
            throw std::invalid_argument("Arbitrage condition is not respected, we must have : D < R < U.");

        // trees initialisation
        _S.setDepth(depth);
        _H.setDepth(depth);

        _computed = false;
}

// function created to replace std::pow()
// because std::pow() is generic and computationnally expensive 
double CRRPricer::intPow(double a, int exponent) const{
    double result = 1.0;
    for(int i = 0; i < exponent; i++)
        result *= a;
    return result;
}

void CRRPricer::compute(){
    // fill the _stockTree with the prices
    for(int n = 0; n <= _depth; n++){
        for(int i = 0; i <= n; i++){
            _S.setNode(n, i, _S0 * intPow(1 + _u, i) * intPow(1 + _d, n-i));
        }
    }
    // at expiracy date (at N = _depth)
    for(int i = 0; i <= _depth; i++){
        _H.setNode(_depth, i, _option->payoff(_S.getNode(_depth, i)));
    }

    // risk neutral probability
    double q = (_r - _d) / (_u - _d);

    // compute _H
    for(int n = _depth-1; n >= 0; n--){
        for(int i = 0; i <= n; i++){
            double value = q * _H.getNode(n+1, i+1) + (1 -q) * _H.getNode(n+1, i);
            value /= (1 + _r);
            _H.setNode(n, i, value);
        }
    }

    _computed = true; 
}

double CRRPricer::get(int n, int i) const {
    if (n > _depth || i > n)
        throw std::out_of_range("CRRPricer::get indices out of range");
    return _H.getNode(n, i);
}

static long double factorial(int n) {
    long double res = 1.0;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

double CRRPricer::operator()(bool closed_form) {
    if (!(_computed))
        compute();
    
    if (!(closed_form))
        return _H.getNode(0, 0);
    else{
        double discount = 1 / intPow(1 + _r, _depth);
        // risk neutral probability
        double q = (_r - _d) / (_u - _d);
        double facto_N = factorial(_depth);
        double sum = 0.0;
        for(int i = 0; i <= _depth; i++){
            sum += (facto_N / (factorial(i) * factorial(_depth - i))) * intPow(q, i) * intPow(1 - q, _depth - i) * _option->payoff(_S.getNode(_depth, i));
        }
        return discount * sum;
    }
}