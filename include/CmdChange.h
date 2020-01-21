#ifndef CHANGE_H
#define CHANGE_H
#include "Command.h"

class Change: public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // CHANGE_H
