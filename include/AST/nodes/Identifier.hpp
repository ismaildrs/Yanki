#pragma once
#include "Visitor/Visitable.hpp"

namespace YANKI{
  class Identifier : public Visitable
  {
  private:
    std::string varname;
    Visitable* expression; // ex= i: (1+3)/2;

  public:

    Identifier(std::string name): varname(name){
    }

    void accept(Visitor* v) override
    {
      v->visitIdentifier(this);
    }

    const std::string& getVarName() const
    {
      return varname;
    }

    void setVarName(const std::string& name)
    {
      varname = name;
    }

    Visitable* getExpression() const
    {
      return expression;
    }

    void setExpression(Visitable* expression)
    {
      expression = expression;
    }
  };
}