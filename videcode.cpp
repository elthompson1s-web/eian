#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <vector>
#include <cctype>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <map>

struct Fraction {
    int numerator;
    int denominator;

    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        simplify();
    }

    void simplify() {
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        int gcd_val = std::gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
    }

    static bool parse(const std::string& input, Fraction& frac) {
        size_t slash_pos = input.find('/');
        if (slash_pos == std::string::npos) {
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
        if (other.numerator == 0) throw std::runtime_error("Division by zero");
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    Fraction pow(int exponent) const {
        if (exponent == 0) return Fraction(1,1);
        int num_pow = static_cast<int>(std::pow(numerator, std::abs(exponent)));
        int denom_pow = static_cast<int>(std::pow(denominator, std::abs(exponent)));
        if (exponent > 0) {
            return Fraction(num_pow, denom_pow);
        } else {
            if (num_pow == 0) throw std::runtime_error("Division by zero in negative exponent");
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

// Token types
enum class TokenType { Number, Operator, LeftParen, RightParen };

// Token structure
struct Token {
    TokenType type;
    std::string value; // number as string or operator symbol

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

// Helper: operator precedence
int precedence(const std::string& op) {
    if (op == "^") return 4;
    if (op == "*" || op == "/") return 3;
    if (op == "+" || op == "-") return 2;
    return 0;
}

// Helper: operator associativity (true for right-associative)
bool isRightAssociative(const std::string& op) {
    return op == "^";
}

// Tokenize input string
std::vector<Token> tokenize(const std::string& expr) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '-') {
            // Parse a number or fraction (possibly negative)
            size_t start = i;
            if (expr[i] == '-') i++; // consume leading minus
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '/')) i++;
            tokens.emplace_back(TokenType::Number, expr.substr(start, i - start));
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            tokens.emplace_back(TokenType::Operator, std::string(1, expr[i]));
            i++;
        }
        else if (expr[i] == '(') {
            tokens.emplace_back(TokenType::LeftParen, "(");
            i++;
        }
        else if (expr[i] == ')') {
            tokens.emplace_back(TokenType::RightParen, ")");
            i++;
        }
        else {
            throw std::runtime_error(std::string("Invalid character in expression: ") + expr[i]);
        }
    }
    return tokens;
}

// Shunting Yard algorithm to convert infix tokens to RPN
std::queue<Token> shuntingYard(const std::vector<Token>& tokens) {
    std::queue<Token> outputQueue;
    std::stack<Token> opStack;

    for (const auto& token : tokens) {
        if (token.type == TokenType::Number) {
            outputQueue.push(token);
        }
        else if (token.type == TokenType::Operator) {
            while (!opStack.empty()) {
                Token top = opStack.top();
                if (top.type != TokenType::Operator)
                    break;

                int topPre = precedence(top.value);
                int currPre = precedence(token.value);

                if ((isRightAssociative(token.value) && currPre < topPre) || 
                    (!isRightAssociative(token.value) && currPre <= topPre)) {
                    outputQueue.push(top);
                    opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(token);
        }
        else if (token.type == TokenType::LeftParen) {
            opStack.push(token);
        }
        else if (token.type == TokenType::RightParen) {
            bool foundLeftParen = false;
            while (!opStack.empty()) {
                Token top = opStack.top();
                opStack.pop();
                if (top.type == TokenType::LeftParen) {
                    foundLeftParen = true;
                    break;
                } else {
                    outputQueue.push(top);
                }
            }
            if (!foundLeftParen) {
                throw std::runtime_error("Mismatched parentheses");
            }
        }
    }

    while (!opStack.empty()) {
        if (opStack.top().type == TokenType::LeftParen || opStack.top().type == TokenType::RightParen)
            throw std::runtime_error("Mismatched parentheses");
        outputQueue.push(opStack.top());
        opStack.pop();
    }

    return outputQueue;
}

// Evaluate RPN expression
Fraction evaluateRPN(std::queue<Token> rpnQueue) {
    std::stack<Fraction> stack;

    while (!rpnQueue.empty()) {
        Token token = rpnQueue.front();
        rpnQueue.pop();

        if (token.type == TokenType::Number) {
            Fraction f;
            if (!Fraction::parse(token.value, f)) {
                throw std::runtime_error("Invalid number: " + token.value);
            }
            stack.push(f);
        }
        else if (token.type == TokenType::Operator) {
            if (stack.size() < 1) throw std::runtime_error("Insufficient operands");

            if (token.value == "^") {
                // exponentiation is right-associative and unary operator here expects integer exponent
                Fraction base = stack.top(); stack.pop();
                if (stack.empty()) throw std::runtime_error("Insufficient operands for exponentiation");
                Fraction exponentFrac = stack.top(); stack.pop();

                if (exponentFrac.denominator != 1) {
                    throw std::runtime_error("Exponent must be an integer");
                }
                int exponent = exponentFrac.numerator;

                stack.push(base.pow(exponent));
            } else {
                // For other operators, pop two operands
                if (stack.size() < 2) throw std::runtime_error("Insufficient operands");
                Fraction right = stack.top(); stack.pop();
                Fraction left = stack.top(); stack.pop();

                if (token.value == "+") {
                    stack.push(left + right);}
        
