#include "Visitor/Visitable.hpp"

namespace YANKI{
  class PrintStatement : public Visitable {
  private:
      Visitable* identifier;

  public:
      void accept(Visitor* v) override {
          v->visitPrintStatement(this);
      }

      const Visitable* getIdentifier() const {
          return identifier;
      }

      void setIdentifier(const Visitable* identifier) {
          identifier = identifier;
      }
  };
}