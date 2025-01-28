#include "AST/nodes/ExitStatement.hpp"

namespace YANKI {
  void ExitStatement::accept(Visitor* v) {
      v->visitExitStatement(this);
  }

  int ExitStatement::getExitCode() const {
      return exitCode;
  }

  void ExitStatement::setExitCode(int code) {
      exitCode = code;
  }
}
