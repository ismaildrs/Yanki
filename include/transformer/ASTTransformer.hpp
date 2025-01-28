#pragma once
#include<iostream>
#include "llvm/IR/Value.h"
#include <llvm/Pass.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/IR/IRBuilder.h>
#include "llvm/IR/PassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include "visitor/Visitor.hpp"

namespace YANKI{
  class ASTTransformer: public Visitor{
  private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
  
    llvm::Function *currentFunction = nullptr;
    std::map<std::string, llvm::Value*> namedValues;

  public:
    ASTTransformer() : builder(context), module("ASTModule", context) {}
    llvm::Module& getModule() { return module; }
    void visitProgram(Program* program) override;
    void visitIdentifier(Identifier* identifier) override;
    void visitFloatFactor(FloatFactor* integerFactor) override;
    void visitIntegerFactor(IntegerFactor* integerFactor) override;
    void visitStringFactor(StringFactor* stringFactor) override;
    void visitOperation(Operation* operation) override;
    void visitStatement(Statement* statement) override;
    void visitPrintStatement(PrintStatement* printStatement) override;
    void visitExitStatement(ExitStatement* exitStatement) override;
    void visitAssignement(Assignement* assignement) override;
    void showIR() const;
  };
}