#pragma once
#include "Visitor/Visitable.hpp"
#include<iostream>
#include<vector>

namespace YANKI{
  class Statement : public Visitable // represents an expression: an instruction terminated with ";" - END_EXPR
  {
  private:
    std::vector<Visitable*> children;

  public:
    void accept(Visitor* v) override
    {
      v->visitStatement(this);
    }

    inline const std::vector<Visitable*>& getChildren() const
    {
      return children;
    }

    void addChild(Visitable* child)
    {
      children.push_back(child);
    }
  };
}