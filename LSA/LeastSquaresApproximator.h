#pragma once
#include <iomanip>
#include <iostream>
#include "../GAUSS/GaussianSolver.h"
#include "Polynomial.h"

using namespace std;

//Апроксимация функции методом наименьших квадратов
//Результат работы этого класса - экземпляр polynomial, который является наследником Expression, т.е просто функция
class LeastSquaresApproximator {
private:
    int N;
    double* X;
    double* Y;
    int polynomialPower;
    Polynomial* polynomial;

public:
    //Формат: Первое число - кол-во точек, далее все X, потом все Y
    LeastSquaresApproximator(ifstream& file, int polynomialPower);

    void solve();

    Polynomial* getPolynomial();

    double getVariance();       //Дисперсия

    double getStdDeviation();   //Среднеквадратическое отклонение

    ~LeastSquaresApproximator();
};