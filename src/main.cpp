#include <iostream>
#include <cmath>

double recursive_sqr(double number_input, double number_compare_actual);

double recursive_sqr(double number_input, double number_compare_actual) {
    double x = 0.5 * (number_compare_actual + (number_input / number_compare_actual));

    if (std::abs(x - number_compare_actual) < 0.00001) {
        return x;
    }   
    
    return recursive_sqr(number_input, x);
}

int main () {

    int max_iterrations = 100;
    double number_input = 0;

    std::cin >> number_input;

    for (int i = 1; i < max_iterrations; i++) {
        double number_compare_actual = i * i;

        if(number_compare_actual >= number_input) {
            double result = recursive_sqr(number_input, number_compare_actual);
            std::cout << "Nearest square number to input is:" << result << "\n";
            break;
        }
    }
    return 0;
}