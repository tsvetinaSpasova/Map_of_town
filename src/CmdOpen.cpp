#include <iostream>
#include "CmdOpen.h"

std::string Open::execute (std::vector<std::string> words, Interface& user){

    if(words.size() == 2){
        if(user.map_of_town.exist_location(words[1])){
            user.map_of_town.open_location(words[1]);
        }
        else{
            std::cout << "Wrong location" << std::endl;
        }
        return "";
    }

    return "Wrong command";
}
