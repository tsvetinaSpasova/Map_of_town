#include <iostream>
#include "CmdClosed.h"

std::string Closed::execute (std::vector<std::string> words, Interface& user){
    ///TODO
    if(words.size() == 1){
        user.map_of_town.print_closed_locations();
        return "";
    }
    return "Wrong command";
}
