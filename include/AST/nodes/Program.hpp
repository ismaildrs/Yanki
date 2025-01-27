#pragma once
#include "Visitor/Visitable.hpp"
#include <vector>


namespace YANKI {
  // A list of statements
  class Program : public Visitable {
  private:
    std::vector<Visitable*> children;

  public: // TODO: constructors ?? 

    void accept(Visitor* v) override
    {
      v->visitProgram(this);
    }

    inline const std::vector<Visitable*> getChildren() const
    {
      return children;
    }

    void addChild(Visitable* child)
    {
      children.push_back(child);
    }
  };
}