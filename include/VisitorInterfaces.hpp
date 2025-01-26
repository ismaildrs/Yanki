#include <iostream>
#include <AST.hpp>

namespace YANKI
{
  class Visitor
  {
    public:
    virtual void visitProgram(Program*) = 0;
    virtual void visitVariable(Variable*) = 0;
    virtual void visitFloatFactor(FloatFactor*) = 0;
    virtual void visitIntegerFactor(IntegerFactor*) = 0;
    virtual void visitStringFactor(StringFactor*) = 0;
    virtual void visitOperation(Operation*) = 0;
    virtual void visitStatement(Statement*) = 0;
  };

  class Visitable
  {
    public:
    virtual void accept(Visitor* v) = 0;
  };

}