#pragma once
#include <iostream>
#include "Visitor.hpp"

namespace YANKI{
  class Visitable
  {
    public:
      virtual void accept(Visitor* v) = 0;
  };
}