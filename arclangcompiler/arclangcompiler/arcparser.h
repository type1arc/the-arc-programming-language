#include <iostream>
#include <string>

class Parser {
    std::string input;
    size_t pos = 0;

    char peek() { return input[pos]; }
    void advance() { pos++; }

public:
    Parser(std::string src) : input(src) {}

    void parseAssignment() {
        std::string var = parseIdentifier();
        expect('=');
        int value = parseExpression();
        expect(';');
        std::cout << "Parsed assignment: " << var << " = " << value << "\n";
    }

    std::string parseIdentifier() {
        std::string id = "";
        while (isalpha(peek())) {
            id += peek();
            advance();
        }
        return id;
    }

    int parseExpression() {
        int result = parseNumber();
        while (peek() == '+' || peek() == '-') {
            char op = peek();
            advance();
            int num = parseNumber();
            result = (op == '+') ? result + num : result - num;
        }
        return result;
    }

    int parseNumber() {
        int num = 0;
        while (isdigit(peek())) {
            num = num * 10 + (peek() - '0');
            advance();
        }
        return num;
    }

    void expect(char c) {
        if (peek() == c) advance();
        else throw std::runtime_error("Unexpected token");
    }
};

