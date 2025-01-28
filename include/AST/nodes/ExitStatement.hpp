#pragma once
#include "visitor/Visitable.hpp"

namespace YANKI {

  class ExitStatement : public Visitable {
  private:
      int exitCode;

  public:
      void accept(Visitor* v) override;
      int getExitCode() const;
      void setExitCode(int code);
  };
}
