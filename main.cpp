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
    char op;
    
    std::cout << "whats your first number ";
    std::cin >> number1;
    std::cout << "whats your operator ";
    std::cin >> op;
    std::cout << "whats your second number ";
    std::cin >> number2;
    if (op == '*'){
        number3 = multiply(number1, number2); 
    }
    if (op == '+'){
        number3 = addition(number1, number2);
    }
    if (op == '-'){
        number3 = subtract(number1, number2);
    }
    if (op == '/'){
        number3 = divide(number1, number2);
    }
    
    std::cout << "your number was: " << number3;
    
    

}   
