#pragma once
#include <iostream>
#include <stdexcept>
#include "visitor/Visitable.hpp"


namespace YANKI
{
  // TypeCheckerVisitor: checks the types of factors and ensures valid operations
  class TypeCheckerVisitor : public Visitor
  {
  private:
    FactorType currentType; // Keeps track of the type being checked

    void ensureCompatibleTypes(FactorType type1, FactorType type2, OpType op)
    {
      if (type1 == STRING || type2 == STRING)
      {
        if (op != ADD)
        {
          throw std::runtime_error("Invalid operation on STRING type. Only ADD is allowed.");
        }
      }
      else if (type1 != type2)
      {
        throw std::runtime_error("Type mismatch: operands must have the same type.");
      }
    }

  public:
    void visitFloatFactor(FloatFactor *factor) override
    {
      currentType = FLOAT;
    }

    void visitIntegerFactor(IntegerFactor *factor) override
    {
      currentType = INT;
    }

    void visitStringFactor(StringFactor *factor) override
    {
      currentType = STRING;
    }

    void visitIdentifier(Identifier *variable) override
    {
      if (variable->getExpression() != nullptr)
      {
        variable->getExpression()->accept(this); // Visit the factor within the variable
      }
    }

    void visitOperation(Operation *operation) override
    {
      // Type check factor1
      operation->getFactor1()->accept(this);
      FactorType type1 = currentType;

      // Type check factor2
      operation->getFactor2()->accept(this);
      FactorType type2 = currentType;

      // Ensure the operation is valid for the operand types
      ensureCompatibleTypes(type1, type2, operation->getOp());
    }

    void visitStatement(Statement *statement) override
    {
      for (Visitable* child : statement->getChildren())
      {
        child->accept(this);
      }
    }

    void visitProgram(Program *program) override
    {
      for (Visitable* child : program->getChildren())
      {
        child->accept(this);
      }
    }
  };
}
