#pragma once
#include <iostream>

// Forward declarations
namespace YANKI {
  class Program;
  class Statement;
  class Identifier;
  class Expression;
  class FloatFactor;
  class IntegerFactor;
  class StringFactor;
  class Operation;
  class PrintStatement;
  class ExitStatement;
  class Assignement;
}

namespace YANKI {
  class Visitor {
  public:
      virtual void visitProgram(Program*) = 0;
      virtual void visitIdentifier(Identifier*) = 0;
      virtual void visitFloatFactor(FloatFactor*) = 0;
      virtual void visitIntegerFactor(IntegerFactor*) = 0;
      virtual void visitStringFactor(StringFactor*) = 0;
      virtual void visitOperation(Operation*) = 0;
      virtual void visitStatement(Statement*) = 0;
      virtual void visitPrintStatement(PrintStatement*) = 0;
      virtual void visitExitStatement(ExitStatement*) = 0;
      virtual void visitAssignement(Assignement*) = 0;
  };
}
