#pragma once 

namespace YANKI{
  enum STATES{
    debug, 
    production
  };

  #define VERSION 1.0
  
  #define STATE STATES::debug

  inline constexpr bool isDebug(){
    return STATE == STATES::debug;
  }

  const std::string RESET = "\033[0m";
  const std::string BOLD = "\033[1m";
  const std::string RED = "\033[31m";
  const std::string GREEN = "\033[32m";
  const std::string YELLOW = "\033[33m";
  const std::string BLUE = "\033[34m";
  const std::string MAGENTA = "\033[35m";
  const std::string CYAN = "\033[36m";
}
