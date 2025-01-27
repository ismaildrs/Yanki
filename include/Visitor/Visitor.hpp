#pragma once
#include <iostream>
#include "AST/nodes/Program.hpp"
#include "AST/nodes/Statement.hpp"
#include "AST/nodes/Identifier.hpp"
#include "AST/nodes/Expression.hpp"
#include "AST/nodes/FloatFactor.hpp"
#include "AST/nodes/IntegerFactor.hpp"
#include "AST/nodes/StringFactor.hpp"
#include "AST/nodes/Operation.hpp"
#include "AST/nodes/PrintStatement.hpp"
#include "AST/nodes/ExitStatement.hpp"

namespace YANKI
{
  class Visitor
  {
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
  };
}