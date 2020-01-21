#ifndef TOUR_H
#define TOUR_H
#include <Command.h>

class Tour : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // TOUR_H
