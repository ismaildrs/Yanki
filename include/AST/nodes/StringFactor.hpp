#pragma once
#include "Visitor/Visitable.hpp"

namespace YANKI{
  class StringFactor : public Visitable
  {
  private:
     std::string value;

  public:
    void accept(Visitor* v) override
    {
      v->visitStringFactor(this);
    }

    const std::string& getValue() const
    {
      return value;
    }

    void setValue(const std::string& val)
    {
      value = val;
    }
  };
}