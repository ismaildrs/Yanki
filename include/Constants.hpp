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

}
