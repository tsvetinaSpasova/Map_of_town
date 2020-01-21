#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
#include <Graph.h>
#include <Interface.h>


class Command{
public:
    virtual std::string execute (std::vector<std::string> words, Interface& location) = 0;
};


#endif // COMMAND_H_INCLUDED
