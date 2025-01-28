#pragma once
#include <iostream>
#include <optional>
#include <vector>
#include <Constants.hpp>

namespace YANKI
{

  // TODO: use regular exp to identify elements of the language 

  enum Token {
    ASSIGN,     // : (or consider renaming to COLON if not assignment)
    OP,
    OPEN_PAREN, // (
    CLOSE_PAREN,// )
    SHOW,       // print to console
    IDENTIFIER,        // variables
    // DATA TYPES
    // INTEGER,
    // FLOAT,
    // STRING,
    // CHAR,
    // ARRAY,
    CST,        // numbers TODO: change CST with proper data types
    END_EXPR,   // end of expression: ;
    EXIT        // exit
  };


  class LexerInterface
  {
  public:
    virtual std::vector<std::pair<Token, std::string>> tokenize() = 0;
  };

  class Lexer : public LexerInterface
  {
  public:
    Lexer(const std::string &src)
        : src(src), index(0)
    {
      if(isDebug()) std::cout << "Lexer Phase: -----------------" << std::endl;
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
      return {}; // Return empty optional if nothing to consume
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
          std::string gen = std::string(buff.begin(), buff.end());
          if (!gen.compare("show"))
            tokens.push_back({Token::SHOW, gen}); // Add token for variable
          else if (!gen.compare("exit"))
            tokens.push_back({Token::EXIT, gen});
          else
            tokens.push_back({Token::IDENTIFIER, gen});
          buff.clear(); // Clear buffer (though it's not strictly necessary)
        }
        else if (isdigit(peek().value()))
        {
          while (peek().has_value() && isdigit(peek().value()))
          {
            buff.push_back(consume().value());
          }
          tokens.push_back({Token::CST, std::string(buff.begin(), buff.end())}); // Add token for constant (number)
          buff.clear();
        }
        else if (peek().value() == ':')
        {
          consume();
          tokens.push_back({Token::ASSIGN, ":"});
        }
        else if (peek().value() == '+')
        {
          consume();
          tokens.push_back({Token::OP, "+"});
        }
        else if (peek().value() == '-')
        {
          consume();
          tokens.push_back({Token::OP, "-"});
        }
        else if (peek().value() == '*')
        {
          consume();
          tokens.push_back({Token::OP, "*"});
        }
        else if (peek().value() == '/')
        {
          consume();
          tokens.push_back({Token::OP, "/"});
        }
        else if (peek().value() == '(')
        {
          consume();
          tokens.push_back({Token::OPEN_PAREN, "("}); // Add token for opening parenthesis
        }
        else if (peek().value() == ')')
        {
          consume();
          tokens.push_back({Token::CLOSE_PAREN, ")"}); // Add token for closing parenthesis
        }
        else if (peek().value() == ';')
        {
          consume();

          tokens.push_back({Token::END_EXPR, ";"}); // Add token for expression end
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
