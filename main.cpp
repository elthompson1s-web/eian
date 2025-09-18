#include <iostream>

int divide(int number1, int number2){
    return(number1 / number2);
} 
int subtract(int number1, int number2){
    return(number1 - number2);
}
int addition(int number1, int number2){
    return(number1 + number2);
}
int multiply(int number1, int number2){
    return(number1 * number2);
}

int main() {
    int number1;
    int number2;
    int number3;
    char io;
    char op;
    
    
    do {
        std::cout << "whats your first number ";
        std::cin >> number1;
        std::cout << "whats your operator ";
        std::cin >> op;
        std::cout << "whats your second number ";
        std::cin >> number2;

        switch(op) {
            case '*': number3 = multiply(number1, number2); break;
            case '+': number3 = addition(number1, number2); break;
            case '-': number3 = subtract(number1, number2); break;
            case '/': number3 = divide(number1, number2); break;
            
        }

        std::cout << "your number was: " << number3 << '\n';
        std::cout << "wanna restart? (y/n)";
        std::cin >> io; std::cout << '\n';
    } while (io != 'n' || 'N');
    
    }
    
   
