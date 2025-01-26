#include "Parser.hpp"
#include "AST.hpp"
#include <Constants.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include<Lexer.hpp>

int main(int argc, char* argv[]){
  // check if source file is provided
  if(argc != 2){
    std::cout << "Usage: yanki [source]" << "\n";
    exit(1);
  }

  std::ifstream srcFile(argv[1]);

  // check if source file exists
  if(!srcFile.is_open()){
    std::cerr << "Input File: File was not found" << "\n";
    exit(1);
  }

  std::stringstream src;
  src << srcFile.rdbuf();

  // initialize a lexer
  YANKI::Lexer lexer(src.str());
  std::vector<std::pair<YANKI::Token, std::string>>  tokens = lexer.tokenize();

  // intialize a parser
  YANKI::Parser parser(tokens);
  parser.parse();

  // debug
  if(YANKI::isDebug())
    for(auto token: tokens){
        std::cout << token.first << ": " << token.second << std::endl;
    }


  return 0;
}