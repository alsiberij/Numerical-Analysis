#include <iostream>
#include <cmath>
#include "SimpsonsRuleSolver.h"
#include "TrapezoidalRuleSolver.h"
#include "DoubleSimpsonsRuleSolver.h"

using namespace std;


//Функция одной переменной
class F1 : public Expression {
public:
    double F(double* args) override {
        return sqrt(1 + 2 * args[0] * args[0] * args[0]);
    }
};

//Функция двух переменных, первый эелемент массива args это Х, второй - Y
class F2 : public Expression {
    double F(double* args) override {
        return args[0] * args[0] / (1 + args[1] * args[1]);
    }
};


int main() {
    double a = 1.2;
    double b = 2.471;
    double eps = 1e-7;
    int n = 2;

    SimpsonsRuleSolver solverS(a, b, new F1, eps, n);
    TrapezoidalRuleSolver solverT(a, b, new F1, eps, n);
    DoubleSimpsonsRuleSolver solverD(0, 4, 1, 2, new F2, eps, n, n);
    solverS.solve();
    solverT.solve();
    solverD.solve();
    cout << endl << solverS.getResult() << " " << solverT.getResult() << " " << solverD.getResult();

    return 0;
}
