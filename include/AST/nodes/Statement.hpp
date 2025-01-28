#pragma once
#include "visitor/Visitable.hpp"
#include <iostream>
#include <vector>

namespace YANKI {
  class Statement : public Visitable {
  private:
      std::vector<Visitable*> children;

  public:
      void accept(Visitor* v) override;
      const std::vector<Visitable*>& getChildren() const;
      void addChild(Visitable* child);
  };
}
