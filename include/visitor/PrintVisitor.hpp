#pragma once
#include <iostream>
#include "visitor/Visitor.hpp"
#include "Constants.hpp"
#include "AST/AST.hpp"

namespace YANKI {
  class PrintVisitor : public Visitor {
  private:
    int indentLevel = 0;
    const std::string indentStr = "    "; // 4 spaces for each level
    void printIndent();
    std::string getOperationSymbol(OpType op);
  public:
      PrintVisitor(){
        if(isDebug()) std::cout << "Print Visitor : -----------------" << std::endl;
      };
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
  };
}
