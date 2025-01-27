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

using tokenPair = std::pair<YANKI::Token, std::string>;

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
    Visitable* parseProgram(){
      Program* program = new Program();
      while(peek().has_value()){
        program->addChild(parseStatement());
      }
      return program;
    }

    Visitable* parseStatement(){
      Statement* statement = new Statement();
      if(Visitable* node = parseAssignement()){
        statement->addChild(node);
      } else if(Visitable* node = parsePrint()){
        statement->addChild(node);
      } else if(Visitable* node = parseExit()){
        statement->addChild(node);
      } else {
        delete statement; // free memory
        return nullptr;
      }
      return statement;
    }

    Visitable* parseAssignement(){
      Statement* statement = new Statement(); 
      if(!peek().has_value()) return nullptr;
      int prevIndex = index;
      tokenPair currentToken = consume().value();
      if(currentToken.first == Token::IDENTIFIER){
        statement->addChild(new Identifier(currentToken.second));
        currentToken = consume().value();
        if(currentToken.first == Token::ASSIGN){
          currentToken = consume().value();
          if(Visitable* node = parseExpression()){
            statement->addChild(node);
          }

          currentToken = consume().value();
          if(currentToken.first == Token::END_EXPR){ // check for ";"
            return statement;
          }
        }
      }
      delete statement;
      prevIndex = index;
      return nullptr;
    }


    Visitable* parseOperation() {
      if (!peek().has_value()) return nullptr;

      Visitable* leftFactor = parseFactor();
      if (!leftFactor) return nullptr;

      while (true) {
        tokenPair currentToken = peek().value();
        if (currentToken.first == Token::OP) {
          OpType op;
          const std::string& currentOp = currentToken.second;

          if (currentOp == "+") {
              op = OpType::ADD;
          } else if (currentOp == "-") {
              op = OpType::SUB;
          } else if (currentOp == "*") {
              op = OpType::MUL;
          } else if (currentOp == "/") {
              op = OpType::DIV;
          } else {
              return nullptr; // Unknown operator
          }

          Operation* operation = new Operation();
          operation->setOp(op);

          Visitable* rightFactor = parseFactor();
          if (!rightFactor) throw std::runtime_error("Expected factor after operator.");

          Operation* operation = new Operation();
          operation->setOp(op);
          operation->setFactor1(leftFactor);
          operation->setFactor2(rightFactor);

          leftFactor = operation; // Chain the operation
        } else {
          break; // Exit loop if no more operators
        }
      }
      return leftFactor;
    }

    Visitable* parsePrint() {
      if (!peek().has_value()) return nullptr;

      tokenPair currentToken = consume().value();
      if (currentToken.first == Token::SHOW) {
        Visitable* expression = parseExpression();
        if (!expression) throw std::runtime_error("Expected expression after 'print'.");
        
        currentToken = consume().value();
        if (currentToken.first != Token::END_EXPR) throw std::runtime_error("Expected ';' after print statement.");
  
        Statement* printStatement = new Statement();
        printStatement->addChild(expression);
        return printStatement;
      }
      return nullptr;
    }

    Visitable* parseExit() {
      if (!peek().has_value()) return nullptr;

      tokenPair currentToken = consume().value();
      if (currentToken.first == Token::EXIT) {
        currentToken = consume().value();
        if (currentToken.first != Token::END_EXPR) throw std::runtime_error("Expected ';' after 'exit'.");
        
        Statement* exitStatement = new Statement();
        return exitStatement;
      }
      return nullptr;
    }

    Visitable* parseExpression() {
      if (!peek().has_value()) return nullptr;

      Visitable* left = parseOperation(); // Parse left operand (or the entire operation chain)
      if (!left) return nullptr;

      return left; // Return the parsed expression
    }

    Visitable* parseOperator() {
      if (!peek().has_value()) return nullptr;

      tokenPair currentToken = consume().value();
      if (currentToken.first == Token::OP) {
          OpType op;
          const std::string& currentOp = currentToken.second;

          if (currentOp == "+") {
              op = OpType::ADD;
          } else if (currentOp == "-") {
              op = OpType::SUB;
          } else if (currentOp == "*") {
              op = OpType::MUL;
          } else if (currentOp == "/") {
              op = OpType::DIV;
          } else {
              return nullptr; // Unknown operator
          }

          Operation* operation = new Operation();
          operation->setOp(op);
          return operation;
      }
      return nullptr;
    }

    Visitable* parseFactor() {
      if (!peek().has_value()) return nullptr;

      tokenPair currentToken = consume().value();
      if (currentToken.first == Token::CST) {
        IntegerFactor* factor = new IntegerFactor();
        factor->setValue(std::stoi(currentToken.second));
        return factor;
      } else if (currentToken.first == Token::IDENTIFIER) {
        Identifier* variable = new Identifier(currentToken.second); 
        return variable;
      } else if (currentToken.first == Token::OPEN_PAREN) {
        Visitable* expression = parseExpression(); // Parse inner expression
        currentToken = consume().value();
        if (currentToken.first != Token::CLOSE_PAREN) throw std::runtime_error("Expected ')' after expression.");
        return expression;
      }
      return nullptr; // Invalid factor
    }

    std::optional<tokenPair> peek(int head = 1)
    {
      if (tokens.size() < index + head)
        return tokens[index];
      else
        return {};
    }

    std::optional<tokenPair> consume()
    {
      if(peek()){
        return tokens[index];
      } else {
        return {};
      }
    }


    public:
    // Entry point

    Parser(std::vector<tokenPair> tokens): tokens(tokens){};

    ASTree* parse() override {
      tree->setProgram(parseProgram());
      return tree;
    }
  };
}