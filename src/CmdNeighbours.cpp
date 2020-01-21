#include <iostream>
#include "CmdNeighbours.h"

std::string Neighbours::execute(std::vector<std::string> words, Interface& user){

    if(words.size() == 1){
        user.map_of_town.print_neighbours(user.get_curr_location());
        return "";
    }
    return "Wrong command";
}


