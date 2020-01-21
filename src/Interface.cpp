#include <iostream>
#include "Interface.h"
#include "Command.h"
#include "CmdLocation.h"
#include "CmdChange.h"
#include "CmdNeighbours.h"
#include "CmdMove.h"
#include "CmdClose.h"
#include "CmdOpen.h"
#include "CmdClosed.h"
#include "CmdTour.h"

Interface:: Interface(){
    commands["location"] = new Location();
    commands["change"] = new Change();
    commands["neighbours"] = new Neighbours();
    commands["move"] = new Move();
    commands["close"] = new Close();
    commands["open"] = new Open();
    commands["closed"] = new Closed();
    commands["tour"] = new Tour();

}

void Interface::change_location(std::string other_location){
    curr_location = other_location;
}

std::string Interface::get_curr_location() const{
    return curr_location;
}

void Interface::execute(std::string file_name){
    map_of_town.load(file_name);

    std::string start_location;
    do{
        std::cout << "Start location: ";
        getline(std::cin, start_location);
        if(map_of_town.exist_location(start_location)){
            curr_location = start_location;
        }
    }
    while(!map_of_town.exist_location(start_location));

    std::string command;
    do{
        getline(std::cin, command);
        std::vector<std::string> words;
        split(command,words, ' ');
        if(commands.find(words[0]) == commands.end()){
            if(words[0] != "exit")
                std::cout << "Wrong command\n";
        }
        else
            std::cout << commands[words[0]]->execute(words, *this) << std::endl;
    }while(command != "exit");

}
