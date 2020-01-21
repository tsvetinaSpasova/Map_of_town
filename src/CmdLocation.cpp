#include <iostream>
#include "CmdLocation.h"

std::string Location::execute (std::vector<std::string> words, Interface& location){
    if(words.size() == 1){
        std::cout << "Your location: " << location.get_curr_location() << std::endl;
        return "";
    }
    return "Wrong command";
}
