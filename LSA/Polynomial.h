#pragma once
#include <iostream>
#include "../Expression.h"

using namespace std;

//Результат работы аппроксиматора - полиномиальная функция
class Polynomial : public Expression {
private:
    int dim;
    double* params;     //Множители перед степенями переменной, х^0, x^1 ... x^n

public:
    Polynomial(int dim, double* params) {
        this->dim = dim;
        this->params = new double[dim + 1];
        for (int i = 0; i < dim + 1; ++i) {
            this->params[i] = params[i];
        }
    }

    double F(double* x) override {
        double result = params[0];
        for (int i = 1; i < dim + 1; ++i) {
            double xPower = *x;
            for (int j = 1; j < i; ++j) {
                xPower *= *x;
            }
            result += xPower * params[i];
        }
        return result;
    }

    double D(int curArg, int argsAmount, double* x) override {
        double result = params[1];
        for (int i = 2; i < dim + 1; ++i) {
            double xPower = *x;
            for (int j = 1; j < i - 1; ++j) {
                xPower *= *x;
            }
            result += xPower * params[i] * i;
        }
        return result;
    }

    void print() {
        cout << "y = ";
        cout << params[0];
        for (int i = 1; i < dim + 1; ++i) {
            cout << (params[i] >= 0 ? "+" : "") << params[i] << "*x^" << i;
        }
        cout << endl;
    }
};