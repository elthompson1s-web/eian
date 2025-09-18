#include <iostream>
#include <string>
#include <sstream>
#include <numeric> // for std::gcd
#include <cmath>   // for std::pow

struct Fraction {
    int numerator;
    int denominator;

    // Constructor for integer
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        simplify();
    }

    // Simplify fraction by gcd
    void simplify() {
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        int gcd_val = std::gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
    }

    // Parse from string like "3" or "3/4"
    static bool parse(const std::string& input, Fraction& frac) {
        size_t slash_pos = input.find('/');
        if (slash_pos == std::string::npos) {
            // no slash, just integer
            try {
                int num = std::stoi(input);
                frac = Fraction(num, 1);
                return true;
            } catch (...) {
                return false;
            }
        } else {
            try {
                int num = std::stoi(input.substr(0, slash_pos));
                int denom = std::stoi(input.substr(slash_pos + 1));
                if (denom == 0) return false;
                frac = Fraction(num, denom);
                return true;
            } catch (...) {
                return false;
            }
        }
    }

    // Overload operators for +, -, *, /
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::runtime_error("Division by zero");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    // New: Exponentiation with integer exponent
    Fraction pow(int exponent) const {
        if (exponent == 0) {
            // anything ^ 0 = 1
            return Fraction(1,1);
        }

        // Compute numerator^exponent and denominator^exponent
        int num_pow = static_cast<int>(std::pow(numerator, std::abs(exponent)));
        int denom_pow = static_cast<int>(std::pow(denominator, std::abs(exponent)));

        if (exponent > 0) {
            return Fraction(num_pow, denom_pow);
        } else {
            // negative exponent means reciprocal
            if (num_pow == 0) {
                throw std::runtime_error("Division by zero in negative exponent");
            }
            return Fraction(denom_pow, num_pow);
        }
    }

    void print() const {
        if (denominator == 1) {
            std::cout << numerator;
        } else {
            std::cout << numerator << "/" << denominator;
        }
    }
};

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
        std::string s_number1, s_number2;
        char op;

        std::cout << "Enter question (can use fractions and '^' for exponent): ";
        std::cin >> s_number1 >> op;

        Fraction number1, number2;
        if (!Fraction::parse(s_number1, number1)) {
            std::cout << "Invalid input for first number.\n";
            continue;
        }

        if (op == '^') {
            // For exponentiation, second input is an integer (exponent)
            int exponent;
            std::cin >> exponent;

            try {
                Fraction result = number1.pow(exponent);
                std::cout << "Result: ";
                result.print();
                std::cout << "\n";
            } catch (std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else {
            // Other operators expect a fraction as second number
            std::cin >> s_number2;
            if (!Fraction::parse(s_number2, number2)) {
                std::cout << "Invalid input for second number.\n";
                continue;
            }

            try {
                Fraction result;
                switch(op) {
                    case '+':
                        result = number1 + number2;
                        break;
                    case '-':
                        result = number1 - number2;
                        break;
                    case '*':
                        result = number1 * number2;
                        break;
                    case '/':
                        result = number1 / number2;
                        break;
                    default:
                        std::cout << "Invalid operator!\n";
                        continue;
                }

                std::cout << "Result: ";
                result.print();
                std::cout << "\n";

            } catch (std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }

        std::cout << "Do you want to restart? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Goodbye!\n";

    return 0;
}
