#pragma once
#include <iostream>
#include <visitor/Visitor.hpp>

namespace YANKI{
  class Visitable
  {
    public:
      virtual void accept(Visitor* v) = 0;
  };
}