#include <iostream>
#include "../Expression.h"
#include "../GAUSS//GaussianSolver.h"
#include "NewtonSolver.h"

using namespace std;


//Чтобы задать функцию необходимо отнаследоваться от Expression
class F1 : public Expression {
public:
    double F(double* args) override {
        return cos(0.4 * args[1] + args[0] * args[0]) + args[1] * args[1] + args[0] * args[0] - 1.6;
    }
};
class F2 : public Expression {
public:

    double F(double* args) override {
        return 1.5 * args[0] * args[0] - args[1] * args[1] / 0.36 - 1;
    }

};
class F3 : public Expression {
    double F(double* vArg) override {
        return log10(vArg[1]/vArg[2]) - vArg[0] + 1;
    }
};
class F4 : public Expression {
    double F(double* vArg) override {
        return vArg[0] * vArg[1] / 20 - vArg[2] + 2;
    }
};
class F5 : public Expression {
    double F(double* vArg) override {
        return 2 * vArg[0] * vArg[0] + vArg[1] - vArg[2] - 0.4;
    }
};


int main() {

    int kMax = 30;
    double eps = 1e-9;

    //Test 1

    Expression** funcs1 = new Expression*[2];
    funcs1[0] = new F1;
    funcs1[1] = new F2;

    double* initApprox = new double[2];
    initApprox[0] = -1;
    initApprox[1] = 1;

    NewtonSolver solver(2, funcs1, kMax, initApprox, eps);
    solver.solve();

    cout << "Solutions:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << 'X' << i << " = " << solver.getSolutions()[i] << endl;
    }
    cout << "Solved in " << solver.getStepsAmount() << " steps" << endl << endl;

    //Test 2

    Expression** funcs2 = new Expression*[3];
    funcs2[0] = new F3;
    funcs2[1] = new F4;
    funcs2[2] = new F5;

    double* initApprox2 = new double[3];
    initApprox2[0] = 1;
    initApprox2[1] = 2.2;
    initApprox2[2] = 2;

    NewtonSolver solver2(3, funcs2, kMax, initApprox2, eps);
    solver2.solve();

    cout << "Solutions: " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << 'X' << i << " = " << solver2.getSolutions()[i] << endl;
    }
    cout << "Solved in " << solver2.getStepsAmount() << " steps" << endl << endl;
    return 0;

}