#pragma once
#include "visitor/Visitable.hpp"
#include <string>

namespace YANKI {
  class Identifier : public Visitable {
  private:
      std::string varname;

  public:
      Identifier(std::string name);
      void accept(Visitor* v) override;
      const std::string& getVarName() const;
      void setVarName(const std::string& name);
  };
}
