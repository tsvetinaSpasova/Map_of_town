#include "CmdTour.h"

std::string Tour::execute (std::vector<std::string> words, Interface& user){

    if(words.size() == 1 && words[0] == "tour"){
        user.map_of_town.print_Euler_path();
        std::cout << std::endl;
        return "";
    }
    return "Wrong command";
}
