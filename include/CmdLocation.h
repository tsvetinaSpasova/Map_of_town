#ifndef LOCATION_H
#define LOCATION_H
#include "Command.h"

class Location : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // LOCATION_H
