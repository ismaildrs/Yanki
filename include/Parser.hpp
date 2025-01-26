#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <Lexer.hpp>
#include <AST.hpp>

using tokenPair = std::pair<YANKI::Token, std::string>;
using ASTree = ASTree;
using Node = Node;
using NodeData = NodeData;

namespace YANKI
{
  // Use the Visitor Pattern: to implement ASTree
  // enum Rule
  // {
  //   ASSIGN,
  //   OPERATION,
  //   OPERATOR,
  //   NUMBER,
  //   PRINT,
  //   STATEMENT,
  //   PROGRAM,
  //   VALUE,
  //   VAR,
  //   CST,
  // };

  class ParserInterface
  {
  public:
    virtual ASTree *parse() = 0;
  };

  class Parser : public ParserInterface
  {
  private:
    std::vector<tokenPair> tokens;
    int index; // current token in tokens
    ASTree* tree;

    // Production rules -> returns an ASTree node
    Visitable* parseStatement(){

    }
    Visitable* parseOperation(){

    }
    Visitable* parseAssignement(){

    }
    Visitable* parsePrint(){

    }
    Visitable* parseExit(){

    }
    Visitable* parseExpression(){

    }
    Visitable* parseOperator(){

    }
    Visitable* parseFactor(){

    }

  public:
    Parser(std::vector<tokenPair> &tokens) : tokens(tokens)
    {
      tree = new ASTree();
      if(isDebug()) std::cout << "Parser Phase: -----------------" << std::endl;
    }

    std::optional<tokenPair> peek(int head = 1)
    {
      if (tokens.size() < index + head)
        return {};
      else
        return tokens[index + head - 1];
    }

    std::optional<tokenPair> consume()
    {
      return tokens[index];
    }

    // entry point
    ASTree* parse() override
    {
      
    }
  };
}