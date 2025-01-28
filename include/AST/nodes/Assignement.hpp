#include <iostream>

#include "visitor/Visitable.hpp"

namespace YANKI {

  class Assignement : public Visitable {
  private:
    Visitable* identifier;
    Visitable* expression;

  public:
      void accept(Visitor* v) override;
      Visitable* getIdentifier() const;
      Visitable* getExpression() const;
      void setIdentifier(Visitable* );
      void setExpression(Visitable*);
  };
}
