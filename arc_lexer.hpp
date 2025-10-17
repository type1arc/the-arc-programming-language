#ifndef LEXER_H
#define LEXER_H 

#include <iostream>
#include <ctype.h>

enum class TokenType { Identifier, Number, Symbol, End };
struct Token { TokenType type; std::string value; };

class Tokenizer {
public:
    explicit Tokenizer(const std::string& src) : source(src), pos(0) {}
    Token nextToken() {
        while (pos < source.size() && isspace(source[pos])) pos++;
        if (pos >= source.size()) return { TokenType::End, "" };
        if (isalpha(source[pos])) return identifier();
        if (isdigit(source[pos])) return number();
        return symbol();
    }

private:
    std::string source;
    size_t pos;
    Token identifier() { size_t start = pos; while (isalnum(source[pos])) pos++; return { TokenType::Identifier, source.substr(start, pos - start) }; }
    Token number() { size_t start = pos; while (isdigit(source[pos])) pos++; return { TokenType::Number, source.substr(start, pos - start) }; }
    Token symbol() { return { TokenType::Symbol, std::string(1, source[pos++]) }; }
};

#endif
