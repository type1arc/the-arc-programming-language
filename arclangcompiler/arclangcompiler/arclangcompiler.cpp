#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

// ---- LEXER (Tokenizer) ----
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

// ---- PARSER ----
class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), pos(0) {}
    void parse() { for (const auto& token : tokens) std::cout << "Parsed: " << token.value << "\n"; }
private:
    std::vector<Token> tokens; size_t pos;
};

// ---- LLVM IR GENERATOR ----
using namespace llvm;

std::string generateLLVMIR() {
    LLVMContext context;
    Module module("ArcModule", context);
    IRBuilder<> builder(context);

    FunctionType* funcType = FunctionType::get(Type::getInt32Ty(context),
        { Type::getInt32Ty(context), Type::getInt32Ty(context) },
        false);
    Function* func = Function::Create(funcType, Function::ExternalLinkage, "add", module);

    BasicBlock* entry = BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    auto args = func->arg_begin();
    Value* x = args++; x->setName("x");
    Value* y = args++; y->setName("y");

    Value* result = builder.CreateAdd(x, y, "sum");
    builder.CreateRet(result);

    verifyFunction(*func);

    std::string irString;
    raw_string_ostream irStream(irString);
    module.print(irStream, nullptr);

    return irString;
}

// ---- NASM ASSEMBLY CODE GENERATOR ----
void generateNASM() {
    std::ofstream asmFile("arc.asm");
    asmFile << "section .text\n";
    asmFile << "global _start\n\n";
    asmFile << "_start:\n";
    asmFile << "    mov eax, [x]\n";
    asmFile << "    add eax, [y]\n";
    asmFile << "    mov [sum], eax\n";
    asmFile << "    mov eax, 1\n";
    asmFile << "    int 0x80\n\n";
    asmFile << "section .data\n";
    asmFile << "x dd 10\n";
    asmFile << "y dd 20\n";
    asmFile << "sum dd 0\n";
    asmFile.close();
}

// ---- MAIN ENTRY POINT ----
void main() {
    std::string input = "x = 42;";
    Tokenizer tokenizer(input);
    std::vector<Token> tokens;

    Token token;
    while ((token = tokenizer.nextToken()).type != TokenType::End) tokens.push_back(token);

    Parser parser(tokens);
    parser.parse();

    std::cout << "\nGenerating LLVM IR...\n";
    generateLLVMIR();

    std::cout << "\nGenerating NASM Assembly...\n";
    generateNASM();

    std::cout << "Compilation process completed!\n";
}