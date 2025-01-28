#include "parser/Parser.hpp"

namespace YANKI {
  Parser::Parser(std::vector<tokenPair> tokens) : tokens(tokens), index(0), tree(new ASTree()) {
    if(isDebug()) std::cout << "Parser Phase: -----------------" << std::endl;
  }

  Visitable* Parser::parseProgram() {
      Program* program = new Program();
      while (peek().has_value()) {

          if (Visitable* stmt = parseStatement()) {
              program->addChild(stmt);
          } else {
              throw std::runtime_error("Unexpected token in program.");
          }
      }
      return program;
  }

  Visitable* Parser::parseStatement() {
      Visitable* stmt = nullptr;
      if ((stmt = parsePrint()) || (stmt = parseAssignment()) || (stmt = parseExit())) {
          return stmt;
      }
      return nullptr;
  }

  Visitable* Parser::parseAssignment() {
      size_t savedIndex = index;
      Visitable* id = parseIdentifier();
      if (!id) return nullptr;

      if (!peek().has_value() || peek().value().first != Token::ASSIGN) {
          index = savedIndex;
          delete id;
          return nullptr;
      }
      consume(); // Consume ASSIGN

      Visitable* expr = parseExpression();
      if (!expr) {
          index = savedIndex;
          delete id;
          return nullptr;
      }

      if (!peek().has_value() || peek().value().first != Token::END_EXPR) {
          index = savedIndex;
          delete id;
          delete expr;
          return nullptr;
      }
      consume(); // Consume ;

      Assignement* assignment = new Assignement();
      assignment->setIdentifier(id);
      assignment->setExpression(expr);
      return assignment;
  }

  Visitable* Parser::parseExpression() {
      Visitable* node = parseTerm();
      while (peek().has_value()) {
          tokenPair op = peek().value();
          if (op.first == Token::OP && (op.second == "+" || op.second == "-")) {
              consume();
              Operation* operation = new Operation();
              operation->setOp(op.second == "+" ? OpType::ADD : OpType::SUB);
              operation->setFactor1(node);
              Visitable* right = parseTerm();
              if (!right) {
                  delete operation;
                  return node;
              }
              operation->setFactor2(right);
              node = operation;
          } else {
              break;
          }
      }
      return node;
  }

  Visitable* Parser::parseTerm() {
      Visitable* node = parseFactor();
      while (peek().has_value()) {
          tokenPair op = peek().value();
          if (op.first == Token::OP && (op.second == "*" || op.second == "/")) {
              consume();
              Operation* operation = new Operation();
              operation->setOp(op.second == "*" ? OpType::MUL : OpType::DIV);
              operation->setFactor1(node);
              Visitable* right = parseFactor();
              if (!right) {
                  delete operation;
                  return node;
              }
              operation->setFactor2(right);
              node = operation;
          } else {
              break;
          }
      }
      return node;
  }

  Visitable* Parser::parsePrint() {
      if (!peek().has_value() || peek().value().first != Token::SHOW){
        return nullptr;
      }
      consume(); // Consume SHOW

      if(!peek().has_value() || peek().value().first != Token::ASSIGN) return nullptr;
      consume(); // Consume :

      Visitable* expr = parseExpression();
      if (!expr) throw std::runtime_error("Expected expression after 'show'.");

      if (!peek().has_value() || peek().value().first != Token::END_EXPR) {
          delete expr;
          throw std::runtime_error("Expected ';' after print statement.");
      }
      consume(); // Consume ;

      PrintStatement* print = new PrintStatement();
      print->setExpression(expr);
      return print;
  }

  Visitable* Parser::parseExit() {
      if (!peek().has_value() || peek().value().first != Token::EXIT) return nullptr;
      consume(); // Consume EXIT

      if (!peek().has_value() || peek().value().first != Token::END_EXPR) {
          throw std::runtime_error("Expected ';' after 'exit'.");
      }
      consume(); // Consume ;

      return new ExitStatement();
  }

  Visitable* Parser::parseIdentifier() {
      if (peek().has_value() && peek().value().first == Token::IDENTIFIER) {
          tokenPair tok = consume().value();
          return new Identifier(tok.second);
      }
      return nullptr;
  }

  Visitable* Parser::parseFactor() {
      if (!peek().has_value()) return nullptr;

      tokenPair tok = peek().value();
      if (tok.first == Token::CST) {
          consume();
          return new IntegerFactor(std::stoi(tok.second));
      } else if (tok.first == Token::IDENTIFIER) {
          return parseIdentifier();
      } else if (tok.first == Token::OPEN_PAREN) {
          consume(); // Consume (
          Visitable* expr = parseExpression();
          if (!expr) throw std::runtime_error("Expected expression after '('.");
          if (!peek().has_value() || peek().value().first != Token::CLOSE_PAREN) {
              delete expr;
              throw std::runtime_error("Expected ')' after expression.");
          }
          consume(); // Consume )
          return expr;
      }
      return nullptr;
  }

  std::optional<tokenPair> Parser::peek(int ahead) {
      size_t pos = index + ahead;
      return pos < tokens.size() ? tokens[pos] : std::optional<tokenPair>();
  }

  std::optional<tokenPair> Parser::consume() {
      return index < tokens.size() ? tokens[index++] : std::optional<tokenPair>();
  }

  ASTree* Parser::parse() {
      tree->setRoot(parseProgram());
      return tree;
  }
}