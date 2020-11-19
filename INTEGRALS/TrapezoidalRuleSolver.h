#pragma once
#include <cmath>
#include "../Expression.h"

using namespace std;


//Решения определенного интеграла методом трапеций
class TrapezoidalRuleSolver {
private:
    double beg;
    double end;
    Expression* function;
    double eps;
    int initN;
    int finN;
    double result;

    double calculate(int N);

public:
    TrapezoidalRuleSolver(double beg, double end, Expression* function, double eps, int initN);

    void solve();

    double getResult();

    int getFinalN();
};