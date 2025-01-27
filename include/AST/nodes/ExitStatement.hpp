#include "Visitor/Visitable.hpp"

namespace YANKI{
  class ExitStatement : public Visitable {
  private:
      int exitCode;

  public:
      void accept(Visitor* v) override {
          v->visitExitStatement(this);
      }

      int getExitCode() const {
          return exitCode;
      }

      void setExitCode(int code) {
          exitCode = code;
      }
  };
}