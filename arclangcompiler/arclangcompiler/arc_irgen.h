#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"


void generateIR() {
    llvm::LLVMContext Context;
    llvm::Module* Module = new llvm::Module("ArcLang", Context);
    llvm::IRBuilder<> Builder(Context);

    // Define function type: int main()
    llvm::FunctionType* FuncType = llvm::FunctionType::get(Builder.getInt32Ty(), false);
    llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", Module);

    // Create function entry block
    llvm::BasicBlock* EntryBB = llvm::BasicBlock::Create(Context, "entry", Func);
    Builder.SetInsertPoint(EntryBB);

    // Generate IR: x = 10 + 5
    llvm::Value* Result = Builder.CreateAdd(Builder.getInt32(10), Builder.getInt32(5), "x");
    Builder.CreateRet(Result);

    // Print generated IR
    Module->print(llvm::outs(), nullptr);

    delete Module;
}