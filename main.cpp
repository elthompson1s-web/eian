#include <iostream>
#include <string>
#include <cmath>

int divide(int number1, int number2) {
    return number1 / number2;
}

int subtract(int number1, int number2) {
    return number1 - number2;
}

int addition(int number1, int number2) {
    return number1 + number2;
}

int multiply(int number1, int number2) {
    return number1 * number2;
}

int main() {
    const std::string correctpass = "5219";
    std::string input;

    std::cout << "What is the pass? ";
    std::cin >> input;

    if (input != correctpass) {
        std::cout << "Incorrect password.\n";
        return 0;  
    }

    std::cout << "Correct!\n";

    char choice;
    do {
        int number1, number2, result;
        char op;

        std::cout << "What's your first number? ";
        std::cin >> number1;

        std::cout << "What's your operator (+, -, *, /)? ";
        std::cin >> op;

        std::cout << "What's your second number? ";
        std::cin >> number2;

        switch(op) {
            case '+':
                result = addition(number1, number2);
                break;
            case '-':
                result = subtract(number1, number2);
                break;
            case '*':
                result = multiply(number1, number2);
                break;
            case '/':
                if (number2 == 0) {
                    std::cout << "Error: Division by zero is not allowed.\n";
                    continue;
                }
                result = divide(number1, number2);
                break;
            default:
                std::cout << "Invalid operator!\n";
                continue;
        }

        std::cout << "Result: " << result << "\n";

        std::cout << "Wanna restart? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Goodbye!\n";

    return 0;
}
