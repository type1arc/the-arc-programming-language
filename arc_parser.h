#include "arc_lexer.hpp"
#include <vector>

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), pos(0) {}
    void parse() { for (const auto& token : tokens) std::cout << "Parsed: " << token.value << "\n"; }
private:
    std::vector<Token> tokens; size_t pos;
};
