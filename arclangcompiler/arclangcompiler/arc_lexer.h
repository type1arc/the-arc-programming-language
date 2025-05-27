#include <stdio.h>
#include <ctype.h>
#include <string.h>


// Token Types
enum TokenType {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_SEMICOLON,
    TOKEN_UNKNOWN,
    TOKEN_END
};

// Token Structure
typedef struct {
    TokenType type;
    char value[64]; // Store token text
} Token;

// Lexer State
typedef struct {
    const char* input;
    size_t pos;
} Lexer;

// Function to Initialize Lexer
void initLexer(Lexer* lexer, const char* source) {
    lexer->input = source;
    lexer->pos = 0;
}

// Function to Get Next Character
char peek(Lexer* lexer) {
    return lexer->input[lexer->pos];
}

// Function to Advance the Lexer
void advance(Lexer* lexer) {
    lexer->pos++;
}

// Function to Extract the Next Token
Token getNextToken(Lexer* lexer) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    while (isspace(peek(lexer))) advance(lexer); // Skip whitespace

    char ch = peek(lexer);

    // Recognize Numbers
    if (isdigit(ch)) {
        int i = 0;
        while (isdigit(peek(lexer))) {
            token.value[i++] = peek(lexer);
            advance(lexer);
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
    }
    // Recognize Identifiers
    else if (isalpha(ch)) {
        int i = 0;
        while (isalnum(peek(lexer))) {
            token.value[i++] = peek(lexer);
            advance(lexer);
        }
        token.value[i] = '\0';
        token.type = TOKEN_IDENTIFIER;
    }
    // Recognize Operators
    else {
        switch (ch) {
        case '=': token.type = TOKEN_ASSIGN; strcpy_s(token.value, "="); break;
        case '+': token.type = TOKEN_PLUS; strcpy_s(token.value, "+"); break;
        case '-': token.type = TOKEN_MINUS; strcpy_s(token.value, "-"); break;
        case '*': token.type = TOKEN_MULTIPLY; strcpy_s(token.value, "*"); break;
        case '/': token.type = TOKEN_DIVIDE; strcpy_s(token.value, "/"); break;
        case ';': token.type = TOKEN_SEMICOLON; strcpy_s(token.value, ";"); break;
        case '\0': token.type = TOKEN_END; break;
        default: token.type = TOKEN_UNKNOWN; strcpy_s(token.value, "?"); break;
        }
        advance(lexer);
    }

    return token;
}

// Function to Run the Lexer
void runLexer(const char* source) {
    Lexer lexer;
    initLexer(&lexer, source);

    Token token;
    do {
        token = getNextToken(&lexer);
        printf("Token: Type = %d, Value = %s\n", token.type, token.value);
    } while (token.type != TOKEN_END);
}

