#pragma once
#include "visitor/Visitable.hpp"
#include <vector>

namespace YANKI {
  // A list of statements
  class Program : public Visitable {
  private:
      std::vector<Visitable*> children;

  public:
      // Constructors
      Program() = default;
      Program(const std::vector<Visitable*>& children) : children(children) {}

      void accept(Visitor* v) override;
      const std::vector<Visitable*> getChildren() const;
      void addChild(Visitable* child);
  };
}
