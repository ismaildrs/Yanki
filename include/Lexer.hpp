#pragma once
#include <iostream>
#include <optional>
#include <vector>

namespace YANKI
{
  enum Token
  {
    ASSIGN, // :
    ADD,
    SUB,
    MUL,
    DIV,
    OPTH, // "("
    CPTH, // ")"
    SHOW, // print to console
    VAR,  // variables
    CST,  // Numbers
    EXP   // end of expression: ;
  };

  class Lexer
  {
  public:
    Lexer(const std::string &src)
        : src(src), index(0)
    {
      std::cout << "Lexer: -----------------" << std::endl;
    }

    std::optional<char> peek(int head = 1)
    {
      if (index + head > src.length())
      {
        return {}; // End of input
      }
      return src.at(index + head - 1);
    }

    std::optional<char> consume()
    {
      if (peek().has_value())
      {
        return src.at(index++);
      }
      return {};  // Return empty optional if nothing to consume
    }

    std::vector<std::pair<Token, std::string>> tokenize()
    {
      std::vector<char> buff;
      while (peek().has_value())
      {
        if (isalpha(peek().value()))
        {
          buff.push_back(consume().value());
          while (peek().has_value() && isalnum(peek().value()))
          {
            buff.push_back(consume().value());
          }
          tokens.push_back({Token::VAR, std::string(buff.begin() ,buff.end())}); // Add token for variable
          buff.clear(); // Clear buffer (though it's not strictly necessary)
        }
        else if (isdigit(peek().value()))
        {
          while (peek().has_value() && isdigit(peek().value()))
          {
            buff.push_back(consume().value());
          }
          tokens.push_back({Token::CST, std::string(buff.begin() ,buff.end())}); // Add token for constant (number)
          buff.clear();
        }
        else if (peek().value() == ':')
        {
          consume();
          tokens.push_back({Token::ASSIGN, ":"}); // Add token for assign operator
        }
        else if (peek().value() == '+')
        {
          consume();
          tokens.push_back({Token::ADD, "+"}); // Add token for assign operator
        }
        else if (peek().value() == '-')
        {
          consume();
          tokens.push_back({Token::SUB, "-"}); // Add token for assign operator
        }
        else if (peek().value() == '*')
        {
          consume();
          tokens.push_back({Token::MUL, "*"}); // Add token for assign operator
        }
        else if (peek().value() == '/')
        {
          consume();
          tokens.push_back({Token::DIV, "/"}); // Add token for assign operator
        }
        else if (peek().value() == '(')
        {
          consume();
          tokens.push_back({Token::OPTH, "("}); // Add token for opening parenthesis
        }
        else if (peek().value() == ')')
        {
          consume();
          tokens.push_back({Token::ASSIGN, ")"}); // Add token for closing parenthesis
        }
        else if (peek().value() == ';')
        {
          consume();

          tokens.push_back({Token::EXP, ";"}); // Add token for expression end
        }
        else if (peek().value() == ' ' || peek().value() == '\n')
        {
          consume(); // Skip spaces
          continue;
        }
        else
        {
          std::cerr << "Lexical error: Wrong character" << "\n";
          exit(1); // Exit on error (could be replaced with throwing an exception)
        }
      }
      return tokens; // Return the list of tokens
    }

  private:
    std::string src;
    std::vector<std::pair<Token, std::string>> tokens;
    int index;
  };

}
