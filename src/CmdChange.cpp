#include <iostream>
#include "CmdChange.h"

std::string Change::execute (std::vector<std::string> words, Interface& user){

    if(words.size() == 2){
        if(user.map_of_town.valid_location(words[1])){
            user.change_location(words[1]);
        }else{
            std::cout << "No way to go there" << std::endl;
        }
        return "";
    }
    return "Wrong command";
}
