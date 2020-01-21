#ifndef NEIGHBOURS_H
#define NEIGHBOURS_H
#include "Command.h"

class Neighbours : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& my_map);
};

#endif // NEIGHBOURS_H
