#pragma once
#include "visitor/Visitable.hpp"
#include <string>

namespace YANKI {
  class StringFactor : public Visitable {
  private:
      std::string value;

  public:
      void accept(Visitor* v) override;
      const std::string& getValue() const;
      void setValue(const std::string& val);
  };
}
