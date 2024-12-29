#include <iostream>
#include <fstream>
#include <sstream>
#include<Lexer.hpp>

int main(int argc, char* argv[]){
  std::ifstream srcFile(argv[1]);

  if(!srcFile.is_open()){
    std::cerr << "Input File: File was not found" << "\n";
    exit(1);
  }
  std::stringstream src;
  src << srcFile.rdbuf();

  YANKI::Lexer lexer = YANKI::Lexer(src.str());
  std::vector<std::pair<YANKI::Token, std::string>>  tokens = lexer.tokenize();

  for(auto token: tokens){
    std::cout << token.second << std::endl;
  }

  return 0;
}