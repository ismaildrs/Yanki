#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include "Lexer.hpp"
#include "AST/AST.hpp"
#include "AST/nodes/Program.hpp"
#include "AST/nodes/Statement.hpp"
#include "AST/nodes/Identifier.hpp"
#include "AST/nodes/Expression.hpp"
#include "AST/nodes/FloatFactor.hpp"
#include "AST/nodes/IntegerFactor.hpp"
#include "AST/nodes/StringFactor.hpp"
#include "AST/nodes/Operation.hpp"
#include "AST/nodes/Assignement.hpp"
#include "AST/nodes/PrintStatement.hpp"
#include "AST/nodes/ExitStatement.hpp"


using tokenPair = std::pair<YANKI::Token, std::string>;

namespace YANKI {
  class ParserInterface {
  public:
      virtual ASTree* parse() = 0;
  };

  class Parser : public ParserInterface {
  private:
      std::vector<tokenPair> tokens;
      int index; // current token in tokens
      ASTree* tree;

      // Production rules -> returns an ASTree node
      Visitable* parseProgram();
      Visitable* parseStatement();
      Visitable* parseAssignment();
      Visitable* parseTerm();
      Visitable* parsePrint();
      Visitable* parseExit();
      Visitable* parseExpression();
      Visitable* parseFactor();
      Visitable* parseIdentifier();

      std::optional<tokenPair> peek(int head = 0);
      std::optional<tokenPair> consume();

  public:
      // Entry point
      Parser(std::vector<tokenPair> tokens);
      ASTree* parse() override;
  };
}
