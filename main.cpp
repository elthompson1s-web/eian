#include <iostream>
#include <string>
#include <cmath> 

//operators for the calc
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
   //password and restarts you wether you get the pass wrong or right
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
//the question/outputs 
        std::cout << "what is the question ";
        std::cin >> number1;

        std::cin >> op;


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
//result for the calc
        std::cout << "Result: " << result << "\n";

        std::cout << "do you want to restart? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Goodbye!\n";

    return 0;
}
