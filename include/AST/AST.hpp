#pragma once
#include <iostream>
#include <vector>
#include "visitor/Visitable.hpp"

namespace YANKI
{
  enum OpType
  {
    ADD,
    SUB,
    MUL,
    DIV
  };

  enum FactorType
  {
    INT,
    FLOAT,
    STRING
  };

  class ASTree {
    Visitable* root; // the main root

    public:

    inline Visitable* getRoot() const{
      return root;
    }

    void setRoot(Visitable* pgm){
      root = pgm;
    }

  };

}
