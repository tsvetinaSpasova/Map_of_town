#include <iostream>
#include "CmdClose.h"

std::string Close::execute (std::vector<std::string> words, Interface& user){

    if(words.size() == 2){
        if(user.map_of_town.valid_location(words[1])){
            user.map_of_town.close_location(words[1]);
        }
        else{
            std::cout << "Wrong location" << std::endl;
        }
        return "";
    }

    return "Wrong command";
}

