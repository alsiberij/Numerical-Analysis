#include "LeastSquaresApproximator.h"

LeastSquaresApproximator::LeastSquaresApproximator(ifstream& file, int polynomialPower) {
    if (!file.is_open()) {
        cerr << "FILE NOT FOUND" << endl;
        throw exception();
    }
    file >> N;
    X = new double[N];
    Y = new double[N];
    for (int i = 0; i < N; ++i) {
        file >> X[i];
    }
    for (int i = 0; i < N; ++i) {
        file >> Y[i];
    }
    this->polynomialPower = polynomialPower;
    polynomial = nullptr;
}

void LeastSquaresApproximator::solve() {
    double* powerX = new double[2 * polynomialPower];

    for (int i = 0; i < 2 * polynomialPower; ++i) {     //Вычисление сумм степеней иксов
        powerX[i] = 0;
        for (int j = 0; j < N; ++j) {
            double curElem = X[j];
            for (int k = 0; k < i; ++k) {
                curElem *= X[j];
            }
            powerX[i] += curElem;
        }
    }

    double* right = new double[polynomialPower + 1];    //Вычисление правой части матрицы
    for (int i = 0; i < polynomialPower + 1; ++i) {
        right[i] = 0;
        for (int j = 0; j < N; ++j) {
            double curXi = 1;
            for (int k = 0; k < i; ++k) {
                curXi *= X[j];
            }
            right[i] += Y[j] * curXi;
        }
    }



    double** A = new double*[polynomialPower + 1];
    for (int i = 0; i < polynomialPower + 1; ++i) {
        A[i] = new double [polynomialPower + 2];
    }

    A[0][0] = N;
    for (int i = 0; i < polynomialPower + 1; ++i) {
        for (int j = 0; j < polynomialPower + 1; ++j) {
            if (i + j - 1 >= 0) {
                A[i][j] = powerX[i + j - 1];
            }
        }
        A[i][polynomialPower + 1] = right[i];
    }


    GaussianSolver solver(A, polynomialPower + 1);          //Решение системы линйных уравнений
    solver.solve();
    double* sols = solver.getSolutions();

    polynomial = new Polynomial(polynomialPower, sols);

    delete [] powerX;
    delete [] right;
    for (int i = 0; i < polynomialPower + 1; ++i) {
        delete [] A[i];
    }
    delete [] A;
}

Polynomial *LeastSquaresApproximator::getPolynomial() {
    return polynomial;
}

LeastSquaresApproximator::~LeastSquaresApproximator() {
    delete [] X;
    delete [] Y;
    delete polynomial;
}

double LeastSquaresApproximator::getVariance() {
    double variance = 0;
    for (int i = 0; i < N; ++i) {
        variance += (polynomial->F(&X[i]) - Y[i]) * (polynomial->F(&X[i]) - Y[i]);
    }
    variance = variance / (N - polynomialPower - 1);
    return variance;
}

double LeastSquaresApproximator::getStdDeviation() {
    return sqrt(getVariance());
}
