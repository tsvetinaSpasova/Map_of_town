#ifndef INTERFACE_H
#define INTERFACE_H
#include <Graph.h>
#include <unordered_map>

class Command;

class Interface
{
    public:
        Interface();
        Graph map_of_town;
        std::string get_curr_location() const;
        void change_location(std::string);
        void execute(std::string);

    private:
        std::string curr_location;
        std::unordered_map<std::string, Command*> commands;
};

#endif // INTERFACE_H
