#include "arc_parser.h"
#include "arc_lexer.hpp"

// ENTRY POINT
int main() {
    std::string input = "x = 1;";
    Tokenizer tokenizer(input);
    std::vector<Token> tokens;

    Token token;
    while ((token = tokenizer.nextToken()).type != TokenType::End) tokens.push_back(token);

    Parser parser(tokens);
    parser.parse();


    std::cout << std::endl << "DONE" << std::endl;
    return EXIT_SUCCESS;
}
