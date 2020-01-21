#include <iostream>
#include "CmdMove.h"

std::string Move::execute (std::vector<std::string> words, Interface& user){

    if(words.size() == 2 && user.map_of_town.valid_location(words[1]) && user.map_of_town.has_path(user.get_curr_location(), words[1])){
        std::vector<std::vector<std::string>> paths = user.map_of_town.three_shortest_paths(user.get_curr_location(), words[1]);
        int length = paths[0].size();
        for(int i = 0; i < length - 1; i++){
            std::cout << paths[0][i] << " -> ";
        }
        std::cout << paths[0][length - 1] << std::endl;
        user.change_location(words[1]);
        return "";
    }

    return "No way to there";
}
