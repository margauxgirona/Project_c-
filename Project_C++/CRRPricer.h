#pragma once

#include <iostream>
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "PutOption.h"
#include "CallOption.h"
#include "BinaryTree.h"
#include "AsianOption.h"

class CRRPricer{
    private:
        Option * _option;
        int _depth;
        double _S0;
        double _u;
        double _d;
        double _r;

        // tree of prices of the option
        BinaryTree<double> _H;
        // boolean tree of early exercises
        BinaryTree<bool> _Exercise;

        bool _computed;

        // function to compute the power 
        double intPow(double a, int exponent) const;
    
    public:
        CRRPricer(Option * option, int depth, double asset_price, double up, double down, double interest_rate);
        
        CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);

        void compute();

        double get(int n, int i) const;
        bool getExercise(int n, int i) const;

        double operator()(bool closed_form = false);
};
