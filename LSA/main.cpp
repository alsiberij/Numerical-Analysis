#include <iostream>
#include "LeastSquaresApproximator.h"
#include "Polynomial.h"

using namespace std;


int main() {

    ifstream file("../LSA/sample.txt");

    LeastSquaresApproximator interpolator(file, 3);
    interpolator.solve();
    Polynomial* polynomial = interpolator.getPolynomial();

    polynomial->print();
    cout << interpolator.getVariance() << " " << interpolator.getStdDeviation();

    return 0;
}