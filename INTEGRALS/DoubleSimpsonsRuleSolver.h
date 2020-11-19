#pragma once
#include <cmath>
#include "../Expression.h"

using namespace std;


//Вычисление двойного интеграла методом Симпсона
class DoubleSimpsonsRuleSolver {
private:
    Expression* function;
    double begX;
    double endX;
    double begY;
    double endY;
    int initN;
    int finN;
    int initM;
    int finM;
    double eps;
    double result;

    double calculate(int N, int M);

public:
    DoubleSimpsonsRuleSolver(double begX, double endX, double begY, double endY, Expression* function, double eps, int initN, int initM);

    void solve();

    double getResult();

    int getFinalN();

    int getFinalM();
};
